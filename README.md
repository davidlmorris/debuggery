
# Debuggery

## A helper library for getting information (including an assert, and print macro) from MCUs like and Arduino Nano an Esp32 via the usual serial port

`"What sort of debuggery is this...?"`   _~ someone in 'Dr Dobbs Journal' many decades ago._

Debuggery is not Debug or Debugging!  Meaning, this is not 'real' debugging using jtag (or any thing else super duper fancy with the ability to stop code, check registers amd variables and resume).

So Why? I had collected various bits and pieces that I was using as a irregular and sometimes random scaffolding code, some of which I thought might be more generally useful. Sometimes I even forgot about things I had, or had learnt before. Putting it together in a Library made the most sense. And when actually putting this together, I discovered even more (like Variadic Macros). Since the boiler plate was mostly used for Serial Out at the start of a project only when I was debugging (yes I know...) - tying it together with Debugging macros seemed like the best idea.  Note, that in `debuggery.h` you get way of identifying the type of MCU or board being used (a work in progress).

## How to use it
Install the library code in the normal way.  Once installed copy the contents of `examples/debug_assert` to a working folder to create as a sketch.  The `debug_assert.INO` is just a modified 'blink' sketch.  The change to decide if we are building a debug or a release build is made in the 'debug_conditionals.h' header file.  

Why a separate header file, and not the INO?  Basically, because of the scope limitations of preprocessing in C++ it is not possible to have something defined in one C++ file and have it also show up in another .cpp file, even if they are in the same folder.  Now while this isn't true of .ino files since they are concatenated together (if in the same folder) before preprocessing to act as one big INO file, it is true if you have other .cpp files present.  So if you **only** use .ino files you can get away with included to contents of 'debug_conditionals.h' in your main .ino file.  However, I suggest you don't - because if you ever add a .cpp file to your project you don't want to be taken by the surprise the hard way (you know, after hours or work tracking down a non-existant bug).  If you are surprised now about this you are not alone, for a while I assumed that Arduino treated INO files and .cpp file in the same way.  The issue has been around for a while, see: <https://github.com/arduino/Arduino/issues/1841>.

For this reason you should include 'debug_conditionals.h' (or another file like it) in every file that you are going to use the assert macro or use Debuggery or the macros to print out some information from the Serial port.  

# How to disable debugging for a release version

To disable debugging just comment out the DEBUG_ON define in the include 'debug_conditionals.h' that you have added to your project.

```// ************************* here **************************```

```# define DEBUG_ON true // comment this out to remove debuggery altogether.```

When `DEBUG_ON` is not defined you will save about 1k of program storage and over 100 bytes of dynamic memory, and your 'release' version will run faster too, since it won't have extra, or maybe any, print statements going out to the Serial port.

Why `DEBUG_ON` and not `DEBUG`?  To avoid collisions with an environment that is able to use a debug builds versus releases (now of in the future).  Like using assert() over debug_assert (see below), this is really up to you, though I would recommend using DEBUG_ON as it is distinct.  All of the defines I use for various aspects or parts of the program I always start with DEBUG_, so I know at a glance what they are doing there.

