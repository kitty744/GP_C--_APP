/**
 * Copyright (C) 2026 Trollycat
 * Contains all 'information' about this App
 */

#ifndef APP_INFO_HH
#define APP_INFO_HH

#include "global/base_types.inc"

class AppInfo
{
public:
    AppInfo()
    {
        Name = "Test App";
        Version = "0.0.1";
    }

    PCCHAR getName();
    PCCHAR getVersion();

private:
    PCCHAR Name;
    PCCHAR Version;
};

#endif // APP_INFO_HH