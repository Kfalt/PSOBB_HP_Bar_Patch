#pragma once
#include <Windows.h>

namespace Offset
{
//     ┌─────────────────────────────────────────────────────────┐
//     │             Patch_HP_BAR: -> Memory Address             │
//     └─────────────────────────────────────────────────────────┘

        // Boss Type Identifiers
    constexpr DWORD DeRolLeType = 0x00A43D2C;
    constexpr DWORD DeRolLeJointType = 0x00A43DAC;
    constexpr DWORD BarbaRayType = 0x00A47AF8;
    constexpr DWORD BarbaRayJointType = 0x00A47B0C;

    // Boss Movement Data
    constexpr DWORD BossMovementData = 0x00A43CC8;

    // Game Functions
    constexpr DWORD UnitxtGetMonsterName = 0x00793014;
    constexpr DWORD GameSwprintf = 0x00857E29;

    // Hook: retrieval of current HP.
    constexpr DWORD HookGetCurrentHP = 0x007318C7;

    // Hook: Monster HP Bar update
    constexpr DWORD HookMonsterHPBar = 0x007318B7;

    // Hook: Updates the text in the Lock-On window.
    constexpr DWORD HookUpdateWindowText = 0x00731F08;

    // Hook: Updates the text by HP Bar function EBX Lock-On window.
    /*constexpr DWORD MonsterHPBarFunction = 0x0073183C;*/

    // Windows HP Bar Memory Size
    constexpr DWORD FlagClearPatch = 0x007318DD;
    constexpr DWORD WindowSizeLoad = 0x00731C44;
    constexpr DWORD WindowSizeInit = 0x00731F2A;
    constexpr DWORD WindowSizeUpdate = 0x00731BAF;
    constexpr DWORD WindowWidthPointer = 0x009710B8;
    constexpr DWORD WindowHeight1 = 0x009F2DA4;
    constexpr DWORD WindowHeight2 = 0x009F2DD4;
    constexpr DWORD WindowHeight3 = 0x009F2E04;
    constexpr DWORD WindowHeight4 = 0x009F2E34;
    constexpr DWORD WindowHeight5 = 0x009F2E64;
    constexpr DWORD WindowColorPointer = 0x009F2E80;
}