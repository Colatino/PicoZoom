// USB Host object
// pio-usb is required for rp2040 host
#include "pio_usb.h"
#define HOST_PIN_DP 2  // Pin used as D+ for host, D- = D+ + 1
#include "Adafruit_TinyUSB.h"
#define LANGUAGE_ID 0x0409  // English
Adafruit_USBH_Host USBHost;

// Current pedal
#include "g1xfour.h"

// OLED displays
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 32     // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int oled_bus []={0,1,2,3,4}; // Buses on the TCA9548a

#define NUM_PEDALS 5
int switch_pins[]={11,12,13,14,15};

struct FootSwitch{
  int pin;
  volatile int cur_state;
  int last_state;
  int last_time;  
};

FootSwitch footswitch[NUM_PEDALS];

// holding device descriptor
tusb_desc_device_t desc_device;
static uint8_t midi_dev_addr = 0;
static bool device_configured = false;
static bool cloned = false;

static bool init_core1 = false;
String manufacturer, product;

// Set active display
void set_bus(uint8_t bus) {
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

// Core0 handles OLEDs, SPSTs (interrupts),
void setup() {
  // Set led
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);

  //Set I2C pins and initialize
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin();
  
  // Initialize display object
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {    
    for (;;)
      ;  // Don't proceed, loop forever
  }  
  
  // Clear all displays
  for(int i=0;i<NUM_PEDALS;i++){
    // Set active display
    set_bus(oled_bus[i]);
    // Clear the buffer
    display.clearDisplay();
    // Print buffer
    display.display();
  }   

  // Set Pins and ISRs
  for(int i=0;i<NUM_PEDALS;i++){
    footswitch[i].pin=switch_pins[i];
    footswitch[i].cur_state=HIGH;
    footswitch[i].last_state=HIGH;
    footswitch[i].last_time=0;    
    pinMode(footswitch[i].pin,INPUT_PULLUP);        
    attachInterrupt(digitalPinToInterrupt(footswitch[i].pin),switch_action_isr,RISING);
  }

  init_core1 = true;
}

void switch_action_isr(){
}

void loop() {
  if (!device_configured) {
    //Serial1.println("Initing device");
    usb_midi.begin();
    device_configured = true;
  }
  if (midi_dev_addr && device_configured) {
    //Clone stream
    uint8_t packet[4];
    if (usb_midi.readPacket(packet)) {
      //Serial1.printf("Packet received from pc: %x %x %x %x\r\n",packet[0],packet[1],packet[2],packet[3]);
      tuh_midi_packet_write(midi_dev_addr, packet);
    }
  }
}

// core1 handles USB Host stack and communications
void setup1() {
  //Hold untill core0 is initialized
  while (!init_core1) {
    delay(1);
  }  
  // PIO USB configuration  
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
  // Always run task
  USBHost.task();  
  midi_host_app_task();
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
    //Serial1.printf("Got %d packets from device at addr %d\r\n",num_packets,dev_addr);
    int i = 1;
    while (num_packets > 0) {
      --num_packets;
      uint8_t packet[4];
      if (tuh_midi_packet_read(dev_addr, packet)) {
        usb_midi.writePacket(packet);
        //Serial1.printf("Packet %d: %x %x %x %x - sent to PC\r\n",i++,packet[0],packet[1],packet[2],packet[3]);
      }
    }
  }
}

void tuh_midi_tx_cb(uint8_t dev_addr) {
  (void)dev_addr;
  //Serial1.printf("Flushed packets to device at addr %d\r\n",dev_addr);
}

void clone_descriptors(tuh_xfer_t *xfer) {
  if (XFER_RESULT_SUCCESS != xfer->result) {
    return;
  }

  uint8_t const daddr = xfer->daddr;
  //Set VID, PID
  TinyUSBDevice.setID(desc_device.idVendor, desc_device.idProduct);

  cloned = true;
  digitalWrite(LED_BUILTIN, HIGH);
}

