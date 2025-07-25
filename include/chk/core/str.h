#pragma once

#include <chk/core/args.h>
#include <chk/core/types.h>

typedef char        char_t;
typedef char*       str_t;
typedef const char* cstr_t;

b8_t chk_str_fmt(str_t buf, size_t buf_size, cstr_t fmt, ...);
b8_t chk_str_fmt_args(str_t buf, size_t buf_size, cstr_t fmt, args_t args);
