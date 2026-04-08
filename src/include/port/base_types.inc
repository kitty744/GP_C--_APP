/**
 * Copyright (c) 2026 Trollycat
 * Defines common capital-case type aliases for the TEST_APP codebase.
 */

#include <cstdint>
#include <cstddef>

typedef bool                BOOL;
typedef char                CHAR;

typedef unsigned char       BYTE;
typedef uint8_t             UBYTE;

typedef int8_t              INT8;
typedef int16_t             INT16;
typedef int32_t             INT32;
typedef int64_t             INT64;

typedef uint8_t             UINT8;
typedef uint16_t            UINT16;
typedef uint32_t            UINT32;
typedef uint64_t            UINT64;

typedef int                 INT;
typedef unsigned int        UINT;

typedef long                LONG;
typedef unsigned long       ULONG;

typedef float               FLOAT;
typedef double              DOUBLE;

typedef size_t              SIZE_T;
typedef intptr_t            INTPTR;
typedef uintptr_t           UINTPTR;

#define IN
#define OUT
#define INOUT
#define OPTIONAL

#define VOID                void
#define CONST               const
#define VOLATILE            volatile
#define STATIC              static
#define EXTERN              extern
#define OVERRIDE            override

#define TEST_APP_API        TEST_APP_EXPORT

#ifndef TRUE
#define TRUE                1
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef NULL
#define NULL                0
#endif