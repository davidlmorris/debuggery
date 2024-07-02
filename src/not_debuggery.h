#ifndef not_debuggery_h
# define not_debuggery_h
// we need to have there here if we use 'debug_assert' regardless of if
// we are using Debuggery or not.
#  define assert(e) ((void)0)
// if we don't include this file things could get horribly messed up if we use assert.
// especially if another libary has used #include <assert>.
// so another option could help to remind us... (in other words USE THIS:)
#  define debug_assert(e) ((void)0)

# define DEBUG_INITIALISE(...) ((void)0)
# define DEBUG_PROGANNOUNCE(...)  ((void)0)
# define DEBUG_WRITE(...)  ((void)0)
# define DEBUG_PRINT(...)  ((void)0)
# define DEBUG_PRINTLN(...)  ((void)0)
# define DEBUG_SETCOLOUR(...)  ((void)0)
# define DEBUG_SETCOLOR(...)  ((void)0)
# define DEBUG_RESETCOLOUR()  ((void)0)
# define DEBUG_RESETCOLOR()  ((void)0)
# define DEBUG_DEBUGGERY  (true)

#endif
