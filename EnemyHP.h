#pragma once

#include "Structures.h"

struct EnemyHPInfo { int CurrentHP; int MaxHP; bool IsShell; };
struct TargetWindowResult { wchar_t* Text; int MaxHP; int CurrentHP; };

namespace EnemyHP {
    EnemyHPInfo GetEnemyHPValues(Enemy* enemy);
    TargetWindowResult BuildTargetWindow(Enemy* enemy, TWindowLockOn* window);

    void BuildTargetWindowRegisters(Enemy* enemy, TWindowLockOn* window, wchar_t** text, int* maxHP, int* currentHP);
    wchar_t* UpdateEnemyHPText(Enemy* enemy, TWindowLockOn* window);
    int GetEnemyMaxHP(Enemy* enemy);
}