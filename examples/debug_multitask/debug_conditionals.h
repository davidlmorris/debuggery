

#ifndef debug_conditionals_h
# define debug_conditionals_h
// Why is this file here:
// We want to have an independent file we can use for different apps
// and for different files including other cpp file in the same app.
// We define DEBUG_ON to true to show 'we are debugging, and what we are debugging'
// defines which may be different in each app so we can application independence.

// Why not just in the main INO file?  Basically because while other INO
// files are concatenated with the main INO file before preprocessing
// any C++ file.  So if you have other .cpp files in your project they 
// will not have DEBUG_ON define.  
// Some of the issues are 10 years old... or more.
// cf https://github.com/arduino/Arduino/issues/1841
// and here a solution of sorts
//  http://www.gammon.com.au/forum/?id=12625
// which I am sorely tempted to follow!

// For more on Scope! 
// How to properly include C / C++ headers and source files in your Arduino Project
// https://stackoverflow.com/questions/55684371/how-do-i-add-cpp-file-to-an-arduino-project
// Sketch build process
// https://arduino.github.io/arduino-cli/1.0/sketch-build-process/


// DEBUG defines 
// This is the key one:
// ************************* here **************************
# define DEBUG_ON true // comment this out to remove debuggery altogether.

# ifdef NDEBUG  // Just in case the IDE is allowing DEBUG v RELEASE builds.
#  undef DEBUG_ON
# endif

# ifdef DEBUG_ON


 // Here add debug defines for specific parts of application, so they can be turned on anf off
 // with DEBUG_ON.  
#  define DEBUG_MIDI_SERIAL_TEXT_OUT true // comment this out to remove MIDI out as TEXT.

// Add any other debug conditionals here where you might want to test/debug/get_info on some part
// of the program, and then optionally undefine it, but keep in the statements just in case.

#  include <debuggery.h>

extern void initSemaphore(void);
extern bool takeSemaphore(void);
extern void giveSemaphore(void);

#  define DEBUG_INIT_SEMAPHORE              initSemaphore()
#  define DEBUG_START_SEMAPHORE_BLOCK       if(takeSemaphore())
#  define DEBUG_SEMAPHORE_RELEASE           giveSemaphore()
//extern const unsigned long xTickATinyBit;
//extern const unsigned long xTickFullSec;
//extern SemaphoreHandle_t xMutexSemaphoreSerialPort;


# else
#  include <not_debuggery.h>
#  define DEBUG_INIT_SEMAPHORE              ((void)0)
#  define DEBUG_START_SEMAPHORE_BLOCK       ((void)0);  // note the semi-colon is require here as we have staement not an if.
#  define DEBUG_SEMAPHORE_RELEASE           ((void)0)
# endif
#endif
