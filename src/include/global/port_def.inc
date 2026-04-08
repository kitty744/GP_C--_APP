/**
 * Copyright (c) 2026 Trollycat
 * This file contains all common portable defs
 * This ensures this file is portable to any compiler
 *
 * This file should only be included ONCE in any file
 * To enforce this, this file will not work if included twice
 * Best practice is to include it LAST in a file
 *
 * Example:
 *  #include "whatever"
 *
 *  // LAST
 *  #include "port_def.inc"
 */

#include "compiler_config.inc"

// TEST_APP_PORT_ is defined after this check
// If this file is included twice, the first include will define TEST_APP_PORT_,
// meaning the second time won't pass this check
#ifdef TEST_APP_PORT_
#error "port_def.inc included multiple times"
#endif
#define TEST_APP_PORT_

// Portable check for gcc-style atomic built-ins
#if TEST_APP_HAVE_BUILTIN(__atomic_load_n)
#define TEST_APP_BUILTIN_ATOMIC 1
#endif

// Portable check for GCC minimum version:
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
#if defined(__GNUC__) && defined(__GNUC_MINOR__) \
    && defined(__GNUC_PATCHLEVEL__)
#  define TEST_APP_GNUC_MIN(x, y) \
  (__GNUC__ > (x) || (__GNUC__ == (x) && __GNUC_MINOR__ >= (y)))
#else
#  define TEST_APP_GNUC_MIN(x, y) 0
#endif

#if defined(__clang__) && defined(__clang_major__) && defined(__clang_minor__)
#define TEST_APP_CLANG_MIN(x, y) \
  (__clang_major__ > (x) || (__clang_major__ == (x) && __clang_minor__ >= (y)))
#else
#define TEST_APP_CLANG_MIN(x, y) 0
#endif

// Portable check for MSVC minimum version:
// https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros
#if defined(_MSC_VER)
#define TEST_APP_MSC_VER_MIN(x) (_MSC_VER >= x)
#else
#define TEST_APP_MSC_VER_MIN(x) 0
#endif

// Portable check for minimum C++ language version:
// https://en.cppreference.com/w/cpp/preprocessor/replace
// https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros
#if !defined(_MSVC_LANG)
#define TEST_APP_CPLUSPLUS_MIN(x) (__cplusplus >= x)
#else
#define TEST_APP_CPLUSPLUS_MIN(x) (_MSVC_LANG >= x)
#endif

// Future versions of test_app will include breaking changes to some APIs.
// This macro can be set to enable these API changes ahead of time, so that
// user code can be updated before upgrading versions of test_app.

#ifdef TEST_APP_FUTURE_BREAKING_CHANGES
#define TEST_APP_FUTURE_DESCRIPTOR_EXTENSION_DECL 1
#define TEST_APP_FUTURE_ADD_NODISCARD [[nodiscard]]
#else
#define TEST_APP_FUTURE_ADD_NODISCARD
#endif


#define TEST_APP_FUTURE_ADD_EARLY_NODISCARD [[nodiscard]]
#define TEST_APP_FUTURE_ADD_EARLY_WARN_UNUSED TEST_APP_ATTRIBUTE_WARN_UNUSED

#ifdef TEST_APP_ALWAYS_INLINE
#error TEST_APP_ALWAYS_INLINE was previously defined
#endif
// For functions we want to force inline.
#if defined(TEST_APP_NO_INLINE)
#define TEST_APP_ALWAYS_INLINE inline
#elif defined(__GNUC__)
#define TEST_APP_ALWAYS_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#define TEST_APP_ALWAYS_INLINE __forceinline
#else
#define TEST_APP_ALWAYS_INLINE inline
#endif

#ifdef TEST_APP_ALWAYS_INLINE_CALL
#error TEST_APP_ALWAYS_INLINE_CALL was previously defined
#endif

