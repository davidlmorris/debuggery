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

#ifdef DEBUG_ON
unsigned long msProgCounter = 0;
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
    DEBUG_PRINTLN(F("Not using a Nano! But that is ok really, since this code will run on lots of boards."));
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
    DEBUG_PRINTLN(F("This sketch will run printing out a speedtest result of loops per second reported every 5 secs. "));
    DEBUG_PRINTLN(F("By defult this will include an average and a time. See SPEED_TEST_OPTION just above loop()."));
    DEBUG_PRINTLN();
    pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
    DEBUG_PRINTLN(F("Starting ... "));
#ifdef DEBUG_ON
    msProgCounter = millis();
#endif        
    }

// Some options, define (uncomment) ONLY ONE of these below:
// #define SPEED_TEST_OPTION (1)  // plain vanilla (and fastest)
// #define SPEED_TEST_OPTION (2)  // extended text
// #define SPEED_TEST_OPTION (3)  // including averages
#define SPEED_TEST_OPTION (4)  // Averages including a reset to the cummulative running total at the 30 sec mark.

    // the loop function runs over and over again forever, well unless we assert something false.
void loop()
    {
    static bool ledOn = true;
    static unsigned long loopTime = 0;
    static int halfSecondsCount = 0;
#ifdef DEBUG_ON    
    char progRunBuffer[255] = "";
    unsigned long ulTimeNow = millis();
    static bool b30SecCheck = true;
    static bool b60SecCheck = true;    
#endif    

    if (loopTime + 500 < millis())
        {
        loopTime = millis();
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
        halfSecondsCount++;
        }
    delay(random(0, 25)); // A fake delay so our aveages can more obviously smooth the data.

#ifdef DEBUG_ON
    debugSnSeconds(progRunBuffer,
                   254,
                   " Running continuously for ",
                   ulTimeNow / 1000);
# if SPEED_TEST_OPTION==1   
    DEBUG_SPEEDTEST(5);                     // show a 'loops per second count' every 5 seconds if DEBUG_ON is defined in "debug_conditionals.h".
# elif SPEED_TEST_OPTION==2
    DEBUG_SPEEDTEST(5, progRunBuffer);                     // show a 'loops per second count' every 5 seconds if DEBUG_ON is defined in "debug_conditionals.h".
# elif SPEED_TEST_OPTION==3
    DEBUG_SPEEDTEST(5, progRunBuffer, true, false);
# elif SPEED_TEST_OPTION==4
    if ((b30SecCheck) && (ulTimeNow > (28000 + msProgCounter)))
        {
            // After ~ 30 secs of loops (we subracted the setup time.)
            // note we keep reseting here.. which is kind of bad... but
            // the code copes anyway as it just takes the current reportLoopCount
            // as the average for the next rerport.
        if (DEBUG_SPEEDTEST(5, progRunBuffer, true, true))
            {
            DEBUG_PRINTLN("Reset Average in next loop count report.");
            b30SecCheck = false;
            }
        }
    else
        {
        if ((b60SecCheck) && (ulTimeNow > (58000 + msProgCounter)))
            {
            // After ~ minute of loops (we subracted the setup time.)
            if (DEBUG_SPEEDTEST(5, progRunBuffer, true, false))
                {
                DEBUG_PRINTLN("Average after a minute.");
                b60SecCheck = false;
                }
            }
        else
            {
            DEBUG_SPEEDTEST(5, progRunBuffer, true, false);
            }
        }
# else        
// No speed test for YOU!
# endif
#endif
    }


