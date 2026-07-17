#include "DebugConsole.h"
#include <Windows.h>
#include <iostream>
#include <cstdio>

namespace DebugConsole
{
    void Init(){
        AllocConsole();
        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);
        std::cout << "=== HP Bar Debug Console ===" << std::endl;
    }
}