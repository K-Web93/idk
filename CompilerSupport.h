//
//  CompilerSupport.h
//  xsw-settings-providers-operationaldata
//
//  Copyright © 2020 VMware, Inc. All rights reserved. This product is protected
//  by copyright and intellectual property laws in the United States and other
//  countries as well as by international treaties. VMware products are covered
//  by one or more patents listed at http://www.vmware.com/go/patents.
//

// Based upon https://github.com/nemequ/hedley
// Created by Evan Nemerson <evan@nemerson.com>
// SPDX-License-Identifier: CC0-1.0

#ifndef XSW_UTIL_COMPILER_SUPPORT_H
#define XSW_UTIL_COMPILER_SUPPORT_H

#include <utility>

#ifdef __cplusplus
extern "C" {
#endif

/** [doc://../../../../../docs/operationaldata/inc/xsw/settings/providers/operationaldata/util/CompilerSupport.md#CompilerSupport-File]
 */

#if defined(__clang__) || defined(__GNUC__)

    // Clang & GCC
    #define XSW_PRAGMA(x) _Pragma(#x)
    #define XSW_DIAGNOSTIC_PRAGMA(x) XSW_PRAGMA(GCC diagnostic x)
    #define XSW_DIAGNOSTIC_PUSH() XSW_DIAGNOSTIC_PRAGMA(push)
    #define XSW_DIAGNOSTIC_POP() XSW_DIAGNOSTIC_PRAGMA(pop)
    #define XSW_DIAGNOSTIC_DISABLE(x) XSW_DIAGNOSTIC_PRAGMA(ignored x)
    #define XSW_HAS_ATTRIBUTE(x) __has_attribute(x)

#elif defined(_MSC_VER)

    // Visual Studio
    #define XSW_PRAGMA(x) __pragma(x)
    #define XSW_DIAGNOSTIC_PRAGMA(x) XSW_PRAGMA(warning(x))
    #define XSW_DIAGNOSTIC_PUSH() XSW_DIAGNOSTIC_PRAGMA(push)
    #define XSW_DIAGNOSTIC_POP() XSW_DIAGNOSTIC_PRAGMA(pop)
    #define XSW_DIAGNOSTIC_DISABLE(x) XSW_DIAGNOSTIC_PRAGMA(disable:x)
    #define XSW_HAS_ATTRIBUTE(x) __has_attribute(x)

#else

    // Compiler unknown
    #define XSW_PRAGMA(x) 
    #define XSW_DIAGNOSTIC_PRAGMA(x)
    #define XSW_DIAGNOSTIC_PUSH()
    #define XSW_DIAGNOSTIC_POP()
    #define XSW_DIAGNOSTIC_DISABLE(x)
    #define XSW_HAS_ATTRIBUTE(x) (0)

#endif

// Version numbers
#define XSW_VERSION(major, minor) (((major) * 1000000) + ((minor) * 1000))
#define XSW_VERSION_GT(a_major, a_minor, b_major, b_minor) XSW_VERSION(a_major, a_minor) >  XSW_VERSION(b_major, b_minor)
#define XSW_VERSION_GE(a_major, a_minor, b_major, b_minor) XSW_VERSION(a_major, a_minor) >= XSW_VERSION(b_major, b_minor)
#define XSW_VERSION_EQ(a_major, a_minor, b_major, b_minor) XSW_VERSION(a_major, a_minor) == XSW_VERSION(b_major, b_minor)
#define XSW_VERSION_LE(a_major, a_minor, b_major, b_minor) XSW_VERSION(a_major, a_minor) <= XSW_VERSION(b_major, b_minor)
#define XSW_VERSION_LT(a_major, a_minor, b_major, b_minor) XSW_VERSION(a_major, a_minor) <  XSW_VERSION(b_major, b_minor)

// CPP Attribute check
#if defined(__has_cpp_attribute) && defined(__cplusplus)
#  define XSW_HAS_CPP_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
#else
#  define XSW_HAS_CPP_ATTRIBUTE(attribute) (0)
#endif

// Deprecation support
#if defined(__cplusplus) && (__cplusplus >= 201402L)
      #  define XSW_DEPRECATED(message) [[deprecated(#message)]]
      #  define XSW_DEPRECATED_USE(message, replacement) [[deprecated(#message "; use " #replacement)]]
#elif XSW_HAS_EXTENSION(attribute_deprecated_with_message) || \
    ((defined(__clang__) || defined(__GNUC__)) && XSW_VERSION_GE( __GNUC__,__GNUC_MINOR__, 4,5 ))
      #  define XSW_DEPRECATED(message) __attribute__((__deprecated__(#message)))
      #  define XSW_DEPRECATED_USE(message, replacement) __attribute__((__deprecated__(#message "; use " #replacement)))
#elif XSW_HAS_ATTRIBUTE(deprecated) || \
    ((defined(__clang__) || defined(__GNUC__)) && XSW_VERSION_GE( __GNUC__,__GNUC_MINOR__, 3,1 ))
      #  define XSW_DEPRECATED(message) __attribute__((__deprecated__))
      #  define XSW_EPRECATED_USE(message, replacement) __attribute__((__deprecated__))
#elif defined(_MSC_VER) && XSW_VERSION_GE( _MSC_VER / 100, _MSC_VER % 100, 14,0 )
      #  define XSW_DEPRECATED(message) __declspec(deprecated(#message))
      #  define XSW_DEPRECATED_USE(message, replacement) __declspec(deprecated(#message "; use " #replacement))
#elif defined(_MSC_VER) && XSW_VERSION_GE( _MSC_VER / 100, _MSC_VER % 100, 13,10 )
      #  define XSW_DEPRECATED(message) __declspec(deprecated)
      #  define XSW_DEPRECATED_USE(message, replacement) __declspec(deprecated)
#else
      #  define XSW_DEPRECATED(message)
      #  define XSW_DEPRECATED_USE(message, replacement)
#endif


// Switch Fallthrough support
#if defined(__cplusplus) && ((__cplusplus >= 201703L) || ((__cplusplus >= 201103L) && XSW_HAS_ATTRIBUTE(fallthrough)))
#    define XSW_FALL_THROUGH [[fallthrough]]
#elif (__cplusplus >= 201103L) && XSW_HAS_CPP_ATTRIBUTE(clang::fallthrough)
#    define XSW_FALL_THROUGH [[clang::fallthrough]]
#elif (__cplusplus >= 201103L) && \
    (defined(__clang__) || defined(__GNUC__)) && XSW_VERSION_GE( __GNUC__,__GNUC_MINOR__, 7,0 )
#    define XSW_FALL_THROUGH [[gnu::fallthrough]]
#elif XSW_HAS_ATTRIBUTE(fallthrough) && \
    (defined(__clang__) || defined(__GNUC__)) && XSW_VERSION_GE( __GNUC__,__GNUC_MINOR__, 7,0 )
#    define XSW_FALL_THROUGH __attribute__((__fallthrough__))
#elif defined(__fallthrough)
#    define XSW_FALL_THROUGH __fallthrough
#else
#    define XSW_FALL_THROUGH
#endif


#ifdef __cplusplus
}
#endif

#endif //XSW_UTIL_COMPILER_SUPPORT_H
