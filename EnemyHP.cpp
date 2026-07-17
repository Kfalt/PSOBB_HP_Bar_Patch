#include "EnemyHP.h"
#include "Offsets.h"
#include "DebugConsole.h"
#include "Logger.h"

#include <cwchar>

static TargetWindowResult LastTargetResult{};

//     ┌─────────────────────────────────────────────────────────┐
//     │       Call Function bool & GetBossMovementData()        │
//     └─────────────────────────────────────────────────────────┘
namespace {

    bool IsDeRolLeJoint(const Enemy* enemy) { return enemy->TypeName == Offset::DeRolLeJointType; }
    bool IsBarbaRayJoint(const Enemy* enemy) { return enemy->TypeName == Offset::BarbaRayJointType; }
    bool IsDeRolLe(const Enemy* enemy) { return enemy->TypeName == Offset::DeRolLeType; }
    bool IsBarbaRay(const Enemy* enemy) { return enemy->TypeName == Offset::BarbaRayType; }
    BossMovementData* GetBossMovementData() { return *reinterpret_cast<BossMovementData**>(Offset::BossMovementData); }
}

//     ┌─────────────────────────────────────────────────────────┐
//     │                   Debug Log                             │
//     └─────────────────────────────────────────────────────────┘
// void LogBossHP(const char* bossName, Enemy* enemy, EnemyHPInfo hp) {
//     Logger::Write("[BOSS HP]:  Name=(%s) | enemy=(%p) | Current=(%d) | Max=(%d) | Shell=(%d)\n", bossName, enemy, hp.CurrentHP, hp.MaxHP,hp.IsShell);
// }


//     ┌─────────────────────────────────────────────────────────┐
//     │     Call EnemyHP::GetEnemyHPValues get value enemy      │
//     └─────────────────────────────────────────────────────────┘
EnemyHPInfo EnemyHP::GetEnemyHPValues(Enemy* enemy) {
    EnemyHPInfo hp{};

    if (!enemy)
        return hp;

    if (!IsDeRolLe(enemy) && !IsDeRolLeJoint(enemy) && !IsBarbaRay(enemy) && !IsBarbaRayJoint(enemy)) {
        hp.CurrentHP = enemy->CurrentHP;
        hp.MaxHP = enemy->MaxHP;
        hp.IsShell = false;
        return hp;
    }


    if (IsDeRolLeJoint(enemy)) {

        BossMovementData* movement = GetBossMovementData();

        if (!(enemy->JointShellFlags & 0x01)) {
            hp.CurrentHP = enemy->JointShellHP;
            hp.MaxHP = movement->ShellMaxHP;
            hp.IsShell = true;

            return hp;
        }

        enemy = enemy->Parent;

        if (enemy->MaskFlags & 0x08) {
            hp.CurrentHP = enemy->BodyCurrentHP;
            hp.MaxHP = enemy->BodyMaxHP;
            hp.IsShell = false;
            return hp;
        }

        hp.CurrentHP = enemy->MaskHP;
        hp.MaxHP = movement->MaskMaxHP;
        hp.IsShell = true;

        return hp;
    }


    if (IsDeRolLe(enemy)) {
        BossMovementData* movement = GetBossMovementData();

        if (enemy->MaskFlags & 0x08) {
            hp.CurrentHP = enemy->BodyCurrentHP;
            hp.MaxHP = enemy->BodyMaxHP;
            hp.IsShell = false;
            return hp;
        }

        hp.CurrentHP = enemy->MaskHP;
        hp.MaxHP = movement->MaskMaxHP;
        hp.IsShell = true;

        return hp;
    }

    if (IsBarbaRayJoint(enemy)) {
        BossMovementData* movement = enemy->Parent->MovementData;

        if (!(enemy->BarbaJointShellFlags & 0x01)) {
            hp.CurrentHP = enemy->BarbaJointShellHP;
            hp.MaxHP = movement->ShellMaxHP;
            hp.IsShell = true;

            return hp;
        }

        enemy = enemy->Parent;

        if (enemy->BarbaMaskFlags & 0x08) {
            hp.CurrentHP = enemy->BarbaBodyCurrentHP;
            hp.MaxHP = enemy->BarbaBodyMaxHP;
            hp.IsShell = false;

            return hp;
        }

        hp.CurrentHP = enemy->BarbaMaskHP;
        hp.MaxHP = movement->MaskMaxHP;
        hp.IsShell = true;

        return hp;
    }


    if (IsBarbaRay(enemy)) {
        BossMovementData* movement = enemy->MovementData;

        if (enemy->BarbaMaskFlags & 0x08) {
            hp.CurrentHP = enemy->BarbaBodyCurrentHP;
            hp.MaxHP = enemy->BarbaBodyMaxHP;
            hp.IsShell = false;

            return hp;
        }

        hp.CurrentHP = enemy->BarbaMaskHP;
        hp.MaxHP = movement->MaskMaxHP;
        hp.IsShell = true;

        return hp;
    }
    return hp;
}