// For functions we want to force inline from the caller, instead of in the
// declaration of the callee.
// This is useful for lambdas where it is not easy to specify ALWAYS_INLINE.
// Use like:
//   TEST_APP_ALWAYS_INLINE_CALL res = SomeFunc(args...);
#if defined(__clang__) && !defined(TEST_APP_NO_INLINE_CALL) && \
    TEST_APP_HAVE_CPP_ATTRIBUTE(clang::always_inline)
#define TEST_APP_ALWAYS_INLINE_CALL [[clang::always_inline]]
#else
#define TEST_APP_ALWAYS_INLINE_CALL
#endif

#ifdef TEST_APP_NDEBUG_INLINE
#error TEST_APP_NDEBUG_INLINE was previously defined
#endif
// Avoid excessive inlining in non-optimized builds. Without other optimizations
// the inlining is not going to provide benefits anyway and the huge resulting
// functions, especially in the test-app-generated serialization functions, produce
// stack frames so large that many tests run into stack overflows (b/32192897).
#if defined(NDEBUG) || (defined(_MSC_VER) && !defined(_DEBUG))
# define TEST_APP_NDEBUG_INLINE TEST_APP_ALWAYS_INLINE
#else
#define TEST_APP_NDEBUG_INLINE inline
#endif


// Note that TEST_APP_NOINLINE is an attribute applied to functions, to prevent
// them from being inlined by the compiler. This is different from
// TEST_APP_NO_INLINE, which is a user-supplied macro that disables forced
// inlining by TEST_APP_(ALWAYS|NDEBUG)_INLINE.
//
// For forward-declared functions, make sure to apply TEST_APP_NOINLINE to all
// the declarations, not just the definition, or else whole-program optimization
// may not honor the attribute.
#ifdef TEST_APP_NOINLINE
#error TEST_APP_NOINLINE was previously defined
#endif
#if defined(__GNUC__)
# define TEST_APP_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
// Seems to have been around since at least Visual Studio 2005
# define TEST_APP_NOINLINE __declspec(noinline)
#endif

#ifdef TEST_APP_MUSTTAIL
#error TEST_APP_MUSTTAIL was previously defined
#endif
#ifdef TEST_APP_TAILCALL
#error TEST_APP_TAILCALL was previously defined
#endif
#if TEST_APP_HAVE_CPP_ATTRIBUTE(clang::musttail) && (defined(__aarch64__) || \
    defined(__x86_64__) || defined(_M_X64))
// Compilation fails on ARM32: b/195943306
// Compilation fails on powerpc64le: b/187985113
// Compilation fails on X86 Windows:
// https://github.com/llvm/llvm-project/issues/53271
#define TEST_APP_MUSTTAIL [[clang::musttail]]
#define TEST_APP_TAILCALL true
#else
#define TEST_APP_MUSTTAIL
#define TEST_APP_TAILCALL false
#endif

// On windows, you need to hint to the compiler that you want to do empty base
// class optimization with multiple inheritance.
#ifdef _MSC_VER
#define TEST_APP_DECLSPEC_EMPTY_BASES __declspec(empty_bases)
#else
#define TEST_APP_DECLSPEC_EMPTY_BASES
#endif

#ifdef TEST_APP_CC
#error TEST_APP_CC was previously defined
#endif
#define TEST_APP_CC

#if defined(__clang__)
#define TEST_APP_IGNORE_DEPRECATION_START                     \
  _Pragma("clang diagnostic push")                                  \
  _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#define TEST_APP_IGNORE_DEPRECATION_STOP                     \
  _Pragma("clang diagnostic pop")
#elif defined(__GNUC__)
#define TEST_APP_IGNORE_DEPRECATION_START                     \
  _Pragma("GCC diagnostic push")                                  \
  _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#define TEST_APP_IGNORE_DEPRECATION_STOP                     \
  _Pragma("GCC diagnostic pop")
#else
#define TEST_APP_IGNORE_DEPRECATION_START
#define TEST_APP_IGNORE_DEPRECATION_STOP
#endif

