/**
 * Copyright (c) 2026 Trollycat
 * Entry point file.
 */

#include "main.hh"
#include "guards/memProtection.hh"

#include "appInfo.hh"

INT main()
{
    AppInfo ai = AppInfo();

    printf("%s\n", ai.getName());
    printf("%s\n", ai.getVersion());
}

#include "global/port_undef.inc"