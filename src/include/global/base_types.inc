/**
 * Copyright (c) 2026 Trollycat
 */

#pragma once

#include <cstdint>
#include <cstddef>
#include <cwchar>

#if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__) || defined(__LP64__) || defined(_M_X64) || defined(_M_ARM64)
    #define TEST_APP_64BIT 1
    #define TEST_APP_32BIT 0
#else
    #define TEST_APP_64BIT 0
    #define TEST_APP_32BIT 1
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define TEST_APP_PLATFORM_WINDOWS 1
#elif defined(__linux__)
    #define TEST_APP_PLATFORM_LINUX 1
#elif defined(__APPLE__)
    #define TEST_APP_PLATFORM_APPLE 1
#endif

#define IN
#define OUT
#define INOUT
#define OPTIONAL

#define VOID                void
#define CONST               const
#define VOLATILE            volatile
#define STATIC              static
#define EXTERN              extern

#define OVERRIDE            TEST_APP_OVERRIDE
#define FINAL               TEST_APP_FINAL
#define VIRTUAL             TEST_APP_VIRTUAL
#define FORCEINLINE         TEST_APP_ALWAYS_INLINE
#define NOINLINE            TEST_APP_NOINLINE
#define RESTRICT            TEST_APP_RESTRICT
#define ALIGNAS(n)          TEST_APP_ALIGNAS(n)

#define TEST_APP_API        TEST_APP_EXPORT

#ifndef TRUE
    #define TRUE            1
#endif

#ifndef FALSE
    #define FALSE           0
#endif

#ifndef NULL
    #define NULL            0
#endif

#ifndef NULLPTR
    #define NULLPTR         nullptr
#endif

typedef bool                BOOL;
typedef char                CHAR;
typedef wchar_t             WCHAR;
typedef char16_t            CHAR16;
typedef char32_t            CHAR32;

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

typedef short               SHORT;
typedef unsigned short      USHORT;

typedef long                LONG;
typedef unsigned long       ULONG;

typedef long long           LONGLONG;
typedef unsigned long long  ULONGLONG;

typedef uint16_t            WORD;

#if TEST_APP_PLATFORM_WINDOWS
    #if TEST_APP_64BIT
        typedef unsigned long       DWORD;
        typedef unsigned long       DWORD32;
        typedef unsigned long long  DWORD64;
        typedef long long           LONG_PTR;
        typedef unsigned long long  ULONG_PTR;
        typedef long long           INT_PTR;
        typedef unsigned long long  UINT_PTR;
        typedef long long           HALF_PTR;
        typedef unsigned long long  UHALF_PTR;
        typedef long long           LONG64;
        typedef unsigned long long  ULONG64;
        typedef unsigned long long  DWORD_PTR;
    #else
        typedef unsigned long       DWORD;
        typedef unsigned long       DWORD32;
        typedef unsigned long long  DWORD64;
        typedef long                LONG_PTR;
        typedef unsigned long       ULONG_PTR;
        typedef int                 INT_PTR;
        typedef unsigned int        UINT_PTR;
        typedef short               HALF_PTR;
        typedef unsigned short      UHALF_PTR;
        typedef long                LONG64;
        typedef unsigned long       ULONG64;
        typedef unsigned long       DWORD_PTR;
    #endif
#else
    #if TEST_APP_64BIT
        typedef uint32_t            DWORD;
        typedef uint32_t            DWORD32;
        typedef uint64_t            DWORD64;
        typedef int64_t             LONG_PTR;
        typedef uint64_t            ULONG_PTR;
        typedef int64_t             INT_PTR;
        typedef uint64_t            UINT_PTR;
        typedef int32_t             HALF_PTR;
        typedef uint32_t            UHALF_PTR;
        typedef int64_t             LONG64;
        typedef uint64_t            ULONG64;
        typedef uint64_t            DWORD_PTR;
    #else
        typedef uint32_t            DWORD;
        typedef uint32_t            DWORD32;
        typedef uint64_t            DWORD64;
        typedef int32_t             LONG_PTR;
        typedef uint32_t            ULONG_PTR;
        typedef int32_t             INT_PTR;
        typedef uint32_t            UINT_PTR;
        typedef int16_t             HALF_PTR;
        typedef uint16_t            UHALF_PTR;
        typedef int32_t             LONG64;
        typedef uint32_t            ULONG64;
        typedef uint32_t            DWORD_PTR;
    #endif
#endif

