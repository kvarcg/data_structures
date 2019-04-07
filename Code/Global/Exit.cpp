// global includes    //////////////////////////////
#include "Global.h"

// includes ////////////////////////////////////////
#include <iostream>
#if defined(WINDEBUG)
#include <crtdbg.h>
#include <windows.h>
#endif
#include "Exit.h"

// defines /////////////////////////////////////////

namespace BASELIB
{
    Exit e;

    // Constructor
    Exit::Exit()
    {
#if defined(WINDEBUG)
        int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
        tmpDbgFlag |= _CRTDBG_ALLOC_MEM_DF;             // Turn on debug allocation
        //tmpDbgFlag |= _CRTDBG_CHECK_ALWAYS_DF;        // Check heap every alloc / dealloc
        //tmpDbgFlag |= _CRTDBG_CHECK_CRT_DF;           // Leak check/diff CRT blocks
        tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;        // Don't actually free memory
        tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;            // Leak check at program exit
        _CrtSetDbgFlag(tmpDbgFlag);
#endif // WIN32 && _DEBUG
    }

    // Destructor
    Exit::~Exit()
    {
#if defined(WINDEBUG)
        OutputDebugStringA("Detecting Memory Leaks\n");
        std::cout << "Detecting Memory Leaks" << std::endl;
#endif // WIN32 && _DEBUG
    }

    // other functions

} // namespace BASELIB

// eof ///////////////////////////////// class Exit