//     ┌─────────────────────────────────────────────────────────┐
//     │             Show Enemy Name window in game              │
//     └─────────────────────────────────────────────────────────┘
namespace {
    const wchar_t* GetEnemyName(Enemy* enemy) {

        using GetMonsterName = wchar_t* (__cdecl*)(int);

        auto func = reinterpret_cast<GetMonsterName>(Offset::UnitxtGetMonsterName);
        return func(enemy->EnemyNameUnitxtIndex);
    }
}

//     ┌─────────────────────────────────────────────────────────┐
//     │       Call to build Windows full Information enemy      │
//     └─────────────────────────────────────────────────────────┘
TargetWindowResult EnemyHP::BuildTargetWindow(Enemy* enemy, TWindowLockOn* window) {
    TargetWindowResult result{};

    if (!enemy || !window)
        return result;
    EnemyHPInfo hp = GetEnemyHPValues(enemy);

    if (hp.MaxHP <= 0)
        hp.MaxHP = 1;

    const wchar_t* name = GetEnemyName(enemy);

    swprintf(window->TextBuffer, 128, L"%ls%ls\n\nHP: %d / %d", name, hp.IsShell ? L" shell" : L"", hp.CurrentHP, hp.MaxHP);

    result.Text = window->TextBuffer;
    result.MaxHP = hp.MaxHP;
    result.CurrentHP = hp.CurrentHP;
    return result;
}

//     ┌─────────────────────────────────────────────────────────┐
//     │      Call BuildTargetWindowRegisters get value enemy    │
//     └─────────────────────────────────────────────────────────┘
void EnemyHP::BuildTargetWindowRegisters(Enemy* enemy, TWindowLockOn* window, wchar_t** text, int* maxHP, int* currentHP) {

    TargetWindowResult result = BuildTargetWindow(enemy, window);

    if (text)
        *text = result.Text;

    if (maxHP)
        *maxHP = result.MaxHP;

    if (currentHP)
        *currentHP = result.CurrentHP;
}

//     ┌─────────────────────────────────────────────────────────────────────────────────┐
//     │     Call UpdateEnemyHPText for update information value enemy in the window     │
//     └─────────────────────────────────────────────────────────────────────────────────┘
wchar_t* EnemyHP::UpdateEnemyHPText(Enemy* enemy, TWindowLockOn* window) {

    TargetWindowResult result;
    result = BuildTargetWindow(enemy, window);
    return result.Text;
}

//     ┌─────────────────────────────────────────────────────────────────────────────────┐
//     │       Call GetEnemyMaxHP for update information value enemy in the window       │
//     └─────────────────────────────────────────────────────────────────────────────────┘
int EnemyHP::GetEnemyMaxHP(Enemy* enemy)
{
    if (!enemy)
        return 0;

    EnemyHPInfo hp = GetEnemyHPValues(enemy);

    return hp.MaxHP;
}