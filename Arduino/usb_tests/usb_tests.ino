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

uint8_t whoareyou[] = { 0x7e, 0x00, 0x06, 0x01 };
uint8_t editoron[] = { 0x52, 0x00, 0x6e, 0x50 };
uint8_t editoroff[] = { 0x52, 0x00, 0x6e, 0x51 };
uint8_t patch_download_current[] = { 0x52, 0x00, 0x6e, 0x29 };
uint8_t toggle_effect_on[] = { 0x52, 0x00, 0x6E, 0x64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 };
uint8_t toggle_effect_off[] = { 0x52, 0x00, 0x6E, 0x64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
int sequence = 0;

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
}

// core1's setup
void setup1() {
  while (!init_core1) {
    //Espera o core0 inicializar
  }
  Serial1.println("started");
  pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
  pio_cfg.pin_dp = HOST_PIN_DP;
  USBHost.configure_pio_usb(1, &pio_cfg);

  // run host stack on controller (rhport) 1
  // Note: For rp2040 pico-pio-usb, calling USBHost.begin() on core1 will have most of the
  // host bit-banging processing works done in core1 to free up core0 for other works
  USBHost.begin(1);
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
  tuh_midi_stream_flush(midi_dev_addr);
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
      if (sequence % 2 == 0) {
        send_sysex(toggle_effect_on, 13);
      } else {
        send_sysex(toggle_effect_off, 13);
      }
    }
    sequence++;
    Serial1.println("Sending sysex");
  }
  midi_host_app_task();
}

void send_sysex(uint8_t* message, int size) {
  size += 2;
  uint8_t new_message[size];
  Serial1.println(size);
  Serial1.println(sizeof(new_message) / sizeof(uint8_t));
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
  Serial1.println("fim");

  int numpackets = ceil((double)size / 3.0);
  Serial1.println(numpackets);
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
    Serial1.printf("%x %x %x %x\r\n", packet[0], packet[1], packet[2], packet[3]);
    tuh_midi_packet_write(midi_dev_addr, packet);
  }
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

//tuh_configuration_set(uint8_t daddr, uint8_t config_num, tuh_xfer_cb_t complete_cb, uintptr_t user_data)
void tuh_midi_rx_cb(uint8_t dev_addr, uint32_t num_packets) {
  if (midi_dev_addr == dev_addr) {
    Serial1.printf("Got %d packets from device at addr %d\r\n", num_packets, dev_addr);
    int i = 1;
    while (num_packets > 0) {
      --num_packets;
      uint8_t packet[4];
      if (tuh_midi_packet_read(dev_addr, packet)) {
        Serial1.printf("Packet %d contents: %x %x %x %x\r\n", i++, packet[0], packet[1], packet[2], packet[3]);
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