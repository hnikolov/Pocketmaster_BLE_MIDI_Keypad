#include <Arduino.h>
#include "wake_touch.h"
#include "midi_commands.h"
#include "touch_buttons.h"

// WS2812 LED Pixel ----------------------------------------------------------------------
#include <driver/rtc_io.h> // To be able to completely switch-off the simple red LED
#include <FastLED.h>

#define NUM_LEDS 1
#define DATA_PIN 48

CRGB leds[NUM_LEDS];
// ---------------- ----------------------------------------------------------------------

void go_to_sleep()
{
  FastLED.setBrightness(0);
  leds[0] = CRGB::Black;
  FastLED.show();

  digitalWrite(DATA_PIN, LOW);         // To completely
  delay(10);                           // switch-off the
  gpio_deep_sleep_hold_en();           // red LED
  gpio_hold_en((gpio_num_t) DATA_PIN); // during deep sleep

  Serial.println("Going to sleep now");
  esp_deep_sleep_start();
}

bool touch1detected = false;
void gotTouch1() { touch1detected = true; }

uint8_t i = 0;

uint32_t tick1 = millis();
uint32_t tick2 = millis();
uint32_t tick3 = millis();

void tick_timing()
{
  if( millis() - tick1 > 100 ) // Go to sleep check
  {
    if( touch1detected )
    {
      touch1detected = false;
      if( touchInterruptGetLastStatus(T8) ) { Serial.println(" --- T8 Touched"); }
      else                                  { go_to_sleep(); } // Serial.println(" --- T8 Released"); 
    }
    tick1 = millis(); // Start new waiting period
	}

  // // TODO: Should be replaced by handling buttons pressed
  // if( millis() - tick2 > 1000 ) // Test: send MIDI periodically
  // {
  //   if( BLEMidiClient.isConnected() )
  //   {
  //     leds[0] = CRGB::DarkBlue;
  //     FastLED.show();

  //     Serial.println("Sending a MIDI command");
  //     midi_commands[i++]();
  //     if( i == 36 ) { i = 0; }

  //     delay(20);
  //     leds[0] = CRGB::Black;
  //     FastLED.show();      
  //   }    
  //   tick2 = millis(); // Start new waiting period
  // }

	if( millis() - tick3 > 3000 )
	{
    if( !BLEMidiClient.isConnected() )
    {
      leds[0] = CRGB::DarkBlue;
      FastLED.show();

      // If we are not already connected, we try te connect to the first BLE Midi device we find
      int nDevices = BLEMidiClient.scan();
      
      leds[0] = CRGB::Black;
      FastLED.show();

      if( nDevices > 0 ) // Then connect to the first found BLE MIDI device
      {
        if(BLEMidiClient.connect(0)) { Serial.println("Connection established"); }
        else                         { Serial.println("Connection failed");      }
      }
    }    
    tick3 = millis(); // Start new waiting period
	}
}


void setup()
{
  Serial.begin(115200);
  delay(1000); // Take some time to open up the Serial Monitor

  Serial.println("Initializing sleep/wake up...");
  touchSleepWakeUpEnable(T8, THRESHOLD);
  gpio_hold_dis((gpio_num_t) DATA_PIN); // To enable the LED pin after deep sleep

  Serial.println("Initializing ESP32 Touch Interrupt for going to sleep");
  touchAttachInterrupt(T8, gotTouch1, THRESHOLD);

  Serial.println("Initializing WS2812 LED...");
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS).setRgbw(RgbwDefault());
  FastLED.setBrightness(8);

  Serial.println("Initializing bluetooth...");
  BLEMidiClient.begin("Midi client"); // "Midi client" is the name you want to give to the ESP32
  // BLEMidiClient.enableDebugging(); // Uncomment to see debugging messages from the library

  Serial.println("Initializing touch boutons"); 
  init_touch_buttons();

  Serial.println("Starting the main loop...");
}

void loop()
{
  tick_timing();
  update_touch_buttons();
  delay(30);
}