typedef size_t              SIZE_T;
typedef ptrdiff_t           SSIZE_T;
typedef intptr_t            INTPTR;
typedef uintptr_t           UINTPTR;

#if TEST_APP_64BIT
    typedef int64_t         SSIZE;
    typedef uint64_t        USIZE;
    typedef int64_t         REGISTER_TYPE;
    typedef uint64_t        QWORD;
    typedef uint64_t*       PQWORD;
    typedef uint64_t*       LPQWORD;
#else
    typedef int32_t         SSIZE;
    typedef uint32_t        USIZE;
    typedef int32_t         REGISTER_TYPE;
    typedef uint32_t        QWORD;
    typedef uint32_t*       PQWORD;
    typedef uint32_t*       LPQWORD;
#endif

typedef float               FLOAT;
typedef double              DOUBLE;
typedef long double         LDOUBLE;

typedef float               FLOAT32;
typedef double              FLOAT64;

typedef CHAR*               PCHAR;
typedef CHAR*               LPCHAR;
typedef CONST CHAR*         PCCHAR;
typedef CONST CHAR*         LPCCHAR;
typedef CONST CHAR*         PCSTR;
typedef CONST CHAR*         LPCSTR;
typedef CHAR*               PSTR;
typedef CHAR*               LPSTR;

typedef WCHAR*              PWCHAR;
typedef WCHAR*              LPWCHAR;
typedef CONST WCHAR*        PCWCHAR;
typedef CONST WCHAR*        LPCWCHAR;
typedef CONST WCHAR*        PCWSTR;
typedef CONST WCHAR*        LPCWSTR;
typedef WCHAR*              PWSTR;
typedef WCHAR*              LPWSTR;

#if defined(UNICODE) || defined(_UNICODE)
    typedef WCHAR           TCHAR;
    typedef PWSTR           PTSTR;
    typedef LPWSTR          LPTSTR;
    typedef PCWSTR          PCTSTR;
    typedef LPCWSTR         LPCTSTR;
#else
    typedef CHAR            TCHAR;
    typedef PSTR            PTSTR;
    typedef LPSTR           LPTSTR;
    typedef PCSTR           PCTSTR;
    typedef LPCSTR          LPCTSTR;
#endif

typedef BOOL*               PBOOL;
typedef BOOL*               LPBOOL;
typedef BYTE*               PBYTE;
typedef BYTE*               LPBYTE;
typedef CONST BYTE*         PCBYTE;
typedef CONST BYTE*         LPCBYTE;
typedef WORD*               PWORD;
typedef WORD*               LPWORD;
typedef DWORD*              PDWORD;
typedef DWORD*              LPDWORD;
typedef DWORD64*            PDWORD64;
typedef INT*                PINT;
typedef INT*                LPINT;
typedef UINT*               PUINT;
typedef LONG*               PLONG;
typedef LONG*               LPLONG;
typedef ULONG*              PULONG;
typedef LONGLONG*           PLONGLONG;
typedef ULONGLONG*          PULONGLONG;
typedef FLOAT*              PFLOAT;
typedef DOUBLE*             PDOUBLE;
typedef VOID*               PVOID;
typedef VOID*               LPVOID;
typedef CONST VOID*         PCVOID;
typedef CONST VOID*         LPCVOID;
typedef SIZE_T*             PSIZE_T;

typedef INT8*               PINT8;
typedef INT16*              PINT16;
typedef INT32*              PINT32;
typedef INT64*              PINT64;
typedef UINT8*              PUINT8;
typedef UINT16*             PUINT16;
typedef UINT32*             PUINT32;
typedef UINT64*             PUINT64;

#if TEST_APP_PLATFORM_WINDOWS
    typedef ULONG_PTR       HANDLE;
    typedef HANDLE          HMODULE;
    typedef HANDLE          HINSTANCE;
    typedef HANDLE          HWND;
    typedef HANDLE          HMENU;
    typedef HANDLE          HICON;
    typedef HANDLE          HCURSOR;
    typedef HANDLE          HBRUSH;
    typedef HANDLE          HPEN;
    typedef HANDLE          HDC;
    typedef HANDLE          HBITMAP;
    typedef HANDLE          HFONT;
    typedef HANDLE          HFILE;
    typedef HANDLE          HKEY;
    typedef HANDLE          HLOCAL;
    typedef HANDLE          HGLOBAL;
    typedef HANDLE          HRSRC;
    typedef HANDLE          HGDIOBJ;
    typedef HANDLE          HTHREAD;
    typedef HANDLE          HPROCESS;
    typedef HANDLE          HEVENT;
    typedef HANDLE          HMUTEX;
    typedef HANDLE          HSEMAPHORE;
    typedef HANDLE          HPIPE;
    typedef HANDLE*         PHANDLE;
    typedef HANDLE*         LPHANDLE;
    typedef INT_PTR         WPARAM;
    typedef LONG_PTR        LPARAM;
    typedef LONG_PTR        LRESULT;
    typedef UINT            ATOM;
    typedef DWORD           COLORREF;
    typedef DWORD*          LPCOLORREF;
    typedef DWORD           LCID;
    typedef WORD            LANGID;
    typedef DWORD           LCTYPE;
