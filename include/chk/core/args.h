#pragma once

#include <stdarg.h>

typedef va_list args_t;

#define chk_args_init(args, last)  va_start(args, last)
#define chk_args_copy(args, src)   va_copy(args, src)
#define chk_args_destroy(args)     va_end(args)
#define chk_args_get(args, type_t) (type_t) va_arg(args, type_t)
