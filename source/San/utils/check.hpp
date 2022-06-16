﻿//
// Created by 秋鱼 on 2022/6/16.
//

#pragma once

#include <logger.hpp>
#include "defines.hpp"

namespace San {

#ifdef SAN_USE_GPU
#define CHECK(x) assert(x)
#define CHECK_IMPL(a, b, op) assert((a)op(b))

#define CHECK_EQ(a, b) CHECK_IMPL(a, b, ==)
#define CHECK_NE(a, b) CHECK_IMPL(a, b, !=)
#define CHECK_GT(a, b) CHECK_IMPL(a, b, >)
#define CHECK_GE(a, b) CHECK_IMPL(a, b, >=)
#define CHECK_LT(a, b) CHECK_IMPL(a, b, <)
#define CHECK_LE(a, b) CHECK_IMPL(a, b, <=)
#else
// CHECK Macro Definitions
#define CHECK(x)                                                                    \
    do {                                                                            \
        if (!(x))                                                                   \
            LOG_FATAL("Check failed: {}", #x);                                      \
    } while (false) /* swallow semicolon */

#define CHECK_EQ(a, b) CHECK_IMPL(a, b, ==)
#define CHECK_NE(a, b) CHECK_IMPL(a, b, !=)
#define CHECK_GT(a, b) CHECK_IMPL(a, b, >)
#define CHECK_GE(a, b) CHECK_IMPL(a, b, >=)
#define CHECK_LT(a, b) CHECK_IMPL(a, b, <)
#define CHECK_LE(a, b) CHECK_IMPL(a, b, <=)

// CHECK\_IMPL Macro Definition
#define CHECK_IMPL(a, b, op)                                                           \
    do {                                                                               \
        auto va = a;                                                                   \
        auto vb = b;                                                                   \
        if (!(va op vb))                                                               \
            LOG_FATAL("Check failed: {} " #op " {} with {} = {}, {} = {}", #a, #b, #a, \
                      va, #b, vb);                                                     \
    } while (false) /* swallow semicolon */

#endif

#ifdef _DEBUG
#define DCHECK(x) CHECK(x)
#define DCHECK_EQ(a, b) CHECK_EQ(a, b)
#define DCHECK_NE(a, b) CHECK_NE(a, b)
#define DCHECK_GT(a, b) CHECK_GT(a, b)
#define DCHECK_GE(a, b) CHECK_GE(a, b)
#define DCHECK_LT(a, b) CHECK_LT(a, b)
#define DCHECK_LE(a, b) CHECK_LE(a, b)

#else

#define EMPTY_CHECK \
    do {            \
    } while (false) /* swallow semicolon */

// Use an empty check (rather than expanding the macros to nothing) to swallow the
// semicolon at the end, and avoid empty if-statements.
#define DCHECK(x) EMPTY_CHECK

#define DCHECK_EQ(a, b) EMPTY_CHECK
#define DCHECK_NE(a, b) EMPTY_CHECK
#define DCHECK_GT(a, b) EMPTY_CHECK
#define DCHECK_GE(a, b) EMPTY_CHECK
#define DCHECK_LT(a, b) EMPTY_CHECK
#define DCHECK_LE(a, b) EMPTY_CHECK

#endif

} // San