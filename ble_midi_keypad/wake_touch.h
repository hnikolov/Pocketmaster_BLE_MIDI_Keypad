#ifndef _WAKE_TOUCH_H_
#define _WAKE_TOUCH_H_

// Wake up on touch ----------------------------------------------------------------------
#if CONFIG_IDF_TARGET_ESP32
#define THRESHOLD 40   // Greater the value, more the sensitivity
#elif (CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3)
#define THRESHOLD 5000 // Lower the value, more the sensitivity
#else                  // ESP32-P4 + default for other chips (to be adjusted)
#define THRESHOLD 500  // Lower the value, more the sensitivity
#endif

//touch_pad_t touchPin;
int touchPin;

// Method to print the reason by which ESP32 has been awaken from sleep
void print_wakeup_reason()
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch( wakeup_reason )
  {
    case ESP_SLEEP_WAKEUP_EXT0:     Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1:     Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER:    Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP:      Serial.println("Wakeup caused by ULP program"); break;
    default:                        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

// Method to print the touchpad by which ESP32 has been awaken from sleep
void print_wakeup_touchpad()
{
  touchPin = esp_sleep_get_touchpad_wakeup_status();

#if CONFIG_IDF_TARGET_ESP32
  switch( touchPin )
  {
    case 0:  Serial.println("Touch detected on GPIO 4");  break;
    case 1:  Serial.println("Touch detected on GPIO 0");  break;
    case 2:  Serial.println("Touch detected on GPIO 2");  break;
    case 3:  Serial.println("Touch detected on GPIO 15"); break;
    case 4:  Serial.println("Touch detected on GPIO 13"); break;
    case 5:  Serial.println("Touch detected on GPIO 12"); break;
    case 6:  Serial.println("Touch detected on GPIO 14"); break;
    case 7:  Serial.println("Touch detected on GPIO 27"); break;
    case 8:  Serial.println("Touch detected on GPIO 33"); break;
    case 9:  Serial.println("Touch detected on GPIO 32"); break;
    default: Serial.println("Wakeup not by touchpad");    break;
  }
#else
  if( touchPin < TOUCH_PAD_MAX )
  {
    Serial.printf("Touch detected on GPIO %d\n", touchPin);
  }
  else
  {
    Serial.println("Wakeup not by touchpad");
  }
#endif
}

// RTC_DATA_ATTR int bootCount = 0;

// Place the following debug code in the setup() function
// // Increment boot number and print it every reboot
// ++bootCount;
// Serial.println("Boot number: " + String(bootCount));

// //Print the wakeup reason for ESP32 and touchpad too
// print_wakeup_reason();
// print_wakeup_touchpad();

#endif // _WAKE_TOUCH_H_
