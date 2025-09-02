#pragma once
#include "cbpch.h"

#ifdef DEBUG
#if defined(_MSC_VER)
#define CB_DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#include <signal.h>
#define CB_DEBUG_BREAK() raise(SIGTRAP)
#else
#define CB_DEBUG_BREAK() std::abort()
#endif
#else
#define CB_DEBUG_BREAK() 
#endif

#define CB_ASSERT(expr) do {if(!expr){std::fprintf(stderr, "Failed to assert expression %s at %d in file %s", #expr, __LINE__, __FILE__); CB_DEBUG_BREAK();}} while (0)
#define CB_ASSERT_MSG(expr, msg) if(!expr){std::fprintf(stderr, "Failed to assert expression %s at %d in file %s", #expr, __LINE__, __FILE__); std::fprintf(stderr, "Message: %s", msg); CB_DEBUG_BREAK();}} while (0)