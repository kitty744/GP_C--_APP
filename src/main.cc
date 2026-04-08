/**
 * Copyright (c) 2026 Trollycat
 * Entry point file.
 */

#include "main.hh"
#include "mem/mem_protection.hh"

INT main(MAIN_ARGC_ARGV_PARAM)
{
    GMemProtector.setProtectionLevel(PROTECTION_LEVEL_MODERATE);
    CHAR *buffer = (CHAR *)MALLOC_SAFE(10);

    for (int i = 0; i < 15; i++)
    {
        buffer[i] = 'X';
    }

    VERIFY_SAFE(buffer);

    return 0;
}

#include "port/port_undef.inc"