#include <Arduino.h>
#include "debug_conditionals.h"
#ifdef ARDUINO_ARCH_AVR
// Esp32 has its own modified version included in the main libs.
# include <Arduino_FreeRTOS.h>
# include <semphr.h>
#endif

#ifdef DEBUG_ON

const unsigned long xTickATinyBit = (50 / portTICK_PERIOD_MS);
const unsigned long tickHalfASec = (500 / portTICK_PERIOD_MS);
const unsigned long xTickFullSec = (1000 / portTICK_PERIOD_MS);

SemaphoreHandle_t xBinarySemaphoreSerialPort = NULL;
#ifdef ESP32
StaticSemaphore_t xSemaphoreSerialPortBuffer;
#endif

void initSemaphore(void)
    {
#ifdef ESP32
    xBinarySemaphoreSerialPort = xSemaphoreCreateBinaryStatic(&xSemaphoreSerialPortBuffer);
    // xSemaphoreCreateBinaryStatic is undefined in <Arduino_FreeRTOS.h>
    // Need #define configSUPPORT_STATIC_ALLOCATION 1 for FreeRTOS code
    // cf https://github.com/earlephilhower/arduino-pico/issues/564
    // I prefer the static version, mainly because I have the impression that
    // the stack and memory size will basically remain constant if I am not
    // allocating memory - which might save grief later on.  However, there are things going on under the hood of FreeRTOS invloling various
    // heaps that I don't grok, so I may have misunderstood that is happening here.
#else    
    xBinarySemaphoreSerialPort = xSemaphoreCreateBinary();
#endif    
    xSemaphoreGive(xBinarySemaphoreSerialPort);
    }

bool takeSemaphore(void)
    {
    return (xSemaphoreTake(xBinarySemaphoreSerialPort, (TickType_t) xTickFullSec ) == pdTRUE);
    }

void giveSemaphore(void)
    {
    vTaskDelay(xTickATinyBit); // Allow a little time for the serial port to do its print.
    xSemaphoreGive(xBinarySemaphoreSerialPort);
    }
#endif
