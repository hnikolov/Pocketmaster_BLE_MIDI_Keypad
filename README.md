# Pocketmaster_BLE_MIDI_Keypad
Simple keypad to control Sonicake Pocketmaster multi effect processor via BLE MIDI

**HARDWARE USED**
- ESP32-S3 Super Mini
- Capacitive touch keypad 3x4 MPR121
- LiPo Battery, 3.7V

**LIBRARIES USED**
- ESP32-BLE-MIDI    (https://github.com/max22-/ESP32-BLE-MIDI)
- r89m Buttons      (https://github.com/r89m/Button)
- r89m MPR121Button (https://github.com/r89m/MPR121Button)
- Adafruit_MPR121.h (https://github.com/adafruit/Adafruit_MPR121_Library)
- FastLED           (https://github.com/FastLED/FastLED)
- <driver/rtc_io.h> (To be able to completely switch-off the simple red LED on the Super Mini board during deep sleep)

**DESCRIPTION**
<br>Uses a capacitive pin of the ESP32 board to wake-up and go to deep sleep. After wake-up, BLE MIDI is initialized and start scanning for compatible devices. This is indicated by a blue LED slowly flashing. The keypad connects to the first found BLE MIDI device. After connecting, the blue LED is off and you can use the 12 capacitive pads to control various features of Pocketmaster, refer to the table below.

| Button | Action  | Function                                      |
|--------|---------|-----------------------------------------------|
|    0   | Release | On/Off Reverb                                 |
|        | Hold    | On/Off IR                                     |
|    1   | Release | On/Off Delay                                  |
|        | Hold    | On/Off Drive                                  |
|    2   | Release | On/Off FX2                                    |
|        | Hold    | On/Off FX1                                    |
|    3   | Release | On/Off EQ                                     |
|        | Hold    | On/Off NR                                     |
|    4   | Release | Select next metronome rhythm                  |
|        | Hold    | Select previous metronome rhythm continuously |
|    5   | Release | Metronome Start/Stop                          |
|        | Hold    | On/Off Metronome menu                         |
|    6   | Release | Looper Stop                                   |
|        | Hold    | Looper delete                                 |
|    7   | Release | Looper Rec/Play                               |
|        | Hold    | On/Off Looper menu                            |
|    8   | Press   | Increase volume by 1 (master, looper, drum) * |
|        | Hold    | Increase volume continuously *                |
|    9   | Press   | Decrease volume by 1 (master, looper, drum) * |
|        | Hold    | Decrease volume continuously *                |
|   10   | Press   | Select next preset                            |
|        | Hold    | Select next preset continuously               |
|   11   | Press   | Select previous preset                        |
|        | Hold    | Select previous preset continuously           |

<br>* Deafault volume is master volume.
<br>* In case the metronome menu is selected, then the metronome volume is changed.
<br>* In case the looper menu is selected, then the looper playback is changed.
