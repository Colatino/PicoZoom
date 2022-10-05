#include <MIDI.h>
// pio-usb is required for rp2040 host
#include "pio_usb.h"
#define HOST_PIN_DP 2  // Pin used as D+ for host, D- = D+ + 1

#include "Adafruit_TinyUSB.h"
#define LANGUAGE_ID 0x0409  // English
// USB Host object
Adafruit_USBH_Host USBHost;

#include "oled.h"

#include "g1xfour.h"

#include "footswitch.h"

// holding device descriptor
tusb_desc_device_t desc_device;
static uint8_t midi_dev_addr = 0;
static bool cloned = false;
static bool device_mounted = false;
static bool init_core1 = false;
String manufacturer, product;

static bool sysex_complete = false;

uint8_t whoareyou[] = { 0x7e, 0x00, 0x06, 0x01 };
uint8_t editoron[] = { 0x52, 0x00, 0x6e, 0x50 };
uint8_t editoroff[] = { 0x52, 0x00, 0x6e, 0x51 };
uint8_t patch_download_current[] = { 0x52, 0x00, 0x6e, 0x29 };
uint8_t toggle_effect[] = { 0x52, 0x00, 0x6E, 0x64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 };
uint8_t set_param[] = { 0x52, 0x00, 0x6E, 0x64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
int sequence = 0;

struct Patch {
  uint8_t cur_slot = 0;
  uint8_t n_effects = 0;
  uint8_t slots[5];
  bool states[5];
  bool delay[5];
  bool xpedal[5];
  Effect effects[5];
};

#define NUM_PEDALS 1
int switch_pins[] = { 5 };
FootSwitch footswitch[NUM_PEDALS];

int buses;
Oled oleds[NUM_PEDALS];

Patch current_patch;

typedef enum {
  EMPTY,
  READING,
  COMPLETE
} message_state_t;

typedef enum {
  IDLE,
  WAITING,
  BUSY
} core_state_t;

typedef enum {
  DISCONNECTED,
  CONNECTED,
  READY,
  IDENTIFIED,
  IDENTIFIED_NOT_SUPPORTED,
  EDITOR_ON
} pedal_usb_state_t;

typedef enum {
  NONE,
  IDENTIFY_REQUEST,
  IDENTIFY_PENDING,
  IDENTIFY_RECEIVED,
  EDITOR_ON_REQUEST,
  EDITOR_ON_PENDING,
  EDITOR_ON_RECEIVED,
  CURRENT_PATCH_REQUEST,
  CURRENT_PATCH_PENDING,
  CURRENT_PATCH_RECEIVED,
  CURRENT_PATCH_UNPACK,
  CURRENT_PATCH_UNPACKED,
  CURRENT_PATCH_PARSE,
  CURRENT_PATCH_PARSED,
  CURRENT_PATCH_CHANGED,
  SET_PARAM_REQUEST,
  SET_PARAM_PENDING,
  SET_PARAM_RECEIVED,
  TOGGLE_EFFECT_REQUEST,
  TOGGLE_EFFECT_PENDING,
  TOGGLE_EFFECT_RECEIVED

} core_task_t;

core_state_t core0_state = IDLE;
core_task_t core0_task = NONE;
core_state_t core1_state = IDLE;
core_task_t core1_task = NONE;

volatile pedal_usb_state_t usb_state = DISCONNECTED;

struct Sysex {
  uint8_t message[1024];
  int size = 0;
  message_state_t status = EMPTY;
} sysex_message;

struct PChange {
  uint8_t message[3];
  message_state_t status = EMPTY;
} pc_message;

Sysex unpacked;

// HELPER FUNCTIONS
// Send a new task to the other core
// core0 <-> core1
bool core_queue_push(uint32_t new_task) {
  return rp2040.fifo.push_nb(new_task);
}

// Get a task from the other core
// core0 <-> core1
// return true on success
bool core_queue_pop(uint32_t* dest) {
  if (rp2040.fifo.available() > 0) {
    *dest = rp2040.fifo.pop();
    return true;
  }
  return false;
}
// CORE 0
// handles functions other than USB communications (switches, displays, data parsing...)

bool handle_identification() {
  if (sysex_message.message[5] == 0x6e && sysex_message.message[6] == 0x00) {
    uint8_t temp = sysex_message.message[7];
    if (temp == 0x00) {
      Serial.println("G5n is currently unsupported");
    } else if (temp == 0x02) {
      Serial.println("G3n is currently unsupported");
    } else if (temp == 0x04) {
      Serial.println("G3Xn is currently unsupported");
    } else if (temp == 0x0c) {
      Serial.println("This is a G1Four");
      return true;
    } else if (temp == 0x0d) {
      Serial.println("This is a G1XFour");
      return true;
    } else if (temp == 0x0e) {
      Serial.println("B1Four is currently unsupported");
    } else if (temp == 0x0f) {
      Serial.println("B1XFour is currently unsupported");
    } else if (temp == 0x10) {
      Serial.println("GCE-3 is currently unsupported");
    } else if (temp == 0x11) {
      Serial.println("A1Four is currently unsupported");
    } else if (temp == 0x12) {
      Serial.println("A1XFour is currently unsupported");
    } else {
      Serial.println("Unidentified pedal");
    }
    return false;
  }
  return false;
}

int find_section_index(const char* section) {
  for (int i = 0; i < unpacked.size; i++) {
    if (unpacked.message[i] == section[0] && unpacked.message[i + 1] == section[1] && unpacked.message[i + 2] == section[2] && unpacked.message[i + 3] == section[3]) {
      return i;
    }
  }
  return -1;
}

bool unpack(int start_byte) {
  Sysex tounpack;
  for (int i = start_byte; i < sysex_message.size; i++) {
    tounpack.message[i - start_byte] = sysex_message.message[i];
  }
  unpacked.size = midi::decodeSysEx(tounpack.message, unpacked.message, sysex_message.size - start_byte);
  if (unpacked.size > 0) {
    return true;
  } else {
    return false;
  }
}

void parse_patch() {
  // Check if it is a Patch message (look PTCF at start)
  if (find_section_index("PTCF") > -1) {
    //Handle patch file
    // Useful data is between EDTB and PPRM keywords
    int edtb_start = find_section_index("EDTB") + 4;
    int edtb_end = find_section_index("PPRM");
    int neff = unpacked.message[edtb_start] / 24;
    current_patch.n_effects = neff;
    current_patch.cur_slot = 0;
    for (int i = 0; i < neff; i++) {
      long aux = unpacked.message[edtb_start + (7 + i * 24)] << 24 | unpacked.message[edtb_start + (6 + i * 24)] << 16 | unpacked.message[edtb_start + (5 + i * 24)] << 8 | unpacked.message[edtb_start + (4 + i * 24)];
      long id = (aux >> 1) & 0xfffffff;
      int index = get_effect_by_id(id);
      bool state = aux & 1;
      if (index > -1) {
        current_patch.effects[i] = effects[index];
        current_patch.states[i] = state;
        current_patch.slots[i] = current_patch.cur_slot;
        current_patch.delay[i] = false;
        for (int j = 0; j < N_DELAYS; j++) {
          if (delay_ids[j] == id) {
            current_patch.delay[i] = true;
            break;
          }
        }
        current_patch.xpedal[i] = false;
        for (int j = 0; j < N_X_PEDALS; j++) {
          if (xpedal_ids[j] == id) {
            current_patch.xpedal[i] = true;
            break;
          }
        }

        current_patch.cur_slot += effects[index].nslots;
        Serial.printf("Effect %s with id %d is %s uses %d slots and has %d parameters\r\n", current_patch.effects[i].fxname, id, state ? "enabled\0" : "disabled\0", current_patch.effects[i].nslots, current_patch.effects[i].nparam);
      }
    }
  }
  unpacked.size = 0;
  sysex_message.size = 0;
  sysex_message.status = EMPTY;
}

void parse_sysex() {
  for (int i = 0; i < sysex_message.size; i++) {
    Serial.printf("%x ", sysex_message.message[i]);
  }
  Serial.println("");
  sysex_message.status = EMPTY;
  if (sysex_message.message[3] == 0x64) {
    if (sysex_message.message[4] == 0x03) {
      // Pedal informing of a change in patch/effect parameters
      if (sysex_message.message[6] < 9) {
        //Change in fx parameter
        uint8_t fxslot = sysex_message.message[6];
        uint8_t fxindex = 0;
        for (int i = 0; i < current_patch.n_effects; i++) {
          if (current_patch.slots[i] == fxslot) {
            fxindex = i;
            break;
          }
        }
        uint8_t param = sysex_message.message[7];
        if (param == 0) {
          // Toggled states
          current_patch.states[fxindex] = sysex_message.message[8];
          oleds[fxindex].clear();
          oleds[fxindex].draw_effect(current_patch.effects[fxindex].fxname, current_patch.states[fxindex]);
          oleds[fxindex].draw();
        } else if (param == 1) {
          // Don't know what it is, better refresh patch
          // Patch/chain updated - better refresh
          core0_task = CURRENT_PATCH_REQUEST;
        } else {
          // Changed parameter - ignore for now
          param -= 2;
          Serial.printf("Changed value of parameter %s\r\n", current_patch.effects[fxindex].params[param].parname);
        }
      } else if (sysex_message.message[6] == 0x09) {
        //Changed patch name - ignore for now
      } else if (sysex_message.message[6] == 0x0a) {
        if (sysex_message.message[7] == 0x02) {
          // Changed global tempo
          // TODO - Implement tap tempo
          uint8_t low = sysex_message.message[8];
          uint8_t high = sysex_message.message[9];
          int tempo = high ? 128 + low : low;
          Serial.println(tempo);
        } else if (sysex_message.message[7] == 0x0c) {
          // Set tuner frequency - ignore
        } else if (sysex_message.message[7] == 0x0f) {
          // Toggle autosave - ignore
        } else if (sysex_message.message[7] == 0x0) {
          // Patch volume - ignore
        }
      }
    } else if (sysex_message.message[4] == 0x12) {
      // Patch/chain updated - better refresh model
      core0_task = CURRENT_PATCH_REQUEST;
    }
  } else if (sysex_message.message[3] == 0x45) {
    // Pedal sending current patch - refresh model
    core0_task = CURRENT_PATCH_REQUEST;
  }
}

void isr() {
  unsigned long aux_time = millis();
  for (int i = 0; i < NUM_PEDALS; i++) {
    footswitch[i].set_trigger_state(millis());
  }
}

void handle_footswitch_states_and_tasks() {
  for (int i = 0; i < NUM_PEDALS; i++) {
    foot_switch_state_t temp_state = footswitch[i].task();
    uint8_t slot = current_patch.slots[i];
    //Serial.println(temp_state);
    if (temp_state == TAP) {
      if (current_patch.delay[i]) {
        oleds[i].clear();
        oleds[i].draw_text("Tap tempo");
        oleds[i].draw();
        delay(500);
      } else {
        oleds[i].clear();
        oleds[i].draw_text("Global bpm");
        oleds[i].draw();
        delay(500);
      }
    } else if (temp_state == HOLD || temp_state == HOLDB) {
      unsigned long new_tempo;
      if (footswitch[i].got_tempo()) {
        new_tempo = footswitch[i].get_tempo();
        // Send tempos to display
        oleds[i].clear();
        if (current_patch.delay[i]) {
          // Draw delay tempo
          oleds[i].draw_tempo(new_tempo,"ms");
        } else {
          // Draw  global BPM
          oleds[i].draw_tempo(60000 / new_tempo,"bpm");
        }
        oleds[i].draw();
        Serial.println(new_tempo);
      }
    } else if (temp_state == TOGGLE) {
      uint8_t state = current_patch.states[i];
      Serial.printf("Toggle effect %s on slot %d: %s\r\n", current_patch.effects[i].fxname, slot, state ? "off\0" : "on\0");

      toggle_effect[6] = slot;
      toggle_effect[9] = !state;
      core0_state = IDLE;
      core0_task = TOGGLE_EFFECT_REQUEST;
    } else if (temp_state == TEMPO || temp_state == TEMPOB) {

      int tempo = footswitch[i].get_tempo();
      Serial.println(tempo);
      if (tempo > 0) {
        // If footswitch is linked to a delay
        if (current_patch.delay[i]) {
          uint8_t tempoLow = (tempo - 10) % 128;
          uint8_t tempoHigh = (tempo - 10) / 128;
          // Set delay time on effect
          set_param[6] = slot;
          //set_param[7] = j;
          set_param[8] = tempoLow;
          set_param[9] = tempoHigh;

          for (int j = 0; j < current_patch.effects[i].nparam; j++) {
            const char* pname = current_patch.effects[i].params[j].parname;
            if (temp_state == TEMPO && strcmp(pname, "Time") == 0 || strcmp(pname, "TimeA") == 0) {
              Serial.printf("Set delay time to %d ms high: %02x low:%02x\r\n", tempo, tempoHigh, tempoLow);
              set_param[7] = j + 2;
              // In case it is a dual delay
              if (strcmp(current_patch.effects[i].params[j].parname, "TimeA") == 0)
                footswitch[i].set_tempo_b();
              // Send tempos to display
              oleds[i].clear();
              oleds[i].draw_tempo(tempo,"ms");
              oleds[i].draw();
              break;
            } else if (temp_state == TEMPOB && strcmp(pname, "TimeB") == 0) {
              Serial.printf("Set delay timeB to %d ms high: %02x low:%02x\r\n", tempo, tempoHigh, tempoLow);
              set_param[7] = j + 2;
              break;
            }
          }
          core0_state = IDLE;
          core0_task = SET_PARAM_REQUEST;
        } else {
          // Set global tempo

          Serial.printf("Setting global tempo to %d ms\r\n", tempo);
          if (tempo < 240) {
            tempo = 240;
          } else if (tempo > 1500) {
            tempo = 1500;
          }
          uint8_t bpm = 60000 / tempo;
          uint8_t bpmLow = bpm % 128;
          uint8_t bpmHigh = bpm / 128;
          set_param[6] = 0x0a;
          set_param[7] = 0x02;
          set_param[8] = bpmLow;
          set_param[9] = bpmHigh;
          oleds[i].clear();
          oleds[i].draw_tempo(bpm,"bpm");
          oleds[i].draw();
          core0_state = IDLE;
          core0_task = SET_PARAM_REQUEST;
        }
      } else {
        core0_state = IDLE;
        core0_task = NONE;
      }
    } else if (temp_state == TEMPOB) {
      unsigned long tempo = footswitch[i].get_tempo();
      // If footswitch is linked to a delay
      if (current_patch.delay[i]) {
        // Set delay time on effect
        for (int j = 0; j < current_patch.effects[i].nparam; j++) {
          if (strcmp(current_patch.effects[i].params[j].parname, "TimeB") == 0) {
            Serial.printf("Param %d is TimeB\r\n", j);
            Serial.printf("Set delay timeB to %d ms\r\n", tempo);
          }
        }
      }
    }
  }
}

void handle_core0_states_and_tasks() {
  //Waiting for other core tasks to complete
  if (core0_state == WAITING) {
    uint32_t other_core;
    // check if tere are any new messages from the other core
    if (core_queue_pop(&other_core)) {
      // New message arrived from core1
      if (core0_task == IDENTIFY_PENDING && other_core == IDENTIFY_RECEIVED) {
        Serial.println("Pedal identification receive");
        core0_state = IDLE;
        core0_task = EDITOR_ON_REQUEST;
        //core0_task = NONE;
        if (handle_identification()) {
          usb_state = IDENTIFIED;
        } else {
          usb_state = IDENTIFIED_NOT_SUPPORTED;
        }
        sysex_message.status = EMPTY;
      } else if (core0_task == EDITOR_ON_PENDING && other_core == EDITOR_ON_RECEIVED) {
        Serial.println("Editor mode turned on");
        core0_state = IDLE;
        core0_task = CURRENT_PATCH_REQUEST;
        usb_state = EDITOR_ON;
        sysex_message.status = EMPTY;
      } else if (core0_task == CURRENT_PATCH_PENDING && other_core == CURRENT_PATCH_RECEIVED) {
        Serial.println("Got current patch");
        core0_state = IDLE;
        core0_task = CURRENT_PATCH_UNPACK;
      } else if (core0_task == TOGGLE_EFFECT_PENDING && other_core == TOGGLE_EFFECT_RECEIVED) {
        Serial.println("Effect toggled");
        core0_state = IDLE;
        core0_task = NONE;
        for (int i = 0; i < NUM_PEDALS; i++) {
          oleds[i].clear();
          oleds[i].draw_effect(current_patch.effects[i].fxname, current_patch.states[i]);
          oleds[i].draw();
        }
      } else if (core0_task == SET_PARAM_PENDING && other_core == SET_PARAM_RECEIVED) {
        Serial.println("Param changed");
        core0_state = IDLE;
        core0_task = NONE;
        for (int i = 0; i < NUM_PEDALS; i++) {
          oleds[i].clear();
          oleds[i].draw_effect(current_patch.effects[i].fxname, current_patch.states[i]);
          oleds[i].draw();
        }
      }
    }
  }
  if (core0_state == IDLE) {
    if (core0_task == NONE) {
      if (usb_state == READY) {
        if (core_queue_push(IDENTIFY_REQUEST)) {
          core0_state = WAITING;
          core0_task = IDENTIFY_PENDING;
        }
      } else if (usb_state == EDITOR_ON) {
        uint32_t other_core;
        // check if tere are any new messages from the other core
        if (core_queue_pop(&other_core)) {
          if (other_core == CURRENT_PATCH_CHANGED) {
            core0_state = IDLE;
            core0_task = CURRENT_PATCH_REQUEST;
            sysex_message.status = EMPTY;
          }
        } else {
          if (sysex_message.status == COMPLETE) {
            parse_sysex();
            //Something changed on the pedal
          }
        }
        handle_footswitch_states_and_tasks();
      }
    } else if (core0_task == EDITOR_ON_REQUEST) {
      if (usb_state == IDENTIFIED) {
        Serial.println("Turn editor on");
        if (core_queue_push(EDITOR_ON_REQUEST)) {
          core0_state = WAITING;
          core0_task = EDITOR_ON_PENDING;
        }
      }
    } else if (core0_task == CURRENT_PATCH_REQUEST) {
      if (usb_state == EDITOR_ON) {
        Serial.println("Request current patch");
        if (core_queue_push(CURRENT_PATCH_REQUEST)) {
          core0_state = WAITING;
          core0_task = CURRENT_PATCH_PENDING;
        }
      }
    } else if (core0_task == CURRENT_PATCH_UNPACK) {
      Serial.println("Unpacking patch data");
      core0_state = BUSY;
      if (unpack(4)) {
        core0_state = IDLE;
        core0_task = CURRENT_PATCH_PARSE;
        sysex_message.status = EMPTY;
      }
    } else if (core0_task == CURRENT_PATCH_PARSE) {
      Serial.println("Parsing patch data");
      core0_state = BUSY;
      parse_patch();
      core0_state = IDLE;
      core0_task = CURRENT_PATCH_PARSED;
    } else if (core0_task == CURRENT_PATCH_PARSED) {
      Serial.println("Entering idle mode");
      core0_task = NONE;
      core0_state = IDLE;
      for (int i = 0; i < NUM_PEDALS; i++) {
        oleds[i].clear();
        oleds[i].draw_effect(current_patch.effects[i].fxname, current_patch.states[i]);
        oleds[i].draw();
      }
    } else if (core0_task == TOGGLE_EFFECT_REQUEST) {
      Serial.println("Request effect toggle");
      if (core_queue_push(TOGGLE_EFFECT_REQUEST)) {
        core0_state = WAITING;
        core0_task = TOGGLE_EFFECT_PENDING;
      }
    } else if (core0_task == SET_PARAM_REQUEST) {
      Serial.println("Request  param change");
      if (core_queue_push(SET_PARAM_REQUEST)) {
        core0_state = WAITING;
        core0_task = SET_PARAM_PENDING;
      }
    }
  }
}

void setup() {
  Wire.setSDA(0);
  Wire.setSCL(1);

  Serial.begin(115200);
  while (!Serial) {
  }
  pinMode(LED_BUILTIN, OUTPUT);

  // Set Pins and ISRs for footswitches
  for (int i = 0; i < NUM_PEDALS; i++) {
    footswitch[i].begin(switch_pins[i], 100);
    attachInterrupt(digitalPinToInterrupt(switch_pins[i]), isr, FALLING);
  }

  // Init displays
  for (int i = 0; i < NUM_PEDALS; i++) {
    oleds[i].begin();
    oleds[i].clear();
    oleds[i].draw_effect("Bypass", true);
    oleds[i].draw();
  }

  Serial.print("Start core1...");
  init_core1 = true;
}

void loop() {
  handle_core0_states_and_tasks();
}

//--------------------------------------------------------------------+
// CORE 1 FUNCTIONS - HANDLE COMMUNICATIONS
//--------------------------------------------------------------------+
// core1's setup
void setup1() {
  core1_state = BUSY;
  while (!init_core1) {
    //wait for core0 to initialize
  }
  Serial.print("setup1...");
  pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
  pio_cfg.pin_dp = HOST_PIN_DP;
  USBHost.configure_pio_usb(1, &pio_cfg);

  // run host stack on controller (rhport) 1
  // Note: For rp2040 pico-pio-usb, calling USBHost.begin() on core1 will have most of the
  // host bit-banging processing works done in core1 to free up core0 for other works
  USBHost.begin(1);
  Serial.println("done");
  core1_state = WAITING;
}

// core1's loop
void loop1() {
  USBHost.task();
  midi_host_task();
}

void handle_core1_states_and_tasks() {
  if (core1_state == WAITING) {
    uint32_t new_task;
    //Got a new task
    if (core_queue_pop(&new_task)) {
      if (core1_task == NONE) {
        if (new_task == IDENTIFY_REQUEST) {
          Serial.println("Sending identify request");
          core1_state = BUSY;
          send_sysex(whoareyou, 4);
          core1_task = IDENTIFY_REQUEST;
        } else if (new_task == EDITOR_ON_REQUEST) {
          Serial.println("Sending editor on request");
          core1_state = BUSY;
          send_sysex(editoron, 4);
          core1_task = EDITOR_ON_REQUEST;
        } else if (new_task == CURRENT_PATCH_REQUEST) {
          Serial.println("Sending current patch request");
          core1_state = BUSY;
          send_sysex(patch_download_current, 4);
          core1_task = CURRENT_PATCH_REQUEST;
        } else if (new_task == TOGGLE_EFFECT_REQUEST) {
          Serial.println("Toggling effect");
          core1_state = BUSY;
          send_sysex(toggle_effect, 13);
          core1_task = TOGGLE_EFFECT_REQUEST;
        } else if (new_task == SET_PARAM_REQUEST) {
          Serial.println("Changing param");
          core1_state = BUSY;
          send_sysex(set_param, 13);
          core1_task = SET_PARAM_REQUEST;
        }
      }
    } else {
      if (core1_task == NONE) {
        if (pc_message.status == COMPLETE) {
          Serial.println("Got patch changed");
          if (core_queue_push(CURRENT_PATCH_CHANGED)) {
            pc_message.status = EMPTY;
          }
        }
      }
    }
  } else if (core1_state == BUSY) {
    if (core1_task == IDENTIFY_REQUEST) {
      if (sysex_message.status == COMPLETE) {
        //TODO - Check if successful
        if (core_queue_push(IDENTIFY_RECEIVED)) {
          core1_task = NONE;
          core1_state = WAITING;
        }
      }
    } else if (core1_task == EDITOR_ON_REQUEST) {
      if (sysex_message.status == COMPLETE) {
        //TODO - Check if successful
        if (core_queue_push(EDITOR_ON_RECEIVED)) {
          core1_task = NONE;
          core1_state = WAITING;
        }
      }
    } else if (core1_task == CURRENT_PATCH_REQUEST) {
      if (sysex_message.status == COMPLETE) {
        //TODO - Check if successful
        if (core_queue_push(CURRENT_PATCH_RECEIVED)) {
          core1_task = NONE;
          core1_state = WAITING;
        }
      }
    } else if (core1_task == TOGGLE_EFFECT_REQUEST) {
      if (sysex_message.status == COMPLETE) {
        //TODO - Check if successful
        if (core_queue_push(TOGGLE_EFFECT_RECEIVED)) {
          core1_task = NONE;
          core1_state = WAITING;
        }
      }
    } else if (core1_task == SET_PARAM_REQUEST) {
      if (sysex_message.status == COMPLETE) {
        //TODO - Check if successful
        if (core_queue_push(SET_PARAM_RECEIVED)) {
          core1_task = NONE;
          core1_state = WAITING;
        }
      }
    }
  }
}

static void poll_midi_host_rx(void) {
  if (!device_mounted) {
    if (!midi_dev_addr) {
      return;
    }
    if (!tuh_midi_configured(midi_dev_addr)) {
      return;
    }
    if (!device_mounted) {
      tuh_descriptor_get_device(midi_dev_addr, &desc_device, 18, clone_descriptors, 0);
    }
    if (tuh_midih_get_num_rx_cables(midi_dev_addr) < 1) {
      return;
    }
  } else {
    tuh_midi_read_poll(midi_dev_addr);
    // if there is data, then the callback will be called
  }
}

static void midi_host_task(void) {
  poll_midi_host_rx();
  handle_core1_states_and_tasks();
  if (sysex_complete) {
    tuh_midi_stream_flush(midi_dev_addr);
    sysex_complete = false;
  }
}




//--------------------------------------------------------------------+
// TinyUSB Host callbacks
//--------------------------------------------------------------------+
void tuh_midi_mount_cb(uint8_t daddr, uint8_t in_ep, uint8_t out_ep, uint8_t num_cables_rx, uint16_t num_cables_tx) {
  midi_dev_addr = daddr;
  Serial.println("device connected");
}

/// Invoked when device is unmounted (bus reset/unplugged)
void tuh_umount_cb(uint8_t daddr) {
  digitalWrite(LED_BUILTIN, LOW);
  midi_dev_addr = 0;
  usb_state = DISCONNECTED;
  cloned = false;
  device_mounted = false;
  core0_state = IDLE;
  core0_task = NONE;
  core1_state = IDLE;
  core1_task = NONE;
  usb_state = DISCONNECTED;
  Serial.println("device disconnected");
}

void send_sysex(uint8_t* message, int size) {
  size += 2;
  uint8_t new_message[size];

  //Add start and end markers for sysex
  new_message[0] = 0xf0;
  for (int i = 0; i < size - 2; i++) {
    new_message[i + 1] = message[i];
  }
  new_message[size - 1] = 0xf7;

  //size += 2;
  for (int i = 0; i < size; i++) {
    Serial.printf("%x ", new_message[i]);
  }
  Serial.println("");

  int numpackets = ceil((double)size / 3.0);
  uint8_t packet[4];
  int index = 0;
  for (int i = 0; i < numpackets; i++) {
    for (int j = 0; j < 4; j++) {
      // Add CIN
      if (j == 0) {
        if (i == numpackets - 1) {
          if (size - index == 1) {
            // SysEx ends on next byte
            packet[0] == 0x05;
          } else if (size - index == 2) {
            // SysEx ends on next 2 bytes
            packet[0] == 0x06;
          } else {
            // SysEx ends on next 3 bytes
            packet[0] = 0x07;
          }
        } else {
          // SysEx packet start
          packet[0] = 0x04;
        }
      } else {
        if (index < size) {
          // SysEx data
          packet[j] = new_message[index];
        } else {
          // Fill rest with 0
          packet[j] = 0x00;
        }
        index++;
      }
    }
    //Send 4 byte packets
    tuh_midi_packet_write(midi_dev_addr, packet);
  }
  // Flag as ready to flush
  sysex_complete = true;
}

void handle_sysex_rx_cb(uint8_t* packet, uint8_t cin) {
  if (cin == 4) {
    if (sysex_message.status == EMPTY) {
      sysex_message.status = READING;
      sysex_message.size = 0;
    }
    if (packet[1] != 0xf0) {
      sysex_message.message[sysex_message.size++] = packet[1];
    }
    sysex_message.message[sysex_message.size++] = packet[2];
    sysex_message.message[sysex_message.size++] = packet[3];
  }
  if (cin == 5) {
    sysex_message.status = COMPLETE;
  }
  if (cin == 6) {
    sysex_message.message[sysex_message.size++] = packet[1];
    sysex_message.status = COMPLETE;
  }
  if (cin == 7) {
    sysex_message.message[sysex_message.size++] = packet[1];
    sysex_message.message[sysex_message.size++] = packet[2];
    sysex_message.status = COMPLETE;
  }
}

void handle_cc_rx_cb() {
  // Serial.println("CC received");
}

void handle_pc_rx_cb() {
  // Serial.println("PC received");
  pc_message.status = COMPLETE;
}

void tuh_midi_rx_cb(uint8_t dev_addr, uint32_t num_packets) {
  if (midi_dev_addr == dev_addr) {
    int i = 1;
    while (num_packets > 0) {
      --num_packets;
      uint8_t packet[4];
      uint8_t cin;
      if (tuh_midi_packet_read(dev_addr, packet)) {
        cin = packet[0];
        //SysEx message
        if (cin == 0x04 || cin == 0x05 || cin == 0x06 || cin == 0x07) {
          handle_sysex_rx_cb(packet, cin);
        } else if (cin == 0xb) {
          handle_cc_rx_cb();
        } else if (cin == 0xc) {
          handle_pc_rx_cb();
        }
      }
    }
  }
}

void tuh_midi_tx_cb(uint8_t dev_addr) {
  (void)dev_addr;
}

void clone_descriptors(tuh_xfer_t* xfer) {
  if (XFER_RESULT_SUCCESS != xfer->result) {
    return;
  }

  uint8_t const daddr = xfer->daddr;

  device_mounted = true;
  usb_state = READY;
  core1_state = WAITING;
  digitalWrite(LED_BUILTIN, HIGH);
}