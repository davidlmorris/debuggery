// Modified https://docs.arduino.cc/built-in-examples/basics/Blink/

#include "debug_conditionals.h"

#if ESP32
# ifndef LED_BUILTIN
#  define LED_BUILTIN 13 // some pin to use as some boards don't have a built in programable led.
// implementation left for the end user.
# endif
#endif

void setup()
    {
     
#ifdef DEBUG_ON
    Debuggery.initialise(true); // allowing colour 
# if ESP32
    delay(5000); // because there is no hold
# endif       
    // use Debuggery.initialise(false); if using the Arduino IDE.
    debuggeryInfo();
#endif    

    pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
#ifdef DEBUG_ON
    Debuggery.println(F("Starting ... "));
#endif    
    }

   // the loop function runs over and over again forever, well unless we assert something false.
void loop()
    {
#ifdef DEBUG_ON
    Debuggery.println(F("On"));
#endif    
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
#ifdef DEBUG_ON
    Debuggery.println(F("Off"));
#endif    
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
    debug_assert(true == false);     // Note this doesn't need a DEBUG_ON conditional to be in-active.
                                    // the actual code will have at the most a NOP but probably 
                                    // nothing depending compiler implementation of (void(0)).
    }

#ifdef DEBUG_ON
/// @brief Completely optional function showing how to use
/// Debuggery during the setup phase of the application.
void debuggeryInfo()
    {
    while (!Debuggery)
        {
        }; // Hold until the serial port is ready.
    Debuggery.progAnnounce("Blink Sketch", __FILE__);
    // For this next bit - see some clues in <debuggery.h>
#if defined(ARDUINO_AVR_NANO)
    Debuggery.setColour(92);
    Debuggery.println(F("Something to say about the Nano here."));
#else    
    Debuggery.setColour(93);
    Debuggery.println(F("WARNING: Not using a Nano! Something to say about not using a Nano here."));
#endif    
    Debuggery.setColour(92);
    Debuggery.println(F("DEBUG_ON is defined."));
    }
#endif    
