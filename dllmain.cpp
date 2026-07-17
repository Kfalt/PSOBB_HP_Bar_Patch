//   ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
//   │                                                                                                            │
//   │                         < DLL patch PSOBB ( HP Bar + Text HP ) Source Code >                               │
//   │                                                                                                            │
//   │                                  Patch DLL Created By: ( Kfalt )                                           │
//   │                                  Created: ( 02/07/2026 - 03:39 )                                           │
//   │                                                                                                            │
//   │                               Special Thanks to: ( Fuzziqer Software )                                     │
//   │                                                                                                            │
//   │  ────────────────────────────────────────────────────────────────────────────────────────────────────────  │
//   │                              Creating this fix took me a long time.                                        │
//   │   Please respect the original source code and do not take full credit for this fix. This C++ fix adheres   │
//   │    to the logic of the ASM patch by 99%; it does not account for the icons of status effects applied to    │
//   │   enemies.Out of respect, please credit the author and acknowledge the source of this project.             │
//   │  ────────────────────────────────────────────────────────────────────────────────────────────────────────  │
//   │                                                                                                            │
//   │   This patch is based on the ASM patch created by Fuzziquer; please respect his work for ethical reasons.  │
//   │                                                                                                            │
//   │   Source: https://github.com/fuzziqersoftware/newserv/blob/master/system/client-functions/EnemyHPBarsBB.s  │
//   │                                                                                                            │
//   │   Name: ( Martin Michelsen )                                                                               │
//   │   Aka: ( Fuzziqe Software )                                                                                │
//   │   Github Author: https://github.com/fuzziqersoftware/                                                      │
//   │                                                                                                            │
//   └────────────────────────────────────────────────────────────────────────────────────────────────────────────┘

#include <Windows.h>
#include "Hooks.h"
#include "DebugConsole.h"
#include "Logger.h"

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        
        /*DebugConsole::Init();*/
       /* Logger::Init();*/
        Hooks::Patch_EnemyHP_BAR();
    }
    return TRUE;
}

