/**
 * Copyright (c) 2026 Trollycat
 * Header file for entry point.
 */

#ifndef TEST_APP_MAIN_HH_
#define TEST_APP_MAIN_HH_

// These #include are global
#include "global/port_def.inc"
#include "global/base_types.inc"
#include "global/base_functions.inc"

// Defines C/C++ style 'main' function parameters
// NOTE: It's not best practice to use a macro, this is will probably be deprecated
#define MAIN_ARGC_ARGV_PARAM IN INT argc, IN CHAR **argv

#endif // TEST_APP_MAIN_HH_