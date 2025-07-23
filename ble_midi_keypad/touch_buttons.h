#ifndef _TOUCH_BUTTONS_H_
#define _TOUCH_BUTTONS_H_

#include <Button.h>
#include <ButtonEventCallback.h>
#include <MPR121Button.h>
#include <Adafruit_MPR121.h> // https://github.com/adafruit/Adafruit_MPR121_Library
#include <Wire.h>

#import "midi_commands.h"

// Attach the MPR121's IRQ pin to digital pin 11
const int PIN_TOUCH_IRQ = 11;

#define I2C_SDA 13
#define I2C_SCL 12

TwoWire I2CMPR121 = TwoWire(0);

// Create an instance of Adafruit_MPR121 to communicate with your IC via i2C
Adafruit_MPR121 touchSensor = Adafruit_MPR121();

// Create a few instances of MPRButton reading electrodes 1, 2 and 3
MPR121Button b00 = MPR121Button(touchSensor,  0);
MPR121Button b01 = MPR121Button(touchSensor,  1);
MPR121Button b02 = MPR121Button(touchSensor,  2);
MPR121Button b03 = MPR121Button(touchSensor,  3);
MPR121Button b04 = MPR121Button(touchSensor,  4);
MPR121Button b05 = MPR121Button(touchSensor,  5);
MPR121Button b06 = MPR121Button(touchSensor,  6);
MPR121Button b07 = MPR121Button(touchSensor,  7);
MPR121Button b08 = MPR121Button(touchSensor,  8);
MPR121Button b09 = MPR121Button(touchSensor,  9);
MPR121Button b10 = MPR121Button(touchSensor, 10);
MPR121Button b11 = MPR121Button(touchSensor, 11);

// Button handlers for midi commands --------------------------------------------
void onBP08(Button& btn) { vol_upd(+1); }
void onBP09(Button& btn) { vol_upd(-1); }
void onBP10(Button& btn) { preset_inc(); }
void onBP11(Button& btn) { preset_dec(); }

void onBR00(Button& btn, uint16_t duration) { if( duration < 300 ) { reverb_tgl(); }}
void onBR01(Button& btn, uint16_t duration) { if( duration < 300 ) { delay_tgl(); }}
void onBR02(Button& btn, uint16_t duration) { if( duration < 300 ) { fx2_tgl(); }}
void onBR03(Button& btn, uint16_t duration) { if( duration < 300 ) { eq_tgl(); }}
void onBR04(Button& btn, uint16_t duration) { if( duration < 300 ) { rhythm_next(); }}
void onBR05(Button& btn, uint16_t duration) { if( duration < 300 ) { drum_p_s(); }}
void onBR06(Button& btn, uint16_t duration) { if( duration < 300 ) { looper_stop(); p_lpr = true; }}
void onBR07(Button& btn, uint16_t duration) { if( duration < 300 ) { looper_r_p(); }}
//void onBR08(Button& btn, uint16_t duration) { bank_inc(); }
//void onBR09(Button& btn, uint16_t duration) { bank_dec(); }

void onBH00(Button& btn, uint16_t duration) { ir_tgl(); }
void onBH01(Button& btn, uint16_t duration) { drive_tgl(); }
void onBH02(Button& btn, uint16_t duration) { fx1_tgl(); }
void onBH03(Button& btn, uint16_t duration) { nr_tgl(); }
void onBH05(Button& btn, uint16_t duration) { drum_tgl(); }
void onBH06(Button& btn, uint16_t duration) { looper_del(); p_lpr = false; }
void onBH07(Button& btn, uint16_t duration) { looper_tgl(); }

void onBHR04(Button& btn, uint16_t duration, uint16_t repeatCount) { rhythm_prev(); }
void onBHR08(Button& btn, uint16_t duration, uint16_t repeatCount) { vol_upd(+1); }
void onBHR09(Button& btn, uint16_t duration, uint16_t repeatCount) { vol_upd(-1); }
void onBHR10(Button& btn, uint16_t duration, uint16_t repeatCount) { preset_inc(); }
void onBHR11(Button& btn, uint16_t duration, uint16_t repeatCount) { preset_dec(); }

// ------------------------------------------------------------------------------
void init_touch_buttons()
{
  // Initialise the touch sensor
  I2CMPR121.begin(I2C_SDA, I2C_SCL, 100000);
  touchSensor.begin(0x5A, &I2CMPR121);  


  // When electrode 1 is first pressed, call the function onButtonPressed (further down the page)
  b08.onPress(onBP08);
  b09.onPress(onBP09);
  b10.onPress(onBP10);
  b11.onPress(onBP11);

  b00.onHold(300, onBH00);
  b01.onHold(300, onBH01);
  b02.onHold(300, onBH02);
  b03.onHold(300, onBH03);
  b05.onHold(350, onBH05);
  b06.onHold(350, onBH06);
  b07.onHold(450, onBH07);

  // Once electode 2 has been held for 1 second (1000ms) call onButtonHeld. Call it again every 0.5s (500ms) until it is let go
  b04.onHoldRepeat(350, 350, onBHR04);
  b08.onHoldRepeat(200, 100, onBHR08);
  b09.onHoldRepeat(200, 100, onBHR09);
  b10.onHoldRepeat(500, 200, onBHR10);
  b11.onHoldRepeat(500, 200, onBHR11);

  // When electrode 3 is released, call onButtonReleased
  b00.onRelease(onBR00);
  b01.onRelease(onBR01);
  b02.onRelease(onBR02);
  b03.onRelease(onBR03);
  b04.onRelease(onBR04);
  b05.onRelease(onBR05);
  b06.onRelease(onBR06);
  b07.onRelease(onBR07);
//  b08.onRelease(onBR08);
//  b09.onRelease(onBR09);
}

void update_touch_buttons()
{
  // Check the state of the button
  // Check the IRQ line - if it is LOW that Touch Sensor IC has new data for us
  if( digitalRead(PIN_TOUCH_IRQ) == LOW )
  {
    // Get the latest touch readings from the sensor. Do this here means we only call .touched() once instead of 3 times
    int latestTouchReading = touchSensor.touched();
    // if( latestTouchReading != 0 ) { Serial.println(latestTouchReading); }
    b00.update(latestTouchReading);
    b01.update(latestTouchReading);
    b02.update(latestTouchReading);
    b03.update(latestTouchReading);
    b04.update(latestTouchReading);
    b05.update(latestTouchReading);
    b06.update(latestTouchReading);
    b07.update(latestTouchReading);
    b08.update(latestTouchReading);
    b09.update(latestTouchReading);
    b10.update(latestTouchReading);
    b11.update(latestTouchReading);
  }
}

#endif // _TOUCH_BUTTONS_H_
