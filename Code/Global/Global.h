#pragma once

#ifdef _WIN32
#ifndef NOMINMAX
# define NOMINMAX
#endif
#include <windows.h>
#endif

#if defined (_WIN32) && defined (_MSC_VER) && !defined(NDEBUG)
    #define WINDEBUG
#endif

#if defined (_WIN32) && defined (_MSC_VER) && !defined(NDEBUG)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define my_new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#else
#define my_new new
#endif // NDEBUG

#define XE_SAFE_FREE(_x)         { if ((_x) != nullptr) { free    ((_x)); _x = nullptr; } }
#define XE_SAFE_DELETE(_x)       { if ((_x) != nullptr) { delete   (_x);  _x = nullptr; } }
#define XE_SAFE_DELETE_POINTER(_x) { if ((_x) != nullptr) { delete [] (_x);  _x = nullptr; } }

#define DS_EXCEPTION_HANDLING
#define DS_DEBUG_LOG         // prints container data, etc.
#ifdef DS_DEBUG_LOG
//#define DS_DEBUG_LOG_VERBOSE // prints constructors of test objects, etc.
#include <sstream>
#endif

// 0x01 ==   1 == "00000001"
// 0x02 ==   2 == "00000010"
// 0x04 ==   4 == "00000100"
// 0x08 ==   8 == "00001000"
// 0x10 ==  16 == "00010000"
// 0x20 ==  32 == "00100000"
// 0x40 ==  64 == "01000000"
// 0x80 == 128 == "10000000"
enum CM_LOGGERLOCATION : unsigned char
{
    CM_LOGGER_NOWHERE = 0x00,
    CM_LOGGER_FILE = 0x01,
    CM_LOGGER_CONSOLE = 0x02
};

enum CM_LOGGERENTRY : unsigned char
{
    CM_LOGGER_NOTHING = 0x00,
    CM_LOGGER_COMMENT = 0x01,
    CM_LOGGER_EVENT = 0x02,
    CM_LOGGER_WARNING = 0x04,
    CM_LOGGER_ERROR = 0x08
};

#define USE_DEBUG_MESSAGES
#ifdef USE_DEBUG_MESSAGES

#define X_NEWLINESTR " \n"
#define SOURCEPATH_LENGTH                         strlen(SOURCEPATH) + 1
#define SOURCE_FILENAME                          &__FILE__[SOURCEPATH_LENGTH]

#include <string>
#define FILE_NAME(name) (std::string(name).find(SOURCEPATH) != std::string::npos) ? SOURCE_FILENAME : __FILE__

#ifdef WINDEBUG
#include <stdexcept>
#define THROW throw std::runtime_error("Failed");
#define X_BREAK { if (IsDebuggerPresent()) __debugbreak(); THROW }
#else
#include <stdexcept>
#define THROW { throw std::runtime_error("Failed"); }
#define X_BREAK THROW
#endif

// the following defines are for asserts, popup dialogs and log messages
// asserts
#define X_ASSERT_IF_FALSE(expr)                                                            {if (!static_cast<bool>(expr)){BASELIB::MessageConsole(CM_LOGGER_WARNING, "Assert (is false): %s (%d): %s" X_NEWLINESTR , FILE_NAME(__FILE__), __LINE__, #expr); X_BREAK}}
#define X_ASSERT_IF_TRUE(expr)                                                            {if (static_cast<bool>(expr)){BASELIB::MessageConsole(CM_LOGGER_WARNING,  "Assert (is true): %s (%d): %s" X_NEWLINESTR , FILE_NAME(__FILE__), __LINE__, #expr); X_BREAK}}
#define X_ASSERT_IF_FALSE_MSG(expr, fmt, ...)                                            {if (!static_cast<bool>(expr)){BASELIB::MessageConsole(CM_LOGGER_WARNING, "Assert (is false): %s (%d): %s" fmt X_NEWLINESTR , FILE_NAME(__FILE__), __LINE__, #expr, ##__VA_ARGS__); X_BREAK}}
#define X_ASSERT_IF_TRUE_MSG(expr, fmt, ...)                                            {if (static_cast<bool>(expr)){BASELIB::MessageConsole(CM_LOGGER_WARNING,  "Assert (is true): %s (%d): %s" fmt X_NEWLINESTR , FILE_NAME(__FILE__), __LINE__, #expr, ##__VA_ARGS__); X_BREAK}}
#define X_ASSERT_ALWAYS()                                                                X_ASSERT_IF_FALSE(false)


// log messages
#define X_DEBUG_MSG(fmt, ...)                                                            BASELIB::MessageConsole(CM_LOGGER_COMMENT, fmt X_NEWLINESTR, ##__VA_ARGS__);
#define X_DEBUG_COMMENT(fmt, ...)                                                        BASELIB::MessageConsole(CM_LOGGER_COMMENT, "Comment: %s(): " fmt X_NEWLINESTR, __func__, ##__VA_ARGS__);
#define X_DEBUG_EVENT(fmt, ...)                                                            BASELIB::MessageConsole(CM_LOGGER_EVENT, "Event: %s(): " fmt X_NEWLINESTR, __func__, ##__VA_ARGS__);
#define X_DEBUG_WARNING(fmt, ...)                                                        BASELIB::MessageConsole(CM_LOGGER_WARNING, "Warning: %s(): " fmt X_NEWLINESTR, __func__, ##__VA_ARGS__);
#define X_DEBUG_ERROR(fmt, ...)                                                            BASELIB::MessageConsole(CM_LOGGER_ERROR, "Error: %s(): " fmt X_NEWLINESTR, __func__, ##__VA_ARGS__);

#endif // USE_DEBUG_MESSAGES

#include "Exit.h"
#include "Logger.h"

