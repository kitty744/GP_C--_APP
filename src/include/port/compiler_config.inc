/**
 * Copyright (c) 2026 Trollycat
 * This file contains macros for compiler configurations
 */

#ifndef TEST_APP_COMPILER_CONFIG_INC_
#define TEST_APP_COMPILER_CONFIG_INC_

// 1. Built-in detector
#ifndef TEST_APP_HAVE_BUILTIN
#ifdef __has_builtin
#define TEST_APP_HAVE_BUILTIN(x) __has_builtin(x)
#else
#define TEST_APP_HAVE_BUILTIN(x) 0
#endif
#endif

// 2. Attribute detector
#ifndef TEST_APP_HAVE_ATTRIBUTE
#ifdef __has_attribute
#define TEST_APP_HAVE_ATTRIBUTE(x) __has_attribute(x)
#else
#define TEST_APP_HAVE_ATTRIBUTE(x) 0
#endif
#endif

#ifndef TEST_APP_HAVE_ATTRIBUTE_WEAK
#if TEST_APP_HAVE_ATTRIBUTE(weak)
#define TEST_APP_HAVE_ATTRIBUTE_WEAK 1
#else
#define TEST_APP_HAVE_ATTRIBUTE_WEAK 0
#endif
#endif

#if TEST_APP_HAVE_ATTRIBUTE(warn_unused_result) || (defined(__GNUC__) && !defined(__clang__))
#define TEST_APP_ATTRIBUTE_WARN_UNUSED __attribute__((warn_unused_result))
#elif defined(_MSC_VER) && _MSC_VER >= 1700
#define TEST_APP_ATTRIBUTE_WARN_UNUSED _Check_return_
#else
#define TEST_APP_ATTRIBUTE_WARN_UNUSED
#endif


#ifndef TEST_APP_HAVE_CPP_ATTRIBUTE
#ifdef __has_cpp_attribute
#define TEST_APP_HAVE_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define TEST_APP_HAVE_CPP_ATTRIBUTE(x) 0
#endif
#endif

// 3. Feature detector
#ifndef TEST_APP_HAVE_FEATURE
#ifdef __has_feature
#define TEST_APP_HAVE_FEATURE(x) __has_feature(x)
#else
#define TEST_APP_HAVE_FEATURE(x) 0
#endif
#endif

#ifndef TEST_APP_HAVE_THREAD_SANITIZER
#if defined(__has_feature)
#if __has_feature(thread_sanitizer)
#define TEST_APP_HAVE_THREAD_SANITIZER 1
#endif
#endif
#ifndef TEST_APP_HAVE_THREAD_SANITIZER
#define TEST_APP_HAVE_THREAD_SANITIZER 0
#endif
#endif

#endif // TEST_APP_COMPILER_CONFIG_INC_