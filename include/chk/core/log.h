#pragma once

#include <chk/core/args.h>
#include <chk/core/str.h>
#include <chk/core/types.h>

typedef enum chk_log_sev {
  chk_log_sev_none = 0,

  chk_log_sev_trace,
  chk_log_sev_debug,
  chk_log_sev_info,
  chk_log_sev_warn,
  chk_log_sev_error,

  chk_log_sev_count,
} chk_log_sev_t;

b8_t          chk_log_set_sev(chk_log_sev_t sev);
chk_log_sev_t chk_log_get_sev(void);

b8_t chk_log_set_indentation(u8_t depth);
s8_t chk_log_get_indentation(void);

b8_t chk_log_raw(chk_log_sev_t sev, cstr_t fmt, cstr_t file, u32_t line, cstr_t fn);
b8_t chk_log_raw_fmt(chk_log_sev_t sev, cstr_t fmt, cstr_t file, u32_t line, cstr_t fn, ...);
b8_t chk_log_raw_args(chk_log_sev_t sev, cstr_t fmt, cstr_t file, u32_t line, cstr_t fn, args_t args);

#define chk_log_trace(fmt, ...)                                                                                        \
  chk_log_raw##__VA_OPT__(_fmt)(chk_log_sev_trace, (fmt), __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)
#define chk_log_debug(fmt, ...)                                                                                        \
  chk_log_raw##__VA_OPT__(_fmt)(chk_log_sev_debug, (fmt), __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)
#define chk_log_info(fmt, ...)                                                                                         \
  chk_log_raw##__VA_OPT__(_fmt)(chk_log_sev_info, (fmt), __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)
#define chk_log_warn(fmt, ...)                                                                                         \
  chk_log_raw##__VA_OPT__(_fmt)(chk_log_sev_warn, (fmt), __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)
#define chk_log_error(fmt, ...)                                                                                        \
  chk_log_raw##__VA_OPT__(_fmt)(chk_log_sev_error, (fmt), __FILE__, __LINE__, __func__ __VA_OPT__(, ) __VA_ARGS__)
