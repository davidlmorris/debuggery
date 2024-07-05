// Modified https://docs.arduino.cc/built-in-examples/basics/Blink/

#include "debug_conditionals.h"

#ifdef DEBUG_ON
# pragma message "We have DEBUG_ON defined, so DEBUG_xxx macros are working."
#else
# pragma message "We have *NOT* defined DEBUG_ON, so DEBUG_xxx macros are not included in the code."
#endif    

#if ESP32
# ifndef LED_BUILTIN
#  define LED_BUILTIN 13 // some pin to use as some boards don't have a built in programable led.
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
    Serial.println("Blink Sketch " __FILE__ " Built: " __DATE__ " " __TIME__);
#endif
    Serial.println(F("This will be printed regardless of the state of DEBUG_ON"));
    DEBUG_PROGANNOUNCE("Blink Sketch", __FILE__ " Built: " __DATE__ " " __TIME__);
    // For this next bit - see some clues in <debuggery.h>
#if defined(ARDUINO_AVR_NANO)
    DEBUG_PRINTLN(F("Something to say about the Nano here."), 92);
#else    
    DEBUG_PRINTLN(F("WARNING: Not using a Nano! Something to say about not using a Nano here."), 93);
#endif    
    DEBUG_PRINTLN(F("DEBUG_ON is defined."), 92);
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

    pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
    DEBUG_PRINTLN(F("Starting ... "));
    }


    // the loop function runs over and over again forever, well unless we assert something false.
void loop()
    {
    static unsigned long loopCount = 0;

    loopCount++;
    DEBUG_PRINTLN(F("On"));
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    DEBUG_PRINTLN(F("Off"));
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
    Serial.print("Successfully looped ");
    Serial.print(loopCount);
    Serial.println(" time(s).");
    debug_assert(true == false);// This will only trigger if DEBUG_ON is defined.
                                // the actual code will be completely ignored by GCC unless DEBUG_ON is defined
                                // See https://stackoverflow.com/questions/2198950/why-is-void-0-a-no-operation-in-c-and-c
                                // and https://stackoverflow.com/questions/25021081/what-does-the-c-precompiler-do-with-macros-defined-as-void0?rq=3.
    }


