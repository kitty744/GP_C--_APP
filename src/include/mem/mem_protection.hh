/**
 * Copyright (c) 2026 Trollycat
 * Memory protection system.
 *
 * Think of this like a safeguard for memory management
 * It will correct mistakes and ensure nothing gets corrupted
 */

#ifndef TEST_APP_MEM_PROTECTION_HH_
#define TEST_APP_MEM_PROTECTION_HH_

#include "../port/base_types.inc"

#include <vector>
#include <mutex>

#define PROTECTION_LEVEL_LOW 0
#define PROTECTION_LEVEL_MODERATE 1
#define PROTECTION_LEVEL_HIGH 2
#define PROTECTION_LEVEL_EXTREME 3

#define MAGIC 0xDEADC0DE

struct MemHeader
{
    SIZE_T size;
    UINT32 magic;
    CONST CHAR *file;
    INT line;
    BOOL active;
};

class MemProtection
{
public:
    VOID setProtectionLevel(IN INT p);
    CONST CHAR *getProtectionLevelString();

    VOID *protected_Malloc(IN SIZE_T size, IN CONST CHAR *file, IN INT line);
    VOID protected_Free(INOUT VOID *ptr);
    VOID verifyIntegrity(IN VOID *ptr);
    VOID auditLeaks();

private:
    INT protection_level = PROTECTION_LEVEL_LOW;

    std::vector<MemHeader *> registry;
    std::mutex mtx;

    VOID scrubMemory(IN VOID *ptr, IN SIZE_T size);
};

extern MemProtection GMemProtector;

#define MALLOC_SAFE(sz) GMemProtector.protected_Malloc(sz, __FILE__, __LINE__)
#define FREE_SAFE(p) GMemProtector.protected_Free(p)
#define VERIFY_SAFE(p) GMemProtector.verifyIntegrity(p)

#endif