#ifdef TEST_APP_RTTI
#error TEST_APP_RTTI was previously defined
#endif
#if defined(TEST_APP_NO_RTTI) && TEST_APP_NO_RTTI
// A user-provided definition TEST_APP_NO_RTTI=1 disables RTTI.
#define TEST_APP_RTTI 0
#elif defined(__cpp_rtti)
// https://en.cppreference.com/w/cpp/feature_test
#define TEST_APP_RTTI 1
#elif TEST_APP_HAVE_FEATURE(cxx_rtti)
// https://clang.llvm.org/docs/LanguageExtensions.html#c-rtti
#define TEST_APP_RTTI 1
#elif defined(__GXX_RTTI)
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
#define TEST_APP_RTTI 1
#elif defined(_CPPRTTI)
// https://docs.microsoft.com/en-us/cpp/build/reference/gr-enable-run-time-type-information
#define TEST_APP_RTTI 1
#else
#define TEST_APP_RTTI 0
#endif

#ifdef TEST_APP_FIELD_OFFSET
#error TEST_APP_FIELD_OFFSET was previously defined
#endif
#if defined(__clang__)
#define TEST_APP_FIELD_OFFSET(TYPE, FIELD)                   \
  _Pragma("clang diagnostic push")                           \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(TYPE, FIELD)                            \
  _Pragma("clang diagnostic pop")
#elif defined(__GNUC__) || defined(_MSC_VER)
#define TEST_APP_FIELD_OFFSET(TYPE, FIELD) __builtin_offsetof(TYPE, FIELD)
#else
#define TEST_APP_FIELD_OFFSET(TYPE, FIELD)                                \
  static_cast< ::uint32_t>(reinterpret_cast<const char*>(                    \
                               &reinterpret_cast<const TYPE*>(16)->FIELD) - \
                           reinterpret_cast<const char*>(16))
#endif

#ifdef TEST_APP_EXPORT
#error TEST_APP_EXPORT was previously defined
#endif

#if defined(TEST_APP_USE_DLLS) && defined(_MSC_VER)
# if defined(LIBTEST_APP_EXPORTS)
#  define TEST_APP_EXPORT __declspec(dllexport)
#  define TEST_APP_EXPORT_TEMPLATE_DECLARE
#  define TEST_APP_EXPORT_TEMPLATE_DEFINE __declspec(dllexport)
# else
#  define TEST_APP_EXPORT __declspec(dllimport)
#  define TEST_APP_EXPORT_TEMPLATE_DECLARE
#  define TEST_APP_EXPORT_TEMPLATE_DEFINE __declspec(dllimport)
# endif
#elif defined(TEST_APP_USE_DLLS) && defined(LIBTEST_APP_EXPORTS)
# define TEST_APP_EXPORT __attribute__((visibility("default")))
# define TEST_APP_EXPORT_TEMPLATE_DECLARE __attribute__((visibility("default")))
# define TEST_APP_EXPORT_TEMPLATE_DEFINE
#else
# define TEST_APP_EXPORT
# define TEST_APP_EXPORT_TEMPLATE_DECLARE
# define TEST_APP_EXPORT_TEMPLATE_DEFINE
#endif

#ifdef TEST_APP_RESTRICT
#error TEST_APP_RESTRICT was previously defined
#endif
#if defined( __clang__) || defined(__GNUC__)
#define TEST_APP_RESTRICT __restrict
#else
#define TEST_APP_RESTRICT
#endif

#ifdef TEST_APP_ALIGNAS
#error TEST_APP_ALIGNAS was previously defined
#endif
#if defined(_MSC_VER)
#define TEST_APP_ALIGNAS(byte_alignment) __declspec(align(byte_alignment))
#elif defined(__GNUC__)
#define TEST_APP_ALIGNAS(byte_alignment) \
  __attribute__((aligned(byte_alignment)))
#else
#define TEST_APP_ALIGNAS(byte_alignment) alignas(byte_alignment)
#endif

#ifdef TEST_APP_THREAD_LOCAL
#error TEST_APP_THREAD_LOCAL was previously defined
#endif
#if defined(_MSC_VER)
#define TEST_APP_THREAD_LOCAL __declspec(thread)
#else
#define TEST_APP_THREAD_LOCAL __thread
#endif

