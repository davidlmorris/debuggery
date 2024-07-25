// Very heavily modified https://docs.arduino.cc/built-in-examples/basics/Blink/ !

#include "debug_conditionals.h"
#ifdef ARDUINO_ARCH_AVR
// Esp32 has its own modified version included in the main libs.
// (Which you are probably using since FreeRTOS on an nano et al is 
// likely to run into memory issues on any sizable project)
# include <Arduino_FreeRTOS.h>
# include <semphr.h>
#endif

/*
This example shows how to use the DEBUG macros in a multitasking environment with FreeRTOS.  Make sure 
you download the FreeRTOS library and install (easiest and best using the Arduino IDE.)

Here we need to surround the DEBUG_PRINT statements with a semaphore to stop both trying to access
the serial port at the same time to avoid confusion and potential catastrophe.

We create two tasks that run in the background after being started in setup). Nothing
happens in loop().  If we were to add code to loop() we would still need to use the semaphore to
avoid contention with the task if we print to the serial port.

The first task (TaskBlink) will blink the Led as usual in a link sketch turning it on and off 
twice a second, and at the same time printing * in yellow when on and _ in read when off.

The second task (imaginatively named TaskSecond) prints the number of seconds since the task 
started every 5 seconds.

The output (when DEBUG_ON is set) should look something like:
* 0 _*_*_*_*_*_*_*_*_ 5 *_*_*_*_*_*_*_*_*_ 10 *_*_*_*_*_*_*_*_* 15 _*_*_*_*_*_*_*_*_* 20 

Never use the (any) serial port print routines (like Debuggery) from inside an ISR, always set an ISR 
to start or continue a task.  

Note that in this simple example we have used portMAX_DELAY.  In reality you would go for something
 a whole lot smaller like 'xTickFullSec' (supplied) at the risk of missing some entries, but only blocking 
 for a max of a second.
*/


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


const unsigned long xTickATinyBit = (50 / portTICK_PERIOD_MS);
const unsigned long xTickFullSec = (1000 / portTICK_PERIOD_MS);

SemaphoreHandle_t xMutexSemaphoreSerialPort = NULL;

void initSemaphore(void)
    {
    xMutexSemaphoreSerialPort = xSemaphoreCreateMutex();
    }

bool takeSemaphore(void)
    {
    if (xSemaphoreTake(xMutexSemaphoreSerialPort, (TickType_t) portMAX_DELAY ) == pdTRUE)
        {
        return (true);
        }
    else
        {
        return (false);
        }
    }

void giveSemaphore(void)
    {
    vTaskDelay(xTickATinyBit);
    xSemaphoreGive(xMutexSemaphoreSerialPort);
    }

void TaskSecond(void* pvParameters);
void TaskBlink(void* pvParameters);

void setup()
    {
    DEBUG_INITIALISE(true, 115200); // allowing colour and setting serial port speed.
                                    // Change this to:
                                    //  DEBUG_INITIALISE(false, 115200);
                                    // if using the arduino IDE.
#ifdef DEBUG_ON
# if ESP32
    delay(5000); // because there is no hold while the serial port initialises
# else    
    initSemaphore();
    while (!DEBUG_DEBUGGERY)
        {
        }; // Hold until the serial port is ready.
# endif
#endif    
    DEBUG_RESETCOLOUR();
    Serial.println(F("This will be printed regardless of the state of DEBUG_ON"));
    #ifndef DEBUG_ON
    Serial.println(F("DEBUG_ON is not defined. (So this is the rather useless release version of blink!)"));
    #endif
    DEBUG_PROGANNOUNCE("debug_multitask blink Sketch ", __FILE__ " Built: " __DATE__ " " __TIME__);
    // For this next bit - see some clues in <debuggery.h>
    DEBUG_SETCOLOUR(92);
    DEBUG_PRINTLN(F("DEBUG_ON is defined."));
    DEBUG_RESETCOLOUR();

// Start two tasks
    int stackSizeInWords = configMINIMAL_STACK_SIZE + 128;

    xTaskCreate(TaskBlink,
                "TaskBlink",
                stackSizeInWords,
                NULL,
                2,
                NULL);

    xTaskCreate(TaskSecond,
                "TaskSecond",
                stackSizeInWords,
                NULL,
                2,
                NULL);

    DEBUG_PRINTLN(F("Starting ... "));
    }


    // The non-blocking version of the blink sketch.

void loop()
    {
      // We do stuff in the tasks.
    }

// cf https://www.freertos.org/a00122.html
void TaskBlink(void* pvParameters)
    {
    pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
    vTaskDelay(500 / portTICK_PERIOD_MS); // wait a half a sec so we start after we said, and not before!
    while (true) // just keep going
        {
        digitalWrite(LED_BUILTIN, HIGH);
        if (takeSemaphore())
            {
            DEBUG_SETCOLOR(93);
            DEBUG_PRINT("*");
            giveSemaphore();
            }
        vTaskDelay(250 / portTICK_PERIOD_MS); // wait a quarter of z sec = 250ms.
        digitalWrite(LED_BUILTIN, LOW);
        if (takeSemaphore())
            {
            DEBUG_SETCOLOR(31);
            DEBUG_PRINT("_");
            giveSemaphore();
            }
        vTaskDelay(250 / portTICK_PERIOD_MS);
        }
    }

void TaskSecond(void* pvParameters)
    {
    vTaskDelay(500 / portTICK_PERIOD_MS); // wait a half a sec so we start after we said, and not before!
    while (true) // just keep going
        {
        if (takeSemaphore())
            {
            DEBUG_RESETCOLOR();
            DEBUG_PRINT(" ");
            DEBUG_PRINT(millis() / 1000);
            DEBUG_PRINT(" ");
            giveSemaphore();
            }
        vTaskDelay(5000 / portTICK_PERIOD_MS); // wait a sec
        }
    }
