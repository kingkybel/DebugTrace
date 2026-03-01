/*
 * Repository:  https://github.com/kingkybel/DebugTrace
 * File Name:   include/traceutil.h
 * Description: debug tracing
 *
 * Copyright (C) 2023 Dieter J Kybelksties <github@kybelksties.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 */

#ifndef DKYB_TRACEUTIL_H_
#define DKYB_TRACEUTIL_H_

#include <iostream>
#include <string_view>
#include <utility>
#if __has_include(<source_location>)
#include <source_location>
#if defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L
#define DKYB_HAS_SOURCE_LOCATION 1
#endif
#endif

#ifndef DKYB_HAS_SOURCE_LOCATION
#if __has_include(<experimental/source_location>)
#include <experimental/source_location>
#define DKYB_HAS_SOURCE_LOCATION 1
#define DKYB_SOURCE_LOCATION_EXPERIMENTAL 1
#endif
#endif

#include <unistd.h>
#include <cstdint>

namespace dkyb::trace {

#ifdef DKYB_HAS_SOURCE_LOCATION
#ifdef DKYB_SOURCE_LOCATION_EXPERIMENTAL
    using source_location = std::experimental::source_location;
#else
    using source_location = std::source_location;
#endif
#else
    struct source_location {
        static constexpr source_location current(const char* file = __builtin_FILE(),
                                                 std::uint32_t line = __builtin_LINE(),
                                                 const char* func = __builtin_FUNCTION()) noexcept {
            return {file, line, func};
        }
        constexpr source_location() noexcept : file("unknown"), ln(0), func("unknown") {}
        constexpr source_location(const char* file, std::uint32_t line, const char* func) noexcept
            : file(file), ln(line), func(func) {}
        constexpr const char* file_name() const noexcept { return file; }
        constexpr std::uint32_t line() const noexcept { return ln; }
        constexpr const char* function_name() const noexcept { return func; }

    private:
        const char* file;
        std::uint32_t ln;
        const char* func;
    };
#endif

    template<typename... Args>
    inline void trace_out(source_location loc, bool show_pid, bool enabled, Args&&... args) {
        if (enabled) {
            std::cout << loc.file_name() << ":" << loc.line() << " " << loc.function_name();
            if (show_pid) {
                std::cout << " PID=" << getpid();
            }
            ((std::cout << " " << std::forward<Args>(args)), ...);
            std::cout << std::endl;
        }
    }
} // namespace dkyb::trace

#endif // DKYB_TRACEUTIL_H_

// The following part is NOT guarded to allow redefining TRACE macros when DO_TRACE_ changes
#undef DKYB_TRACE_ENABLED_ // NOSONAR
#undef TRACE0              // NOSONAR
#undef TRACE1              // NOSONAR
#undef TRACE2              // NOSONAR
#undef TRACE3              // NOSONAR
#undef PTRACE0             // NOSONAR
#undef PTRACE1             // NOSONAR
#undef PTRACE2             // NOSONAR
#undef PTRACE3             // NOSONAR

#if defined(ENABLE_DEBUG_TRACE) || defined(DO_TRACE_)
    #define DKYB_TRACE_ENABLED_ true
#else
    #define DKYB_TRACE_ENABLED_ false
#endif

// Simple Wrappers
#define TRACE0 dkyb::trace::trace_out(dkyb::trace::source_location::current(), false, DKYB_TRACE_ENABLED_)
#define TRACE1(v1) dkyb::trace::trace_out(dkyb::trace::source_location::current(), false, DKYB_TRACE_ENABLED_, #v1 "=", v1)
#define TRACE2(v1, v2) dkyb::trace::trace_out(dkyb::trace::source_location::current(), false, DKYB_TRACE_ENABLED_, #v1 "=", v1, #v2 "=", v2)
#define TRACE3(v1, v2, v3) dkyb::trace::trace_out(dkyb::trace::source_location::current(), false, DKYB_TRACE_ENABLED_, #v1 "=", v1, #v2 "=", v2, #v3 "=", v3)

#define PTRACE0 dkyb::trace::trace_out(dkyb::trace::source_location::current(), true, DKYB_TRACE_ENABLED_)
#define PTRACE1(v1) dkyb::trace::trace_out(dkyb::trace::source_location::current(), true, DKYB_TRACE_ENABLED_, #v1 "=", v1)
#define PTRACE2(v1, v2) dkyb::trace::trace_out(dkyb::trace::source_location::current(), true, DKYB_TRACE_ENABLED_, #v1 "=", v1, #v2 "=", v2)
#define PTRACE3(v1, v2, v3) dkyb::trace::trace_out(dkyb::trace::source_location::current(), true, DKYB_TRACE_ENABLED_, #v1 "=", v1, #v2 "=", v2, #v3 "=", v3)