#ifdef TEST_APP_CONSTINIT
#error TEST_APP_CONSTINIT was previously defined
#endif

#if defined(TEST_APP_USE_DLLS) && (defined(_WIN32) || defined(__CYGWIN__))
#define TEST_APP_CONSTINIT
#elif defined(_MSC_VER) && !defined(__clang__)
#define TEST_APP_CONSTINIT
#elif defined(__GNUC__) && !defined(__clang__)
#define TEST_APP_CONSTINIT
#elif defined(__cpp_constinit)
#define TEST_APP_CONSTINIT constinit
#define TEST_APP_CONSTINIT_DEFAULT_INSTANCES
#elif TEST_APP_HAVE_CPP_ATTRIBUTE(clang::require_constant_initialization) && \
    ((defined(__APPLE__) && TEST_APP_CLANG_MIN(13, 0)) ||                \
     (!defined(__APPLE__) && TEST_APP_CLANG_MIN(12, 0)))
#define TEST_APP_CONSTINIT [[clang::require_constant_initialization]]
#define TEST_APP_CONSTINIT_DEFAULT_INSTANCES
#else
#define TEST_APP_CONSTINIT
#endif

#ifdef TEST_APP_ATTRIBUTE_NO_DESTROY
#error TEST_APP_ATTRIBUTE_NO_DESTROY was previously defined
#endif
#if TEST_APP_HAVE_CPP_ATTRIBUTE(clang::no_destroy)
#define TEST_APP_ATTRIBUTE_NO_DESTROY [[clang::no_destroy]]
#else
#define TEST_APP_ATTRIBUTE_NO_DESTROY
#endif

#ifdef TEST_APP_ATTRIBUTE_INIT_PRIORITY1
#error TEST_APP_ATTRIBUTE_INIT_PRIORITY1 was previously defined
#endif
#ifdef TEST_APP_ATTRIBUTE_INIT_PRIORITY2
#error TEST_APP_ATTRIBUTE_INIT_PRIORITY2 was previously defined
#endif
#if defined(__GNUC__) && (!defined(__APPLE__) || defined(__clang__)) && \
    !((defined(sun) || defined(__sun)) &&                                     \
      (defined(__SVR4) || defined(__svr4__)))
#define TEST_APP_ATTRIBUTE_INIT_PRIORITY1 __attribute__((init_priority((101))))
#define TEST_APP_ATTRIBUTE_INIT_PRIORITY2 __attribute__((init_priority((102))))
#else
#define TEST_APP_ATTRIBUTE_INIT_PRIORITY1
#define TEST_APP_ATTRIBUTE_INIT_PRIORITY2
#endif

#ifdef TEST_APP_PRAGMA_INIT_SEG
#error TEST_APP_PRAGMA_INIT_SEG was previously defined
#endif
#ifdef _MSC_VER
#define TEST_APP_PRAGMA_INIT_SEG __pragma(init_seg(lib))
#else
#define TEST_APP_PRAGMA_INIT_SEG
#endif

#ifdef TEST_APP_ATTRIBUTE_WEAK
#error TEST_APP_ATTRIBUTE_WEAK was previously defined
#endif
#if TEST_APP_HAVE_ATTRIBUTE_WEAK && !defined(__APPLE__) && \
    (!defined(_WIN32) || __clang_major__ < 9) && !defined(__MINGW32__)
#define TEST_APP_ATTRIBUTE_WEAK __attribute__((weak))
#define TEST_APP_HAVE_ATTRIBUTE_WEAK_INTERNAL 1
#else
#define TEST_APP_ATTRIBUTE_WEAK
#define TEST_APP_HAVE_ATTRIBUTE_WEAK_INTERNAL 0
#endif

#if TEST_APP_HAVE_THREAD_SANITIZER
#define TEST_APP_TSAN_DECLARE_MEMBER char _tsan_detect_race = 0;
#else
#define TEST_APP_TSAN_DECLARE_MEMBER
#endif

