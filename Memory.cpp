#pragma once
#include "Memory.h"
#include <Windows.h>
#include <vector>

namespace Memory {
//     ┌─────────────────────────────────────────────────────────┐
//     │             Call Function bool Write();                 │
//     └─────────────────────────────────────────────────────────┘
 bool Write(void* address,const void* data,size_t size) {

      DWORD oldProtect;

     if (!VirtualProtect(address,size,PAGE_EXECUTE_READWRITE,&oldProtect)){
            return false; 
     }           
          memcpy(address,data,size);
          VirtualProtect(address, size,oldProtect,&oldProtect);
          return true;
  }

//     ┌─────────────────────────────────────────────────────────┐
//     │            Call Function bool WriteByte();              │
//     └─────────────────────────────────────────────────────────┘
 bool WriteByte(uintptr_t address,BYTE value) {
     return Write(reinterpret_cast<void*>(address), &value,sizeof(BYTE));
 }

//     ┌─────────────────────────────────────────────────────────┐
//     │           Call Function bool WriteCall();               │
//     └─────────────────────────────────────────────────────────┘
 bool WriteCall(uintptr_t address,void* function) {
        
    BYTE opcode = 0xE8; DWORD relative =(DWORD)function - (DWORD)address -5;
    
    if (!Write(reinterpret_cast<void*>(address),&opcode, 1)) { 
        return false; 
    } 
    return Write(reinterpret_cast<void*>(address + 1), &relative, sizeof(DWORD));
 }

//     ┌─────────────────────────────────────────────────────────┐
//     │           Call Function bool WriteNOP();                │
//     └─────────────────────────────────────────────────────────┘
 bool WriteNOP(uintptr_t address, size_t count) { 
     std::vector<BYTE> nop(count, 0x90); 
     return Write(reinterpret_cast<void*>(address), nop.data(), count); 
 }

//     ┌─────────────────────────────────────────────────────────┐
//     │           Call Function bool WriteFloat();              │
//     └─────────────────────────────────────────────────────────┘
 bool Memory::WriteFloat(uintptr_t address,float value) { 
     return Write(reinterpret_cast<void*>(address),&value,sizeof(float)); 
 }


//     ┌─────────────────────────────────────────────────────────┐
//     │           Call Function bool WriteDWORD();              │
//     └─────────────────────────────────────────────────────────┘
 bool Memory::WriteDWORD(uintptr_t address,DWORD value) { 
     return Write(reinterpret_cast<void*>(address),&value,sizeof(DWORD)); 
 }


 //     ┌─────────────────────────────────────────────────────────┐
 //     │          Call Function bool WriteCallNop();             │
 //     └─────────────────────────────────────────────────────────┘
 bool Memory::WriteCallNop(uintptr_t address,void* function,size_t size) {
        if (!WriteCall(address, function))
            return false;

        if (size > 5) {return WriteNOP( address + 5, size - 5);}
        return true;
 }

//     ┌─────────────────────────────────────────────────────────┐
//     │           Call Function bool WriteJump();               │
//     └─────────────────────────────────────────────────────────┘
 bool WriteJump(uintptr_t address, void* function) {
      BYTE opcode = 0xE9;
      DWORD relative = (DWORD)function - (DWORD)address - 5;

        if (!Write(reinterpret_cast<void*>(address), &opcode, 1))
            return false;

        return Write(reinterpret_cast<void*>(address + 1),&relative,sizeof(DWORD));
    }
}