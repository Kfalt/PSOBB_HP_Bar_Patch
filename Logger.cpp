#pragma once

#include "Logger.h"
#include <cstdio>
#include <cstdarg>
#include <Windows.h>

namespace Logger
{
    static FILE* File = nullptr;


    void Init()
    {
        fopen_s(&File, "HP_Bar_Patch.log", "w");

        if (File)
        {
            fprintf(File, "=== HP Bar Patch Log ===\n");
            fflush(File);
        }
    }


    void Write(const char* format, ...)
    {
        if (!File)
            return;

        va_list args;

        va_start(args, format);

        vfprintf(File, format, args);

        va_end(args);

        fflush(File);
    }
}