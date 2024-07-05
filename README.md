
# Debuggery

## A helper library for getting information (including an assert, and print macro) from Arduino including the Esp32 via the usual serial port

`"What sort of debuggery is this...?"` ~  *someone in Dr Dobbs Journal many decades ago.*

Debuggery is not Debug or Debugging!  Meaning, this is not 'real' debugging using jtag (or any thing else super duper fancy with the ability to stop code, check registers amd variables and resume).

## Contents

- [Why?](#why)
- [How to use it](#how-to-use-it)
- [How to disable debugging for a release version](#how-to-disable-debugging-for-a-release-version)
- [Initialisation](#initialisation)
- [Printing to the Serial port](#printing-to-the-serial-port)
- [Colour support](#colour-support)
- [Assert](#assert)
- [Macros instead](#macros-instead)
- [Spelling](#spelling)
- [Debuggery Public Mmebers](#debuggery-public-members)
- [Coding Style](#coding-style)
- [Language](#language)

## How it works

Unlike some other debug utilities library this will print floating point numbers (as per the Serial library).  It extends the Print amd Printable classes, also  used by Serial, LiquidCrystal, Ethernet and WifI, and so prints in exactly the same way with out adding much overhead to your code (about 1k).  

## Why?

So why? I had collected various bits and pieces that I was using as a irregular and sometimes random scaffolding code, some of which I thought might be more generally useful. Sometimes I even forgot about things I had, or had learnt before. Putting it together in a Library made the most sense. And when actually putting this together, I discovered even more (like Variadic Macros). Since the boiler plate was mostly used for Serial Out at the start of a project only when I was debugging (yes I know...) - tying it together with Debugging macros seemed like the best idea.  

Note, that in `debuggery.h` you get way of identifying the type of MCU or board being used, see 'src\board_name.h'.  

## How to use it

Install the library code in the normal way.  Currently that means using the 'add zip method' in arduino IDE 2.0 onwards.  Alternatively, download the current release zip file, and copy the folder inside to where the arduino libraries are stored on your system.  On windows, by default, this is in your documents folder, under 'Arduino\libraries'.

Once installed copy the contents of `examples/debug_assert` to a working folder to create as a sketch.  (Do NOT use the arduino 'include library' method from the sketch menu as that will add all the header files to your sketch INO file, when all we want is to include the 'debug_conditionals.h' header file that we will have copied or created in the local sketch folder.)  

The `debug_assert.INO` is just a modified 'blink' sketch.  To Debug or not is a question we decide (are building a debug or a release build?) in the 'debug_conditionals.h' header file.  

Why a separate header file, and not just in the sketch.INO?  Basically, because of the scope limitations of preprocessing in C++  it is not possible to have something defined in one C++ file and have it also show up in another '.cpp' file, even if they are in the same folder.  Now while this isn't actually true of '.ino' files since all the INO files in the Arduino project folder are concatenated together before preprocessing to act as one big INO file, it is true if you have other '.cpp' files present. 

So if you **only** use '.ino' files you can get away with including the contents of 'debug_conditionals.h' in your main '.ino' file, if your really insisted.  However, I wouldn't recommend it - because if you ever add a '.cpp' file to your project you don't want to be taken by surprise the hard way (you know, after hours of work tracking down a non-existant bug).  If you are surprised now about this you are not alone, for a while I naturally assumed that Arduino treated INO files and '.cpp' file in the same way.  The [issue](https://github.com/arduino/Arduino/issues/1841) has been around for a while.

For this reason you should include 'debug_conditionals.h' (or another file like it) in every file that you are going to use the assert macro or use Debuggery or the macros to print out some information from the Serial port.  

## How to disable debugging for a release version

To disable debugging just comment out the DEBUG_ON define in the include 'debug_conditionals.h' that you have added to your project.

```// ************************* here **************************```

```# define DEBUG_ON true // comment this out to remove debuggery altogether.```

When `DEBUG_ON` is not defined you will save program storage  and dynamic memory.  With the example code it will be about 1k of program storage and over 100 bytes of dynamic memory, and your 'release' version will likely run faster too, since it won't have extra, or maybe any, print statements going out to the Serial port.  Unfortunately, if you include a reference to the header file 'debuggery.h' in an INO file even if #defined out (as in "debug_conditionals.h"), Arduino seems to find a way of including the associated cpp file. This is true of all library headers that you might add, not just Debuggery! See this answer from Nick Gammon on [StackExchange](https://arduino.stackexchange.com/a/13182/100121) for an hint about why.

Why `DEBUG_ON` and not `DEBUG`?  It is to avoid potential collisions with an IDE environment that uses debug builds versus releases (now or in the future) since they will certainly use DEBUG.  This is really up to you, as DEBUG will probably work now, though I would recommend using DEBUG_ON as it is distinct.  All of the defines I use for various aspects or parts of the program I always start with DEBUG_, so I know at a glance what they are doing there.

Surround every Debuggery use (or group, or even a whole function) with `#if DEBUG_ON ... #endif`, so that when DEBUG_ON is not defined  (of is define to be false) the code runs without any issues, OR use the [Macros instead](#macros-instead) as shown below.

If you are convinced that using DEBUG (or even NDEBUG) will not result in any present or future collisions or issues, go ahead an use it. You'll probably want [assert()](#assert) as well (again not recommended).  I'm just playing it safe here.

## Initialisation

Debuggery must be initialised using `Debuggery.initialise(true)` (or false for no colour). VScode will handle [colour](#colour-support). You won't want colour if just using the Arduino IDE, as that doesn't handle colour and you'll see extra junk characters instead.  

If you have a Serial port open already, 'initialise' will flush the Serial port and re-open it at the default speed of 115200, or at the speed your specify.

## Printing to the Serial port

Debuggery implements all of the Serial ports print and println commands, so for example `Debuggery.print(127, BIN)` will print "01111111" to the serial port, in exactly the same way as Serial.  You can find details of Arduino Serial here [Serial.print](https://www.arduino.cc/reference/en/language/functions/communication/serial/print/) and here [Serial.println](https://www.arduino.cc/reference/en/language/functions/communication/serial/println/).

## Colour support

You can set the colour to print, or use some overloads of Debuggery.print to print text in colour.  To change the colour of text can use `setColour(ForegroundColour)` (note the Commonwealth [spelling](#spelling)) or `setColour(ForegroundColour, BackgroundColour)` to turn of a colour, and `resetColour()` to change it back to default.  The colours to be used can be found on the [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code) wikipedia page.  See [spelling](#spelling) below if you want to use color instead of colour (basically you can).

These colours are allowed:
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

There is an `assert()` macro also defined in exactly the same way, however I would recommend against using this just in case your environment (perhaps later) supports the `assert()`, and it becomes unclear which one is being used.  If DEBUG_ON is undefined in 'debug_conditionals.h', (just comment it out) this macro wil be removed from the code when complied (though it is still present in the source code), and the loop will continue as expected.

## Macros instead

You might want to remove the need for `#if DEBUG_ON` or #`ifndef DEBUG_ON` from your code for single line prints, too make the code easier to manage especially if you don't want Macro conditions littered everywhere.

So for all of Debuggery you can substitute a macro in the form DEBUG_'some debuggery function'.

Some examples here:

`DEBUG_INITIALISE(true);`  instead of `Debuggery.initialise(true);`

`DEBUG_PROGANNOUNCE("Name of prog", "some greeting or detail");` instead of `Debuggery.progAnnounce("Name of prog", "some greeting or detail");`

`DEBUG_PRINT(127, HEX);` instead of `Debuggery.print(127, NEX);`

`DEBUG_PRINTLN("Some text");` instead of `Debuggery.println("Some text");`

`DEBUG_SETCOLOUR(91);` instead of `Debuggery.setColour(91);`

So this section of code...

```
# if DEBUG_ON
  Debuggery.println("Some text");
# endif
```

can be replaced with:

```
  DEBUG_PRINTLN("Some text");
```

...which is probably easier and neater.

Note that each of these macro substitutions requires a semi colon at the end to complete the statement.  Easy to forget.

With one exception all of these macros when `DEBUG_ON` is not defined will be replaced in the code with (void(0)) which means they will be ignored by the compiler.

The exception is the boolean 'Overloaded operator' call to Debuggery, which will be replaced with `(true)`, so that `if(DEBUG_DEBUGGERY)` will not result in a syntax error.  This replicates the behaviour of the default `if(Serial)` statement. See [Arduino if(Serial)](https://www.arduino.cc/reference/en/language/functions/communication/serial/ifserial/). If you do use this it would be best to wrap the use of it in an `#if DEBUG_ON ... #endif` preprocessor conditional, so the if or while statement is not unnecessarily included in the release code.

## Spelling

I can't.  As I discovered when I found how to get spell check for Readme.md files.

But more importantly... since I expect someone will want to spell colour as color, there are macros that will do with automagically, so using `Debuggery.setColor(91)` is the same as using `Debuggery.setColour(91)`, and `DEBUG_SETCOLOR(91)` is the same as using `DEBUG_SETCOLOUR(91)`.

## Debuggery Public Members

- ###  operator bool ()

    Overloaded operator to test if the serial port has started.

- ### void initialise (bool bAllowColour)

    Overloaded function to initialise Debuggery.

- ### void initialise (bool bAllowColour, unsigned long speed)

    Overloaded function to initialise Debuggery.

- ### void initialise (bool bAllowColour, unsigned long speed, uint8_t config)

    Overloaded function to initialise Debuggery.

- ### void progAnnounce (char \*programmeName)

    Displays the Board name and program as a hello message usually used
    in setup when establishing the app as a start up message.

- ### void progAnnounce (char \*programmeName, char \*greeting)

    Displays the Board name and program and a greeting usually used in
    setup when establishing the app as a start up message.

- ### size_t print (char \*text, uint8_t colour)

    Overloaded function to print text to the serial port with colour.

- ### size_t println (char \*text, uint8_t colour)

    Overloaded function to print text to the serial port with colour,
    followed by a carriage return character (ASCII 13, or \'\\r\') and a
    newline character (ASCII 10, or \'\').

- ### size_t print (const \_\_FlashStringHelper \*text, uint8_t colour)

    Overloaded function to print to the serial port with colour using
    the F() macro.

- ### size_t println (const \_\_FlashStringHelper \*text, uint8_t colour)

    Overloaded function to print to the serial port with colour using
    the F() Macro, followed by a carriage return character (ASCII 13, or
    \'\\r\') and a newline character (ASCII 10, or \'\').

- ### "+ all the print and println functions from the Arduino Serial interface"

    See [Serial.print()](https://www.arduino.cc/reference/en/language/functions/communication/serial/print/) and [Serial.println()](https://www.arduino.cc/reference/en/language/functions/communication/serial/println/).

- ### virtual size_t write (uint8_t byte)

    Write a byte to the the serial port.

- ### void setColour (uint8_t colour)

    Changes the serial monitor display colour.

- ### void setColour (uint8_t fgColour, uint8_t bgColour)

    Changes the serial monitor foreground and background display colour.

- ### void resetColour (void)

    Resets the colour to the default value.

- ### void \_\_assert (const char \*func, const char \*file, int line, const char \*failedexpr)

    Used in conjuction with the debug_assert macro.

## Coding Style

 I prefer one idea per line, full and redundant use of brackets and braces, and I avoid terse expression like `x =+ 2` in favour of `x = x + 2`, making an exception for for the obvious `x++`. (Terse code is only useful, in my view, for those having a crack at the [International Obfuscated C Code Contest](https://en.wikipedia.org/wiki/International_Obfuscated_C_Code_Contest)!) None of this makes a bit of difference to the compiled result, of course.

 The brace format is called [whitesmiths](https://en.wikipedia.org/wiki/Indentation_style#Whitesmiths), though I hadn't heard of that before using '.editorconfig'.  Using whitesmiths may show my age, but really it is just that I have read Steve McConnell's 'Code Complete' which explains why the braces are like 'begin' and 'end' (with some evidence has to how to place them for clarity and why 'Allman' and 'Whitesmiths' are superior), and Charles Petzold in general who used Whitesmiths.  Beyond that, this is the style I find is the cleanest and clearest (for the least [Cognitive load](https://en.wikipedia.org/wiki/Cognitive_load)), and is the preferred coding style in my repositories.

## Language

Somewhere, somehow, someone will be offended by the name of this project. And I will probably have to change it.

Where I grew up in Western Australia the use of the word 'bugger' was considered inoffensive slang.  My favourite aunt used it, it was used in front of children, and in front of your mother. It was even in a [Toyota television add](https://www.youtube.com/watch?v=CPYmtEQiG18) back a few decades ago. This is by way of contrast with the F-Bomb which was never used in polite company ever.  But like a lot of language 'Bugger', 'Crikey' and 'Bloody' have all fallen into less common use.  The more woke amongst us would suggest that these words had derivations respectively from Homophobic, blasphemous, or misogynistic roots, and that culture, rightfully, moves with the times.

That language changes is demonstrated by that last sentence which would not have been parsed at all well in the last century!  Of course, even [roots](https://www.smh.com.au/traveller/inspiration/its-rooted-aussie-terms-that-foreigners-just-wont-get-20140521-38nlc.html) is sort of rude in Australia.  And internationalisation has meant many words from my childhood in the 60's and 70's have vanished.  Locally, we used ging (for sling shot or child's catapult) and broggie (for skidding your bicycle sideway especially on a sandy track or road) which I haven't heard in decades.  Though 'gidgee' for fishing spear seems to have escaped its local confines (Perth Noongar aboriginal word) and is apparently now used world wide.  

Perhaps by using Debuggery I am just inviting a pull request...

  ...OK, I really should stop now.
