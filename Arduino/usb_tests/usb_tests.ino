#include <MIDI.h>
// pio-usb is required for rp2040 host
#include "pio_usb.h"
#define HOST_PIN_DP 2  // Pin used as D+ for host, D- = D+ + 1

#include "Adafruit_TinyUSB.h"
#define LANGUAGE_ID 0x0409  // English
//#include "tusb_config.h"

// USB Host object
Adafruit_USBH_Host USBHost;

// holding device descriptor
tusb_desc_device_t desc_device;
static uint8_t midi_dev_addr = 0;
static bool device_configured = false;
static bool cloned = false;

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

typedef enum {
  EMPTY,
  READING,
  READY
} message_state_t;

typedef enum {
  IDLE,
  SYSEX,
  CC,
  PC
} pedal_state_t;

pedal_state_t PEDAL_STATE = IDLE;

typedef enum {
  STANDBY,
  WHOAREYOU,
  EDITORON,
  EDITOROFF,
  GETPATCH,
  //EFFECTON,
  //EFFECTOFF,
  //GETDELAYTEMPO,
  //SETDELAYTEMPO,
  //GETTEMPO
  //SETTEMPO
} pedal_tasks_t;

pedal_tasks_t todo = STANDBY;

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

// the setup function runs once when you press reset or power the board
void setup() {
  Serial1.begin(115200);
  while (!Serial1) {
  }

  pinMode(LED_BUILTIN, OUTPUT);

  Serial1.print("Start core1...");
  init_core1 = true;
}

void loop() {
  if (!device_configured) {
    Serial1.println("Initing device");
    device_configured = true;
  }
  int pos = 0;
  if (PEDAL_STATE != IDLE) {
    if (PEDAL_STATE == SYSEX) {
      if (sysex_message.status == READY) {
        Serial1.println(sysex_message.status);
        Serial1.println("SysEx");
        for (int i = 0; i < sysex_message.size; i++) {
          pos++;
          Serial1.printf("%02x ", sysex_message.message[i]);
          if (pos == 16) {
            Serial1.println("");
            pos = 0;
          }
        }
        sysex_message.status = EMPTY;
        Serial1.println("");
        Serial1.println("UNPACKED");
        unpack();
        PEDAL_STATE = IDLE;
      }
    } else if (PEDAL_STATE == CC) {
      Serial1.println("Control change");
      PEDAL_STATE = IDLE;
    } else if (PEDAL_STATE == PC) {
      Serial1.println("Program change - Request current patch");
      PEDAL_STATE = IDLE;
    }
  }
}

// core1's setup
void setup1() {
  while (!init_core1) {
    //Espera o core0 inicializar
  }
  Serial1.print("Starting host...");
  pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
  pio_cfg.pin_dp = HOST_PIN_DP;
  USBHost.configure_pio_usb(1, &pio_cfg);

  // run host stack on controller (rhport) 1
  // Note: For rp2040 pico-pio-usb, calling USBHost.begin() on core1 will have most of the
  // host bit-banging processing works done in core1 to free up core0 for other works
  USBHost.begin(1);
  Serial1.println("started");
}

static void poll_midi_host_rx(void) {
  //device must be attached and have at least one endpoint ready to receive a message
  if (!midi_dev_addr) {
    return;
  }
  if (!tuh_midi_configured(midi_dev_addr)) {
    return;
  }
  if (!cloned) {
    tuh_descriptor_get_device(midi_dev_addr, &desc_device, 18, clone_descriptors, 0);
  }
  if (tuh_midih_get_num_rx_cables(midi_dev_addr) < 1) {
    return;
  }
  tuh_midi_read_poll(midi_dev_addr);
  // if there is data, then the callback will be called
}

static void midi_host_app_task(void) {
  poll_midi_host_rx();
  if (sysex_complete) {
    tuh_midi_stream_flush(midi_dev_addr);
    sysex_complete = false;
  }
}

