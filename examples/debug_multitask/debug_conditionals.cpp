#include <arduino.h>
#ifdef ARDUINO_ARCH_AVR
// Esp32 has its own modified version included in the main libs.
# include <Arduino_FreeRTOS.h>
# include <semphr.h>
#endif
#include "debug_conditionals.h"

#ifdef DEBUG_ON

const unsigned long xTickATinyBit = (50 / portTICK_PERIOD_MS);
const unsigned long xTickFullSec = (1000 / portTICK_PERIOD_MS);

SemaphoreHandle_t xBinarySemaphoreSerialPort = NULL;
// StaticSemaphore_t xSemaphoreSerialPortBuffer;

void initSemaphore(void)
    {

    // xBinarySemaphoreSerialPort = xSemaphoreCreateBinaryStatic(&xSemaphoreSerialPortBuffer);
    // xSemaphoreCreateBinaryStatic is undefined in <Arduino_FreeRTOS.h>
    // Need #define configSUPPORT_STATIC_ALLOCATION 1 for FreeRTOS code
    // cf https://github.com/earlephilhower/arduino-pico/issues/564
    xBinarySemaphoreSerialPort = xSemaphoreCreateBinary();
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