#else
    typedef void*           HANDLE;
    typedef HANDLE          HMODULE;
    typedef HANDLE          HINSTANCE;
    typedef HANDLE          HFILE;
    typedef HANDLE          HKEY;
    typedef HANDLE*         PHANDLE;
    typedef HANDLE*         LPHANDLE;
    typedef UINT32          COLORREF;
    typedef UINT32*         LPCOLORREF;
    typedef UINT32          LCID;
    typedef UINT16          LANGID;
#endif

typedef INT32               HRESULT;
typedef INT32               NTSTATUS;
typedef UINT32              SCODE;
typedef UINT32              FLAGS;
typedef UINT32              MASK;
typedef UINT32              BITFIELD;

#if TEST_APP_64BIT
    typedef UINT64          FLAGS64;
    typedef UINT64          MASK64;
#endif

#if TEST_APP_PLATFORM_WINDOWS
    #define S_OK            ((HRESULT)0x00000000L)
    #define S_FALSE         ((HRESULT)0x00000001L)
    #define E_FAIL          ((HRESULT)0x80004005L)
    #define E_INVALIDARG    ((HRESULT)0x80070057L)
    #define E_OUTOFMEMORY   ((HRESULT)0x8007000EL)
    #define E_NOTIMPL       ((HRESULT)0x80004001L)
    #define E_NOINTERFACE   ((HRESULT)0x80004002L)
    #define E_POINTER       ((HRESULT)0x80004003L)
    #define E_ABORT         ((HRESULT)0x80004004L)
    #define E_ACCESSDENIED  ((HRESULT)0x80070005L)
    #define E_UNEXPECTED    ((HRESULT)0x8000FFFFL)
    #define SUCCEEDED(hr)   (((HRESULT)(hr)) >= 0)
    #define FAILED(hr)      (((HRESULT)(hr)) < 0)
    #define HRESULT_CODE(hr)        ((hr) & 0xFFFF)
    #define HRESULT_FACILITY(hr)    (((hr) >> 16) & 0x1FFF)
    #define HRESULT_SEVERITY(hr)    (((hr) >> 31) & 0x1)
#endif

#if TEST_APP_64BIT
    #define MAXBYTE         ((BYTE)0xFF)
    #define MAXWORD         ((WORD)0xFFFF)
    #define MAXDWORD        ((DWORD)0xFFFFFFFF)
    #define MAXDWORD64      ((DWORD64)0xFFFFFFFFFFFFFFFFULL)
    #define MAXUINT8        ((UINT8)~((UINT8)0))
    #define MAXUINT16       ((UINT16)~((UINT16)0))
    #define MAXUINT32       ((UINT32)~((UINT32)0))
    #define MAXUINT64       ((UINT64)~((UINT64)0))
    #define MAXINT8         ((INT8)(MAXUINT8 >> 1))
    #define MAXINT16        ((INT16)(MAXUINT16 >> 1))
    #define MAXINT32        ((INT32)(MAXUINT32 >> 1))
    #define MAXINT64        ((INT64)(MAXUINT64 >> 1))
    #define MININT8         ((INT8)~MAXINT8)
    #define MININT16        ((INT16)~MAXINT16)
    #define MININT32        ((INT32)~MAXINT32)
    #define MININT64        ((INT64)~MAXINT64)
    #define MAXSIZE_T       ((SIZE_T)(~((SIZE_T)0)))
    #define MAXSSIZE_T      ((SSIZE_T)(MAXSIZE_T >> 1))
    #define MINSSIZE_T      ((SSIZE_T)~MAXSSIZE_T)
    #define MAXULONG_PTR    ((ULONG_PTR)~((ULONG_PTR)0))
    #define MAXLONG_PTR     ((LONG_PTR)(MAXULONG_PTR >> 1))
    #define MINLONG_PTR     ((LONG_PTR)~MAXLONG_PTR)
