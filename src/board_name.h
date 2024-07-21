#ifndef board_name_h
# define board_name_h
# include <Arduino.h>

// This BOARD_NAME ID modified from:
// https://arduino.stackexchange.com/questions/21137/arduino-how-to-get-the-BOARD_NAME-type-in-code
// answer by @Elmue.

#  if defined(TEENSYDUINO)
    //  --------------- Teensy -----------------
#   if defined(__AVR_ATmega32U4__)
#    define BOARD_NAME F("Teensy 2.0")
#   elif defined(__AVR_AT90USB1286__)
#    define BOARD_NAME F("Teensy++ 2.0")
#   elif defined(__MK20DX128__)
#    define BOARD_NAME F("Teensy 3.0")
#   elif defined(__MK20DX256__)
#    define BOARD_NAME F("Teensy 3.2") // and Teensy 3.1 (obsolete)
#   elif defined(__MKL26Z64__)
#    define BOARD_NAME F("Teensy LC")
#   elif defined(__MK64FX512__)
#    define BOARD_NAME F("Teensy 3.5")
#   elif defined(__MK66FX1M0__)
#    define BOARD_NAME F("Teensy 3.6")
#   elif defined(__IMXRT1062__) && defined(ARDUINO_TEENSY40)
#    define BOARD_NAME F("Teensy 4.0")
#   elif defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41)
#    define BOARD_NAME F("Teensy 4.1")
#   else
#    error "Unknown TEENSYDUINO BOARD_NAME"
#   endif
#  elif defined(ESP_PLATFORM)
#   if defined(ESP8266) // Don't have one to test - a guess that probably works
#    define BOARD_NAME F("ESP8266")
#   elif defined(ESP32)
#    if defined(ARDUINO_VARIANT)
#     define BOARD_NAME F("Esp32 " ARDUINO_VARIANT) // Will likely hold the actual board name.
#    elif defined(ARDUINO_BOARD)
#     define BOARD_NAME F("Esp32 " ARDUINO_BOARD)
#    else
#     define BOARD_NAME F("Esp32 (unknown board)")
#    endif
#   elif defined(ESP32S3)
#    define BOARD_NAME F("Esp32 S3")
#   else
// Need to fill in some gaps here.
#    error "Unknown ESP_PLATFORM BOARD_NAME"
#   endif
#  else // --------------- Arduino and others ------------------
#   if defined(ARDUINO_AVR_ADK)
#    define BOARD_NAME F("Arduino AVR Mega Adk")
#   elif defined(ARDUINO_AVR_BT)    // Bluetooth
#    define BOARD_NAME F("Arduino AVR Bt")
#   elif defined(ARDUINO_AVR_DUEMILANOVE)
#    define BOARD_NAME F("Arduino AVR Duemilanove")
#   elif defined(ARDUINO_AVR_ESPLORA)
#    define BOARD_NAME F("Arduino AVR Esplora")
#   elif defined(ARDUINO_AVR_ETHERNET)
#     define BOARD_NAME F("Arduino AVR Ethernet")
#   elif defined(ARDUINO_AVR_FIO)
#    define BOARD_NAME F("Arduino AVR Fio")
#   elif defined(ARDUINO_AVR_GEMMA)
#    define BOARD_NAME F("Arduino AVR Gemma")
#   elif defined(ARDUINO_AVR_LEONARDO)
#    define BOARD_NAME F("Arduino AVR Leonardo")
#   elif defined(ARDUINO_AVR_LILYPAD)
#    define BOARD_NAME F("Arduino AVR Lilypad")
#   elif defined(ARDUINO_AVR_LILYPAD_USB)
#    define BOARD_NAME F("Arduino AVR Lilypad Usb")
#   elif defined(ARDUINO_AVR_MEGA)
#    define BOARD_NAME F("Arduino AVR Mega")
#   elif defined(ARDUINO_AVR_MEGA2560)
#    define BOARD_NAME F("Arduino AVR Mega 2560")
#   elif defined(ARDUINO_AVR_MICRO)
#    define BOARD_NAME F("Arduino AVR Micro")
#   elif defined(ARDUINO_AVR_MINI)
#   define BOARD_NAME F("Arduino AVR Mini")
#   elif defined(ARDUINO_AVR_NANO)
#    define BOARD_NAME F("Arduino AVR Nano")
#   elif defined(ARDUINO_AVR_NG)
#    define BOARD_NAME F("Arduino AVR NG")
#   elif defined(ARDUINO_AVR_PRO)
#   define BOARD_NAME F("Arduino AVR Pro")
#   elif defined(ARDUINO_AVR_ROBOT_CONTROL)
#    define BOARD_NAME F("Arduino AVR Robot Ctrl")
#   elif defined(ARDUINO_AVR_ROBOT_MOTOR)
#    define BOARD_NAME F("Arduino AVR Robot Motor")
#   elif defined(ARDUINO_AVR_UNO)
#    define BOARD_NAME F("Arduino AVR Uno")
#   elif defined(ARDUINO_AVR_YUN)
#    define BOARD_NAME F("Arduino AVR Yun")

// These BOARD_NAMEs must be installed separately:
#   elif defined(ARDUINO_SAM_DUE)
#    define BOARD_NAME F("Arduino AVR Due")
#   elif defined(ARDUINO_SAMD_ZERO)
#    define BOARD_NAME F("Arduino AVR Zero")
#   elif defined(ARDUINO_ARC32_TOOLS)
#    define BOARD_NAME F("Arduino AVR 101")

// SparkFun BOARD_NAMEs (installed separately) :
#   elif defined(AVR_PROMICRO)
#    define BOARD_NAME F("SparkFun Pro Micro")
#   elif defined(ARDUINO_AVR_PROMICRO8)
#    define BOARD_NAME F("SparkFun Pro Micro (8mhz)")
#   elif defined(ARDUINO_AVR_PROMICRO16)
#    define BOARD_NAME F("SparkFun Pro Micro (16mhz)")
#   elif defined(AVR_FIOV3)
#    define BOARD_NAME F("SparkFun Fio v3")
#   elif defined(AVR_MAKEYMAKEY)
#    define BOARD_NAME F("SparkFun MaKey MaKey")
#   elif defined(AVR_QDUINOMINI)
#    define BOARD_NAME F("Qtechknow Qduino Mini")
#   elif defined(AVR_LILYPAD_ARDUINO_USB_PLUS_BOARD_NAME)
#    define BOARD_NAME F("LilyPad USB Plus")

//  My 'slacky hacky' (installed separately) SparkFun Pro Micro modification:
//  SparkFun Pro Micro USB descriptor modifications
//  cf https://www.wronex.com/articles/220211-pro-micro-usb-name/
// use for a Mixxx Midi Controller.
#   elif defined(ARDUINO_AVR_PROMICRO)
#    define BOARD_NAME F("Radio Laneway Pro Micro")
#   else
#    error "Unknown BOARD_NAME"
#   endif
#  endif

#endif
