    // The non-blocking version of the blink sketch.
#include "debug_conditionals.h"

#ifdef DEBUG_ON
# pragma message "We have DEBUG_ON defined, so DEBUG_xxx macros are working."
#else
# pragma message "We have *NOT* defined DEBUG_ON, so DEBUG_xxx macros are not included in the code."
#endif    

#if ESP32
# ifndef LED_BUILTIN
#  define LED_BUILTIN 13 // some pin to use as some boards don't have a built in programmable led.
// implementation left for the end user.
# endif
#endif

void setup()
    {
    Serial.begin(115200);
    while (!Serial)
        {
        }; // Hold until the serial port is ready.
#if ESP32
    delay(5000); // because there is no hold
#endif

    Serial.println("Setting up... ");
    DEBUG_INITIALISE(true, 115200); // allowing colour and making sure 
    // we are at the same speed as the previous serial begin.
#ifdef DEBUG_ON
    while (!DEBUG_DEBUGGERY)
        {
        }; // Hold until the serial port is ready.
#endif 
    // use Debuggery.initialise(false); if using the Arduino IDE.
#ifndef DEBUG_ON        
    Serial.println(F("Blink Sketch " __FILE__ " Built: " __DATE__ " " __TIME__));
#endif
    Serial.println(F("This will be printed regardless of the state of DEBUG_ON"));
    DEBUG_PROGANNOUNCE("Blink Sketch", __FILE__ " Built: " __DATE__ " " __TIME__);
    // For this next bit - see some clues in <debuggery.h>
#if defined(ARDUINO_AVR_NANO)
    DEBUG_SETCOLOUR(92);
    DEBUG_PRINTLN(F("Something to say about the Nano here."));
#else    
    DEBUG_SETCOLOUR(93);
    DEBUG_PRINTLN(F("WARNING: Not using a Nano! Something to say about not using a Nano here."));
#endif    
    DEBUG_SETCOLOUR(92);
    DEBUG_PRINTLN(F("DEBUG_ON is defined."));
    DEBUG_RESETCOLOUR();
    DEBUG_PRINTLN(F("Now some ordinary coloured text."));
    DEBUG_SETCOLOUR(92);
    DEBUG_PRINTLN(F("Now some coloured text."));
    DEBUG_SETCOLOUR(93);
    DEBUG_PRINTLN(F("Now some more coloured text."));
    DEBUG_SETCOLOUR(94);
    DEBUG_PRINTLN(F("Now some even more coloured text."));
    DEBUG_PRINTLN(F("And now the number 127 in various forms."));
    DEBUG_PRINTLN(127);
    DEBUG_PRINTLN(127, HEX);
    DEBUG_PRINTLN(127, BIN);
    DEBUG_PRINTLN(F("And floating point variations."));
    DEBUG_PRINTLN(1234.567897, 5);
    DEBUG_PRINTLN(1234.567897, 4);
    DEBUG_PRINTLN(1234.567897, 2);
    DEBUG_PRINTLN(1234.567897, 1);
    DEBUG_PRINTLN(1234.567897, 0);
    DEBUG_RESETCOLOUR();
    DEBUG_PRINTLN(F("And now back to the default colours."));
    DEBUG_PRINTLN();
    DEBUG_PRINTLN(F("This sketch will run for a about a minute, and then assert "));
    DEBUG_PRINTLN(F(" that the 'halfSecondsCount' is no longer less than 120."));
    DEBUG_PRINTLN();
    pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
    DEBUG_PRINTLN(F("Starting ... "));
    }




    // the loop function runs over and over again forever, well unless we assert something false.
void loop()
    {
    static bool ledOn = true;        
    static unsigned long loopTime = 0;
    static int halfSecondsCount = 0;

    if (loopTime + 500 < millis())
        {
         loopTime =    millis();
         digitalWrite(LED_BUILTIN, ledOn);
         ledOn = !ledOn;
         halfSecondsCount++;
        }
    DEBUG_ASSERT(halfSecondsCount < 120);   // This will assert at about a minute if DEBUG_ON is defined in "debug_conditionals.h".
    DEBUG_SPEEDTEST(5);                     // show a 'loops per second count' every 5 seconds if DEBUG_ON is defined in "debug_conditionals.h".
    }