// core1's loop
void loop1() {
  static unsigned long last = 0;
  USBHost.task();
  //BOOTSEL function
  if (BOOTSEL && (millis() - last > 500)) {
    last = millis();
    // Do something
    uint8_t packet[] = { 0x7e, 0x00, 0x06, 0x01 };
    if (sequence == 0) {
      send_sysex(whoareyou, 4);
    } else if (sequence == 1) {
      send_sysex(editoron, 4);
    } else {
      send_sysex(patch_download_current, 4);
    }
    sequence++;
  }
  midi_host_app_task();
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
      if (j == 0) {
        if (i == numpackets - 1) {
          if (size - index == 1) {
            packet[0] == 0x05;
          } else if (size - index == 2) {
            packet[0] == 0x06;
          } else {
            packet[0] = 0x07;
          }
        } else {
          packet[0] = 0x04;
        }
      } else {
        if (index < size) {
          packet[j] = new_message[index];
        } else {
          packet[j] = 0x00;
        }
        index++;
      }
    }
    tuh_midi_packet_write(midi_dev_addr, packet);
  }
  sysex_complete = true;
}

void unpack() {
  Serial1.printf("unpacking message with size %d\r\n", sysex_message.size);
  Sysex tounpack;
  for(int i=4;i<sysex_message.size;i++){
    tounpack.message[i-4]=sysex_message.message[i];
  }
  //unpacked.size=midi::decodeSysEx(tounpack.message,unpacked.message,sysex_message.size-4);
  int index = -1;
  uint8_t hibits = 0;

  for (int i = 4; i < sysex_message.size; i++) {
    if(index!=-1) {
      //Serial1.printf("i:%d index:%d hibits:%x byte:%x", i, index, hibits, sysex_message.message[i]);
      //if(bitRead(hibits,index)){
        uint8_t b=sysex_message.message[i];
        uint8_t c;
      if(bitRead(hibits,index)==1){
        bitSet(b,7);
      } 
      unpacked.message[unpacked.size++] = b;
      index--;
    }else{
      hibits = sysex_message.message[i];
      index = 6;
    } 
  }
  Serial1.println("done");
  Serial1.println("Searching for EDTB");
  int pos=0;
  for (int i = 0; i < unpacked.size; i++) {
    if(unpacked.message[i]==0x45 &&
    unpacked.message[i+1]==0x44 &&
    unpacked.message[i+2]==0x54 &&
    unpacked.message[i+3]==0x42){
      Serial1.printf("EDTB at index %d",i);
    }
    Serial1.printf("%c ", unpacked.message[i]);
    pos++;
    if (pos == 16) {
      Serial1.println("");
      pos = 0;
    }
  }
  unpacked.size=0;
  sysex_message.size=0;
}
//--------------------------------------------------------------------+
// TinyUSB Host callbacks
//--------------------------------------------------------------------+
void tuh_midi_mount_cb(uint8_t daddr, uint8_t in_ep, uint8_t out_ep, uint8_t num_cables_rx, uint16_t num_cables_tx) {
  midi_dev_addr = daddr;
}

/// Invoked when device is unmounted (bus reset/unplugged)
void tuh_umount_cb(uint8_t daddr) {
  digitalWrite(LED_BUILTIN, LOW);
  midi_dev_addr = 0;
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
          if (cin == 4) {
            if (sysex_message.status == EMPTY) {
              sysex_message.status = READING;
            }
            if (packet[1] != 0xf0) {
              sysex_message.message[sysex_message.size++] = packet[1];
            }
            sysex_message.message[sysex_message.size++] = packet[2];
            sysex_message.message[sysex_message.size++] = packet[3];
          }
          if (cin == 5) {
            sysex_message.status = READY;
          }
          if (cin == 6) {
            sysex_message.message[sysex_message.size++] = packet[1];
            sysex_message.status = READY;
          }
          if (cin == 7) {
            sysex_message.message[sysex_message.size++] = packet[1];
            sysex_message.message[sysex_message.size++] = packet[2];
            sysex_message.status = READY;
          }
          if (sysex_message.status == READY) {
            PEDAL_STATE = SYSEX;
          }
        } else if (cin == 0xb) {
          PEDAL_STATE = CC;
        } else if (cin == 0xc) {
          PEDAL_STATE = PC;
        }
      }
    }
  }
}

void tuh_midi_tx_cb(uint8_t dev_addr) {
  (void)dev_addr;
  Serial1.printf("Flushed packets to device at addr %d\r\n", dev_addr);
}

void clone_descriptors(tuh_xfer_t* xfer) {
  if (XFER_RESULT_SUCCESS != xfer->result) {
    return;
  }

  uint8_t const daddr = xfer->daddr;
  //Set VID, PID
  TinyUSBDevice.setID(desc_device.idVendor, desc_device.idProduct);

  cloned = true;
  digitalWrite(LED_BUILTIN, HIGH);
}