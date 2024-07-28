
[//]: # (https://keepachangelog.com/en/1.1.0/)


# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 1.1.8
- fixing version information in library.properties and library.json.

## 1.1.7
- fixed conversion from 'SerialConfig' to 'uint8_t' (which should have been uint32_t).
- Commented out define assert(e), as far too likely to conflict with existing 'asserts', especially for the Esp32.


## 1.1.6
- Changed to <Arduino.h> rather than <arduino.h> in debug_multitask 'debug_multitask.ino' example.

## 1.1.5
- Changed to <Arduino.h> rather than <arduino.h> in debug_multitask 'debug_conditionals.cpp' example.

## 1.1.4
- Removed debug_assert macros from inside print colour which could cause stack overflow failures as they were self referring.
- Improved debug_multitask by adding Macros in the same style as the ones in debuggery.h
- Minor changes to keywords and library properties.
- Added library.json for platformIO.

## 1.1.3
- Bumped to try and solve lib reg issues over capital letter in lib name.
- Changed name from Debuggery to debuggery to attempt to address Arduino-lint issues.

## 1.1.2
- Removed a weird macro that somehow crept in to debuggery.h.
- Added debug_multitask example.


## 1.1.1
 - Added void speedTest(const uint8_t reportEvery) which when inserted (once only) in a loop as the last item, will report the number of loops per second displaying every 'reportEvery' number of seconds.
 - Added an 'upper case' version of DEBUG_ASSERT to make it obvious that this is a macro and part of Debuggery.


## 1.1.0
 - Added ARDUINO_AVR_PROMICRO16 to "board_name.h" (used in platformio).
 - removed the following functions as redundant, and for expressing two ideas in one call.  Use a print or println, with a setcolour before the call.
 - removed size_t print(char* text, uint8_t colour);
 - removed size_t println(char* text, uint8_t colour);
 - removed size_t print(const __FlashStringHelper* text, uint8_t colour);
 - removed size_t println(const __FlashStringHelper* text, uint8_t colour);


## 1.0.5 - 2024-07-06
 - fixed regression from 1.0.4 'no matching function' in assert_macros.ino in examples.

## 1.0.4 - 2024-07-06
- Added const to `void progAnnounce(const char* progName);` and overloads and associated functions.
- Made SETCOLOUR and SETCOLOR macros variadic.
- Added manual changelog.

## 1.0.3 - 2024-07-05
- Changed Macros to use KEYWORD3.
- Added floating point examples to debug_macros.ino.
- removed assets folder.

## 1.0.2 - 2024-07-03
- Changed or added some comments.
- remove vscode workspace settings file.

## 1.0.1 - 2024-07-03
- Removed unnecessary constructors.

## 1.0.0 - 2024-07-01
- Initial release.