Surround every Debuggery use (or group, or even a whole function) with `#if DEBUG_ON ... #endif`, so that when DEBUG_ON is not defined  (of is define to be false) the code runs without any issues, OR use the [Macros instead](#macros-instead) as shown below.

If you are convinced that using DEBUG (or even NDEBUG) will not result in any present or future collisions or issues, go ahead an use it. You'll probably want assert() as well.  I'm just playing safe here.

## Initialisation

Debuggery must be initialised using `Debuggery.initialise(true)` (or false for no colour). You won't want colour if just using the Arduino IDE, as that won't handle colour, and you'll see extra junk characters instead.  If you have a Serial port open already, it will flush the current one and re-open it at the default speed of 115200.

## Printing to the Serial port

Debuggery implements all of the Serial ports print and println commands, so for example `Debuggery.print(127, BIN)` will print "01111111" to the serial port, in exactly the same way as Serial.  You can find details of Arduino Serial here [Serial.print](https://www.arduino.cc/reference/en/language/functions/communication/serial/print/) and here [Serial.println](https://www.arduino.cc/reference/en/language/functions/communication/serial/println/).

## Colour support

In addition, optionally for serial monitors that support colour (like VSCode) you can set the colour to print, or use some variations of Debuggery.print to print text in colour.  To print numbers you can use `setColour(ForegroundColour)` (note the Commonwealth spelling) or `setColour(ForegroundColour, BackgroundColour)` to turn of a colour, and `resetColour()` to change it back to default.  The colours to be used can be found on the [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code) wikipedia page.

These colours allowed:
| FG | BG | Colour |
|-----|-----|-----------------|
| 30 |  40 |  Black   |
| 31 |  41 |  Red   |
| 32 |  42 |  Green   |
| 33 |  43 |  Yellow   |
| 34 |  44 |  Blue   |
| 35 |  45 |  Magenta  |  
| 36 |  46 |  Cyan   |
| 37 |  47 |  White   |
| 90 |  100 |  Bright Black (Gray) |
| 91 |  101 |  Bright Red   |
| 92 |  102 |  Bright Green   |
| 93 |  103 |  Bright Yellow   |
| 94 |  104 |  Bright Blue   |
| 95 |  105 |  Bright Magenta  |  
| 96 |  106 |  Bright Cyan   |
| 97 |  107 |  Bright White |

## Assert
An assert macro is provided that uses Debuggery to print to the serial port.  When `DEBUG_ON` is undefined (see: 'How to use it' above) the `debug_assert()` macro is replace by `((void)0)` which tells the compiler to do nothing, and not emit any code for the statement.  When `DEBUG_ON` is defined `debug_assert(some_boolean_test_condition)` will call `Debuggery.__assert(...)` passing the detail of the error and the location. If the condition is false, `Debuggery.__assert` will print 'assertion failed' follow by the condition that caused it, the function (if present), the file, and the line number.  And then the application will be aborted (terminated), or in the case of the Esp32 put into an infinite loop, since the Esp32 will reboot after an abort.

So our example code 'debug_macros.ino' when asserting the evidently false assertion `debug_assert(true == false)` the following being printed:

```Assertion failed: (true == false), function:loop, file:C:\Home\Github\Debuggery\examples\debug_assert\debug_assert.ino, line:32.```

There is an `assert()` macro also defined in exactly the same way, however I would recommend against using this just in case your environment (perhaps later) supports the `assert()`, and it becomes unclear which one is being used.  If DEBUG_ON is undefined in 'debug_conditionals.h', (just comment it out) this macro wil be removed from the code when complied, and the loop will continue.

# Macros instead
You might want to remove the need for `#if DEBUG_ON` or #`ifndef DEBUG_ON` from your code for single line prints, too make the code easier to manage especially if you don't want Macro conditions littered everywhere.  (My personal preference is to leave them in so I can see what is meant to be there.)

So for all of Debuggery you can substitute a macro in the form DEBUG_'some debuggery function'.

Some examples here:

`DEBUG_INITIALISE(true);`  instead of `Debuggery.initialise(true);`

`DEBUG_PROGANNOUNCE("Name of prog", "some greeting or detail");` instead of `Debuggery.progAnnounce("Name of prog", "some greeting or detail");`

`DEBUG_PRINT(127, HEX);` instead of `Debuggery.print(127, NEX);`

`DEBUG_PRINTLN("Some text");` instead of `Debuggery.println("Some text");`

`DEBUG_SETCOLOUR(91);` instead of `Debuggery.setColour(91);`

Note that each of these macro substitutions requires a semi colon at the end to complete the statement.

With one exception all of these macros when `DEBUG_ON` is not defined will be replace in the code with (void(0)) which means they will be ignored by the compiler.

The one exception is the boolean 'Overloaded operator' call to Debuggery, which will be replaced with `(true)`, so that `if(DEBUG_DEBUGGERY)` will not result in a syntax error.  This replicates the behaviour of the default `if(Serial)` statement. See [Arduino if(Serial)](https://www.arduino.cc/reference/en/language/functions/communication/serial/ifserial/). If you do use this it would be best to wrap the use of it in an `#if DEBUG_ON ... #endif` preprocessor conditional, so the if or while statement is not unnecessarily included in the release code.
