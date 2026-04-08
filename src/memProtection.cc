/**
 * Copyright (c) 2026 Trollycat
 * Memory protection system.
 *
 * Think of this like a safeguard for memory management
 * It will correct mistakes and ensure nothing gets corrupted
 */

#include "main.hh"
#include "guards/memProtection.hh"

#include <cstdlib>
#include <algorithm>

MemProtection GMemProtector;

VOID MemProtection::setProtectionLevel(IN INT p)
{
    protection_level = p;
}

CONST CHAR *MemProtection::getProtectionLevelString()
{
    switch (protection_level)
    {
    case PROTECTION_LEVEL_LOW:
        return "LOW";
    case PROTECTION_LEVEL_MODERATE:
        return "MODERATE";
    case PROTECTION_LEVEL_HIGH:
        return "HIGH";
    case PROTECTION_LEVEL_EXTREME:
        return "EXTREME";
    default:
        return "UNKNOWN";
    }
}

VOID *MemProtection::protected_Malloc(IN SIZE_T size, IN CONST CHAR *file, IN INT line)
{
    SIZE_T total_size = sizeof(MemHeader) + size;
    VOID *raw = std::malloc(total_size);

    if (is_null(raw))
    {
        log_error("MEMORY ALLOCATION FAILURE");
        exit_program(-1);
        return NULL;
    }

    MemHeader *header = (MemHeader *)raw;

    header->size = size;
    header->magic = MAGIC;
    header->file = file;
    header->line = line;
    header->active = TRUE;

    if (protection_level >= PROTECTION_LEVEL_HIGH)
    {
        std::lock_guard<std::mutex> lock(mtx);
        registry.push_back(header);
    }

    return (VOID *)((BYTE *)raw + sizeof(MemHeader));
}

VOID MemProtection::verifyIntegrity(IN VOID *ptr)
{
    if (is_null(ptr))
        return;

    MemHeader *header = (MemHeader *)((BYTE *)ptr - sizeof(MemHeader));

    if (header->magic != MAGIC)
    {
        printf_t("CRITICAL: CORRUPTION AT %p (Allocated %s:%d)\n", ptr, header->file, header->line);
        abort_program();
    }
}

VOID MemProtection::protected_Free(INOUT VOID *ptr)
{
    if (is_null(ptr))
        return;

    MemHeader *header = (MemHeader *)((BYTE *)ptr - sizeof(MemHeader));

    if (protection_level >= PROTECTION_LEVEL_MODERATE)
    {
        verifyIntegrity(ptr);
    }

    if (protection_level >= PROTECTION_LEVEL_HIGH)
    {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = std::find(registry.begin(), registry.end(), header);
        if (it != registry.end())
            registry.erase(it);
    }

    if (protection_level == PROTECTION_LEVEL_EXTREME)
    {
        scrubMemory(ptr, header->size);
    }

    header->magic = 0x0;
    header->active = FALSE;
    std::free(header);
}

VOID MemProtection::scrubMemory(IN VOID *ptr, IN SIZE_T size)
{
    mem_set(ptr, 0xCC, size);
}

VOID MemProtection::auditLeaks()
{
    if (protection_level < PROTECTION_LEVEL_HIGH)
        return;

    std::lock_guard<std::mutex> lock(mtx);
    if (registry.empty())
        return;

    println("--- MEMORY LEAK REPORT ---");
    for (MemHeader *header : registry)
    {
        printf_t("LEAK: %zu bytes (Allocated at %s:%d)\n", header->size, header->file, header->line);
    }
}