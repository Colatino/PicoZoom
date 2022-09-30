#include <MIDI.h>
// pio-usb is required for rp2040 host
#include "pio_usb.h"
#define HOST_PIN_DP 2  // Pin used as D+ for host, D- = D+ + 1

#include "Adafruit_TinyUSB.h"
#define LANGUAGE_ID 0x0409  // English
// USB Host object
Adafruit_USBH_Host USBHost;

#include "g1xfour.h"

// holding device descriptor
tusb_desc_device_t desc_device;
static uint8_t midi_dev_addr = 0;
static bool cloned = false;
static bool device_mounted = false;
static bool init_core1 = false;
String manufacturer, product;

static bool sysex_complete = false;
static bool sysex_receive_complete = false;

uint8_t whoareyou[] = { 0x7e, 0x00, 0x06, 0x01 };
uint8_t editoron[] = { 0x52, 0x00, 0x6e, 0x50 };
uint8_t editoroff[] = { 0x52, 0x00, 0x6e, 0x51 };
uint8_t patch_download_current[] = { 0x52, 0x00, 0x6e, 0x29 };
uint8_t toggle_effect_on[] = { 0x52, 0x00, 0x6E, 0x64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 };
uint8_t toggle_effect_off[] = { 0x52, 0x00, 0x6E, 0x64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
int sequence = 0;

struct Patch {
  uint8_t cur_slot = 0;
  uint8_t n_effects = 0;
  Effect effects[8];
};

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
  CURRENT_PATCH_PARSED
  //EFFECT_ON_REQ,
  //EFFECT_ON_PENDING,
  //EFFECT_OFF_REQ,
  //EFFECT_OFF_PENDING,
  //GETDELAYTEMPO,
  //SETDELAYTEMPO,
  //GETTEMPO
  //SETTEMPO
} core_task_t;

core_state_t core0_state = IDLE;
core_task_t core0_task = NONE;
core_state_t core1_state = IDLE;
core_task_t core1_task = NONE;

volatile pedal_usb_state_t usb_state = DISCONNECTED;

//uint8_t sysex_message[1024];
struct Sysex {
  uint8_t message[1024];
  int size = 0;
  message_state_t status = EMPTY;
} sysex_message;

struct CChange {
  uint8_t message[2];
  message_state_t status = EMPTY;
} cc_message;

struct PChange {
  uint8_t message[3];
  message_state_t status = EMPTY;
} pc_message;

Sysex unpacked;

// HELPER FUNCTIONS
// Send a new task to the other core
// core0 <-> core1
bool queue_push(uint32_t new_task) {
  return rp2040.fifo.push_nb(new_task);
}

// Get a task from the other core
// return true on success
bool queue_pop(uint32_t* dest) {
  if (rp2040.fifo.available() > 0) {
    *dest = rp2040.fifo.pop();
    return true;
  }
  return false;
}
// CORE 0
// handles functions other than USB communications (switches, displays, data parsing...)

void handle_core0_states_and_tasks() {
  //Waiting for other core tasks to complete
  if (core0_state == WAITING) {
    uint32_t other_core;
    // check if tere is any new messages from the other core
    if (queue_pop(&other_core)) {
      // New message arrived from core1
      if (core0_task == IDENTIFY_PENDING && other_core == IDENTIFY_RECEIVED) {
        Serial1.println("Pedal identified");
        core0_state = IDLE;
        core0_task = EDITOR_ON_REQUEST;
        usb_state = IDENTIFIED;
        sysex_message.status = EMPTY;
      } else if (core0_task == EDITOR_ON_PENDING && other_core == EDITOR_ON_RECEIVED) {
        Serial1.println("Editor mode turned on");
        core0_state = IDLE;
        core0_task = CURRENT_PATCH_REQUEST;
        usb_state = EDITOR_ON;
        sysex_message.status = EMPTY;
      } else if (core0_task == CURRENT_PATCH_PENDING && other_core == CURRENT_PATCH_RECEIVED) {
        Serial1.println("Got current patch");
        core0_state = IDLE;
        core0_task = CURRENT_PATCH_UNPACK;
      }
    }
  }
  if (core0_state == IDLE) {
    if (core0_task == NONE) {
      if (usb_state == READY) {
        Serial1.println("Asking to identify");
        if (queue_push(IDENTIFY_REQUEST)) {
          core0_state = WAITING;
          core0_task = IDENTIFY_PENDING;
        }
      }
    } else if (core0_task == EDITOR_ON_REQUEST) {
      if (usb_state == IDENTIFIED) {
        Serial1.println("Turn editor on");
        if (queue_push(EDITOR_ON_REQUEST)) {
          core0_state = WAITING;
          core0_task = EDITOR_ON_PENDING;
        }
      }
    } else if (core0_task == CURRENT_PATCH_REQUEST) {
      if (usb_state == EDITOR_ON) {
        Serial1.println("Request current patch");
        if (queue_push(CURRENT_PATCH_REQUEST)) {
          core0_state = WAITING;
          core0_task = CURRENT_PATCH_PENDING;
        }
      }
    } else if (core0_task == CURRENT_PATCH_UNPACK) {
      Serial1.println("Unpacking patch data");
      core0_state = BUSY;
      unpack(4);
      core0_state = IDLE;
      core0_task = CURRENT_PATCH_PARSE;
    } else if (core0_task == CURRENT_PATCH_PARSE) {
      Serial1.println("Parsing patch data");
      core0_state = BUSY;
      parse_patch();
      core0_state = IDLE;
      core0_task = CURRENT_PATCH_PARSED;
    }
  }
}

