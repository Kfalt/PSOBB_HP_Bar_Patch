#pragma once

#include <Windows.h>

namespace Memory
{
    bool Write(void* address, const void* data, size_t size);
    bool WriteByte(uintptr_t address, BYTE value);
    bool WriteCall(uintptr_t address, void* function);
    bool WriteJump(uintptr_t address, void* function);
    bool WriteNOP(uintptr_t address, size_t count);
    bool WriteFloat(uintptr_t address, float value);
    bool WriteDWORD(uintptr_t address, DWORD value);
    bool WriteCallNop(uintptr_t address, void* function, size_t size);
}