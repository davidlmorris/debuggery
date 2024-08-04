#ifndef debuggery_h
# define debuggery_h

# include <Arduino.h>
# include <Print.h>
# include "board_name.h"

// "What sort of debuggery is this...?"
//          ~ someone in 'Dr Dobbs Journal' decades ago.

// #  define assert(e) ((e) ? (void)0 : Debuggery.__assert(__func__, __FILE__, __LINE__, #e))
#  define debug_assert(e) ((e) ? (void)0 : Debuggery.__assert(__func__, __FILE__, __LINE__, #e))
#  define DEBUG_ASSERT(e) ((e) ? (void)0 : Debuggery.__assert(__func__, __FILE__, __LINE__, #e))

#  define setColor(...)  setColour(__VA_ARGS__);

// Variadic Macros to substitute Debuggery calls so we can undefine then
// without needing surround code with #if DEBUG_ON et al.
// C++11 onwards only of course... wow I could have used this 20 years ago!
# define DEBUG_INITIALISE(...) Debuggery.initialise(__VA_ARGS__)
# define DEBUG_PROGANNOUNCE(...)  Debuggery.progAnnounce(__VA_ARGS__)
# define DEBUG_WRITE(...)  Debuggery.write(__VA_ARGS__)
# define DEBUG_PRINT(...)  Debuggery.print(__VA_ARGS__)
# define DEBUG_PRINTLN(...)  Debuggery.println(__VA_ARGS__)
# define DEBUG_SETCOLOUR(...)  Debuggery.setColour(__VA_ARGS__)
# define DEBUG_SETCOLOR(...)  Debuggery.setColour(__VA_ARGS__)
// However, both the C99 and C++11 standards require at least one argument, so
// we really would prefer __VA_OPT__ from C++20 onwards.  But Arduino uses C++11.
// We are a bit lucky that we have only one and that it is not polymorphic.
# define DEBUG_RESETCOLOUR()  Debuggery.resetColour()
# define DEBUG_RESETCOLOR()  Debuggery.resetColour()
# define DEBUG_SPEEDTEST(...)  Debuggery.speedTest(__VA_ARGS__)
//# define DEBUG_SPEEDTEST(y)  Debuggery.speedTest(y)
//# define DEBUG_SPEEDTEST(y,z)  Debuggery.speedTest(y,z)
# define DEBUG_DEBUGGERY  Debuggery


// Note the use of the base Print class here.
// cf C:\Users\David\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\cores\arduino/Print.h
// cf C:\Users\David\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\cores\arduino/Printable.h

/// @brief Class for printing pretty information through the serial port using the same structure as
/// the print commands of a serial port, as well as providing additional infomation
/// if required.
class Debuggery_ : private Print
    {
    public:
        operator bool();
        void initialise(bool bAllowColour);
        void initialise(bool bAllowColour, unsigned long speed);
        void initialise(bool bAllowColour, unsigned long speed, uint32_t config);
        void progAnnounce(const char* progName);
        void progAnnounce(const char* progName, const char* greeting);
        void speedTest(const uint8_t reportEvery);
        void speedTest(const uint8_t reportEvery, const char * extraText);
        void speedTest(const uint8_t reportEvery, const char * extraText, const char * moreExtraText);


        // ~See Stroustrup 'The C++ Programming Language' 2nd ed r.3.3.1.3
        // for what seems like an out of place virtual.
        // note that Print::write is virtual.
        virtual size_t write(uint8_t byte);

        void setColour(uint8_t colour);
        void setColour(uint8_t fgColour, uint8_t bgColour);
        void resetColour(void);

        using Print::println;
        using Print::print;
        using Print::write;

        void __assert(const char* func, const char* file, int line, const char* failedExpr);

    private:
        void _init(bool bAllowColour);
        void _progAnnounce(const char* progname, const char* greeting);
        bool _bAllowColour;
    };

extern Debuggery_ Debuggery;

#endif