#else
    #define MAXBYTE         ((BYTE)0xFF)
    #define MAXWORD         ((WORD)0xFFFF)
    #define MAXDWORD        ((DWORD)0xFFFFFFFFUL)
    #define MAXDWORD64      ((DWORD64)0xFFFFFFFFFFFFFFFFULL)
    #define MAXUINT8        ((UINT8)~((UINT8)0))
    #define MAXUINT16       ((UINT16)~((UINT16)0))
    #define MAXUINT32       ((UINT32)~((UINT32)0))
    #define MAXUINT64       ((UINT64)~((UINT64)0))
    #define MAXINT8         ((INT8)(MAXUINT8 >> 1))
    #define MAXINT16        ((INT16)(MAXUINT16 >> 1))
    #define MAXINT32        ((INT32)(MAXUINT32 >> 1))
    #define MAXINT64        ((INT64)(MAXUINT64 >> 1))
    #define MININT8         ((INT8)~MAXINT8)
    #define MININT16        ((INT16)~MAXINT16)
    #define MININT32        ((INT32)~MAXINT32)
    #define MININT64        ((INT64)~MAXINT64)
    #define MAXSIZE_T       ((SIZE_T)(~((SIZE_T)0)))
    #define MAXSSIZE_T      ((SSIZE_T)(MAXSIZE_T >> 1))
    #define MINSSIZE_T      ((SSIZE_T)~MAXSSIZE_T)
    #define MAXULONG_PTR    ((ULONG_PTR)~((ULONG_PTR)0))
    #define MAXLONG_PTR     ((LONG_PTR)(MAXULONG_PTR >> 1))
    #define MINLONG_PTR     ((LONG_PTR)~MAXLONG_PTR)
#endif

#define MAKEBYTE(lo, hi)        ((BYTE)(((BYTE)(lo)) | ((BYTE)((BYTE)(hi)) << 4)))
#define MAKEWORD(lo, hi)        ((WORD)(((BYTE)(lo)) | ((WORD)((BYTE)(hi))) << 8))
#define MAKELONG(lo, hi)        ((LONG)(((WORD)(lo)) | ((DWORD)((WORD)(hi))) << 16))
#define MAKEDWORD(lo, hi)       ((DWORD)(((WORD)(lo)) | ((DWORD)((WORD)(hi))) << 16))
#define MAKEQWORD(lo, hi)       ((QWORD)(((DWORD)(lo)) | ((QWORD)((DWORD)(hi))) << 32))

#define LOBYTE(w)               ((BYTE)((DWORD_PTR)(w) & 0xFF))
#define HIBYTE(w)               ((BYTE)(((DWORD_PTR)(w) >> 8) & 0xFF))
#define LOWORD(dw)              ((WORD)((DWORD_PTR)(dw) & 0xFFFF))
#define HIWORD(dw)              ((WORD)(((DWORD_PTR)(dw) >> 16) & 0xFFFF))
#define LODWORD(qw)             ((DWORD)((QWORD)(qw) & 0xFFFFFFFF))
#define HIDWORD(qw)             ((DWORD)(((QWORD)(qw) >> 32) & 0xFFFFFFFF))

#if TEST_APP_PLATFORM_WINDOWS
    #define MAKELPARAM(lo, hi)  ((LPARAM)(DWORD)(((WORD)(lo)) | ((DWORD)((WORD)(hi))) << 16))
    #define MAKEWPARAM(lo, hi)  ((WPARAM)(DWORD)(((WORD)(lo)) | ((DWORD)((WORD)(hi))) << 16))
    #define MAKELRESULT(lo, hi) ((LRESULT)(DWORD)(((WORD)(lo)) | ((DWORD)((WORD)(hi))) << 16))
#endif

#define ALIGNUP(val, align)         (((val) + ((align) - 1)) & ~((align) - 1))
#define ALIGNDOWN(val, align)       ((val) & ~((align) - 1))
#define ISALIGNED(val, align)       (((val) & ((align) - 1)) == 0)
#define ALIGNUP_PTR(p, a)           ((PVOID)(ALIGNUP((UINTPTR)(p), (a))))
#define ALIGNDOWN_PTR(p, a)         ((PVOID)(ALIGNDOWN((UINTPTR)(p), (a))))