void setup() {
  Serial1.begin(115200);
  while (!Serial1) {
  }
  pinMode(LED_BUILTIN, OUTPUT);
  Serial1.print("Start core1...");
  init_core1 = true;
  //Serial1.println(g1xfour.get_n_effects());
}

void loop() {
  static unsigned long last = 0;
  // //BOOTSEL function
  // if (BOOTSEL && (millis() - last > 500)) {
  //   if (core0_state == IDLE) {
  //     last = millis();
  //     // Do something
  //     if (sequence == 0) {
  //       send_sysex(whoareyou, 4);
  //     } else if (sequence == 1) {
  //       send_sysex(editoron, 4);
  //     } else {
  //       send_sysex(patch_download_current, 4);
  //     }
  //     sequence++;
  //   }
  // }
  handle_core0_states_and_tasks();
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
  uint8_t keyword[] = { 'P', 'T', 'C', 'F' };
  if (find_section_index(keyword) > -1) {
    //Handle patch file
    // Useful data is between EDTB and PPRM keywords
    uint8_t edtbk[] = { 'E', 'D', 'T', 'B' };
    int edtb_start = find_section_index(edtbk) + 4;
    uint8_t pprmk[] = { 'P', 'P', 'R', 'M' };
    int edtb_end = find_section_index(pprmk);
    int neff = unpacked.message[edtb_start] / 24;
    current_patch.n_effects = neff;
    for (int i = 0; i < neff; i++) {
      long uniao = unpacked.message[edtb_start + (7 + i * 24)] << 24 | unpacked.message[edtb_start + (6 + i * 24)] << 16 | unpacked.message[edtb_start + (5 + i * 24)] << 8 | unpacked.message[edtb_start + (4 + i * 24)];
      long id = (uniao >> 1) & 0xfffffff;
      int index = get_effect_by_id(id);
      if (index > -1) {
        current_patch.effects[i] = effects[index];
        Serial1.printf("Effect %s with id %d uses %d slots and has %d parameters\r\n", current_patch.effects[i].fxname, id, current_patch.effects[i].nslots, current_patch.effects[i].nparam);
      }
    }
  }
  unpacked.size = 0;
  sysex_message.size = 0;
  sysex_message.status = EMPTY;
}

int find_section_index(uint8_t* section) {
  for (int i = 0; i < unpacked.size; i++) {
    if (unpacked.message[i] == section[0] && unpacked.message[i + 1] == section[1] && unpacked.message[i + 2] == section[2] && unpacked.message[i + 3] == section[3]) {
      return i;
    }
  }
  return -1;
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
  Serial1.print("setup1...");
  pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
  pio_cfg.pin_dp = HOST_PIN_DP;
  USBHost.configure_pio_usb(1, &pio_cfg);

  // run host stack on controller (rhport) 1
  // Note: For rp2040 pico-pio-usb, calling USBHost.begin() on core1 will have most of the
  // host bit-banging processing works done in core1 to free up core0 for other works
  USBHost.begin(1);
  Serial1.println("done");
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
    if (queue_pop(&new_task)) {
      if (core1_task == NONE) {
        if (new_task == IDENTIFY_REQUEST) {
          Serial1.println("Sending identify request");
          core1_state = BUSY;
          send_sysex(whoareyou, 4);
          core1_task = IDENTIFY_REQUEST;
        } else if (new_task == EDITOR_ON_REQUEST) {
          Serial1.println("Sending editor on request");
          core1_state = BUSY;
          send_sysex(editoron, 4);
          core1_task = EDITOR_ON_REQUEST;
        } else if (new_task == CURRENT_PATCH_REQUEST) {
          Serial1.println("Sending current patch request");
          core1_state = BUSY;
          send_sysex(patch_download_current, 4);
          core1_task = CURRENT_PATCH_REQUEST;
        }
      }
    }
  } else if (core1_state == BUSY) {
    if (core1_task == IDENTIFY_REQUEST) {
      if (sysex_message.status == COMPLETE) {
        //TODO - Check if successful
        if (queue_push(IDENTIFY_RECEIVED)) {
          core1_task = NONE;
          core1_state = WAITING;
        }
      }
    } else if (core1_task == EDITOR_ON_REQUEST) {
      if (sysex_message.status == COMPLETE) {
        //TODO - Check if successful
        if (queue_push(EDITOR_ON_RECEIVED)) {
          core1_task = NONE;
          core1_state = WAITING;
        }
      }
    } else if (core1_task == CURRENT_PATCH_REQUEST) {
      if (sysex_message.status == COMPLETE) {
        //TODO - Check if successful
        if (queue_push(CURRENT_PATCH_RECEIVED)) {
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
    Serial1.printf("%x ", new_message[i]);
  }
  Serial1.println("");

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


//--------------------------------------------------------------------+
// TinyUSB Host callbacks
//--------------------------------------------------------------------+
void tuh_midi_mount_cb(uint8_t daddr, uint8_t in_ep, uint8_t out_ep, uint8_t num_cables_rx, uint16_t num_cables_tx) {
  midi_dev_addr = daddr;
  Serial1.println("device connected");
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
  Serial1.println("device disconnected");
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
  Serial1.println("CC received");
}

void handle_pc_rx_cb() {
  Serial1.println("PC received");
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
  //Set VID, PID
  TinyUSBDevice.setID(desc_device.idVendor, desc_device.idProduct);

  device_mounted = true;
  usb_state = READY;
  core1_state = WAITING;
  digitalWrite(LED_BUILTIN, HIGH);
}