#define TEST_APP_TC_PARAM_DECL                 \
  ::test_app::MessageLite *msg, const char *ptr, \
      ::test_app::internal::ParseContext *ctx,   \
      ::test_app::internal::TcFieldData data,    \
      const ::test_app::internal::TcParseTableBase *table, uint64_t hasbits
#define TEST_APP_TC_PARAM_PASS msg, ptr, ctx, data, table, hasbits

#ifdef TEST_APP_BUILTIN_CONSTANT_P
#error TEST_APP_BUILTIN_CONSTANT_P was previously defined
#endif
#if TEST_APP_HAVE_BUILTIN(__builtin_constant_p)
#define TEST_APP_BUILTIN_CONSTANT_P(x) __builtin_constant_p(x)
#else
#define TEST_APP_BUILTIN_CONSTANT_P(x) false
#endif

#ifdef TEST_APP_VIRTUAL
#error TEST_APP_VIRTUAL was previously defined
#endif
#define TEST_APP_VIRTUAL virtual
#define TEST_APP_OVERRIDE override
#define TEST_APP_FINAL final

#ifdef TEST_APP_PREFETCH_WITH_OFFSET
#error TEST_APP_PREFETCH_WITH_OFFSET was previously defined
#endif
#if defined(__x86_64__) && defined(__GNUC__)
#define TEST_APP_PREFETCH_WITH_OFFSET(base, offset) \
  asm("prefetcht0 " #offset "(%0)" : : "r"(base));
#else
#define TEST_APP_PREFETCH_WITH_OFFSET(base, offset)
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic error "-Wdeprecated-enum-enum-conversion"
#pragma clang diagnostic error "-Wconstant-conversion"
#pragma clang diagnostic error "-Wunused-label"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wextra-semi"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#pragma GCC diagnostic ignored "-Wunused-lambda-capture"
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wshadow"
#ifndef __clang__
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#pragma GCC diagnostic ignored "-Wself-move"
#pragma GCC diagnostic ignored "-Wpedantic"
#endif
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4582)
#pragma warning(disable : 4583)
#pragma warning(disable : 4073)
#pragma warning(disable : 5031)
#pragma warning(disable: 4127)
#pragma warning(disable: 4125)
#endif

namespace test_app {
namespace internal {
[[noreturn]] TEST_APP_EXPORT void test_app_assumption_failed(const char *pred,
                                                             const char *file,
                                                             int line);
}
}

#ifdef TEST_APP_ASSUME
#error TEST_APP_ASSUME was previously defined
#endif
#if TEST_APP_HAVE_BUILTIN(__builtin_assume)
#ifdef NDEBUG
#define TEST_APP_ASSUME(pred) __builtin_assume(pred)
#else
#define TEST_APP_ASSUME(pred)                                                  \
  if (!(pred)) {                                                               \
    ::test_app::internal::test_app_assumption_failed(#pred, __FILE__, __LINE__); \
  }                                                                            \
  __builtin_assume(pred)
#endif
#else
#ifndef NDEBUG
#define TEST_APP_ASSUME(pred)                                                  \
  if (!(pred)) {                                                               \
    ::test_app::internal::test_app_assumption_failed(#pred, __FILE__, __LINE__); \
  }
#else
#define TEST_APP_ASSUME(pred)
#endif
#endif

#if TEST_APP_HAVE_BUILTIN(__builtin_expect_with_probability)
#define TEST_APP_EXPECT_TRUE_WITH_PROBABILITY(expr, prob) \
  __builtin_expect_with_probability((expr), 1, (prob))
#else
#define TEST_APP_EXPECT_TRUE_WITH_PROBABILITY(expr, prob) (expr)
#endif

#define TEST_APP_DEPRECATE_AND_INLINE() [[deprecated]]
#define TEST_APP_NONNULL
#define TEST_APP_NULLABLE
#define TEST_APP_NO_MERGE
#define TEST_APP_PRESERVE_ALL