#define COUNTOF(arr)                (sizeof(arr) / sizeof((arr)[0]))
#define FIELDOFFSET(type, field)    TEST_APP_FIELD_OFFSET(type, field)
#define FIELDSIZE(type, field)      (sizeof(((type*)0)->field))
#define CONTAINING_RECORD(addr, type, field) \
    ((type*)((BYTE*)(addr) - FIELDOFFSET(type, field)))

#define BITS_PER_BYTE               8
#define BITS_PER_WORD               (sizeof(WORD)  * BITS_PER_BYTE)
#define BITS_PER_DWORD              (sizeof(DWORD) * BITS_PER_BYTE)
#define BITS_PER_QWORD              (sizeof(QWORD) * BITS_PER_BYTE)

#if TEST_APP_64BIT
    #define BITS_PER_PTR            64
    #define BYTES_PER_PTR           8
    #define PTR_SIZE                8
    #define PTR_ALIGN               8
#else
    #define BITS_PER_PTR            32
    #define BYTES_PER_PTR           4
    #define PTR_SIZE                4
    #define PTR_ALIGN               4
#endif

#if TEST_APP_PLATFORM_WINDOWS && TEST_APP_64BIT
    #define CACHE_LINE_SIZE         64
    #define PAGE_SIZE               4096
    #define LARGE_PAGE_SIZE         (2 * 1024 * 1024)
#elif TEST_APP_PLATFORM_WINDOWS
    #define CACHE_LINE_SIZE         64
    #define PAGE_SIZE               4096
    #define LARGE_PAGE_SIZE         (4 * 1024 * 1024)
#elif TEST_APP_PLATFORM_LINUX && TEST_APP_64BIT
    #define CACHE_LINE_SIZE         64
    #define PAGE_SIZE               4096
    #define LARGE_PAGE_SIZE         (2 * 1024 * 1024)
#elif TEST_APP_PLATFORM_LINUX
    #define CACHE_LINE_SIZE         32
    #define PAGE_SIZE               4096
    #define LARGE_PAGE_SIZE         (4 * 1024 * 1024)
#else
    #define CACHE_LINE_SIZE         64
    #define PAGE_SIZE               4096
    #define LARGE_PAGE_SIZE         (2 * 1024 * 1024)
#endif

#define BIT(n)                      (1UL << (n))
#define BIT64(n)                    (1ULL << (n))
#define SETBIT(val, n)              ((val) |=  BIT(n))
#define CLRBIT(val, n)              ((val) &= ~BIT(n))
#define TGLBIT(val, n)              ((val) ^=  BIT(n))
#define TSTBIT(val, n)              (((val) >> (n)) & 1)
#define SETFLAG(val, flag)          ((val) |=  (flag))
#define CLRFLAG(val, flag)          ((val) &= ~(flag))
#define TGLFLAG(val, flag)          ((val) ^=  (flag))
#define TSTFLAG(val, flag)          (((val) & (flag)) != 0)

static_assert(sizeof(BYTE)   == 1, "BYTE must be 1 byte");
static_assert(sizeof(WORD)   == 2, "WORD must be 2 bytes");
static_assert(sizeof(DWORD)  == 4, "DWORD must be 4 bytes");
static_assert(sizeof(UINT8)  == 1, "UINT8 must be 1 byte");
static_assert(sizeof(UINT16) == 2, "UINT16 must be 2 bytes");
static_assert(sizeof(UINT32) == 4, "UINT32 must be 4 bytes");
static_assert(sizeof(UINT64) == 8, "UINT64 must be 8 bytes");
static_assert(sizeof(INT8)   == 1, "INT8 must be 1 byte");
static_assert(sizeof(INT16)  == 2, "INT16 must be 2 bytes");
static_assert(sizeof(INT32)  == 4, "INT32 must be 4 bytes");
static_assert(sizeof(INT64)  == 8, "INT64 must be 8 bytes");

#if TEST_APP_64BIT
    static_assert(sizeof(PVOID)     == 8, "PVOID must be 8 bytes on 64-bit");
    static_assert(sizeof(SIZE_T)    == 8, "SIZE_T must be 8 bytes on 64-bit");
    static_assert(sizeof(ULONG_PTR) == 8, "ULONG_PTR must be 8 bytes on 64-bit");
#else
    static_assert(sizeof(PVOID)     == 4, "PVOID must be 4 bytes on 32-bit");
    static_assert(sizeof(SIZE_T)    == 4, "SIZE_T must be 4 bytes on 32-bit");
    static_assert(sizeof(ULONG_PTR) == 4, "ULONG_PTR must be 4 bytes on 32-bit");
#endif
