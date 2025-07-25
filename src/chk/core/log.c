#include <chk/core/check.h>
#include <chk/core/log.h>

#include <stdio.h>

#include <cwalk.h>

static chk_log_sev_t g_sev_lvl = chk_log_sev_trace;
static cstr_t        g_ind_arr = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
static u8_t          g_ind_lvl = 0;

b8_t chk_log_set_sev(chk_log_sev_t sev) {
  chk_check_raw_ret(sev > chk_log_sev_none, 0, 0);
  chk_check_raw_ret(sev < chk_log_sev_count, 0, 0);

  g_sev_lvl = sev;
  return 1;
}

chk_log_sev_t chk_log_get_sev(void) { return g_sev_lvl; }

b8_t chk_log_set_indentation(u8_t depth) {
  chk_check_raw_ret(depth < sizeof(g_ind_arr), 0, 0);

  g_ind_lvl = depth;
  return 1;
}

s8_t chk_log_get_indentation(void) { return g_ind_lvl; }

cstr_t chk_log_sev_to_str(chk_log_sev_t sev) {
  switch (sev) {
    case chk_log_sev_none:
    case chk_log_sev_count: break;

    case chk_log_sev_trace: return "TRC";
    case chk_log_sev_debug: return "DBG";
    case chk_log_sev_info:  return "INF";
    case chk_log_sev_warn:  return "WRN";
    case chk_log_sev_error: return "ERR";
  }

  return "UNK";
}

cstr_t chk_log_sev_to_ansi(chk_log_sev_t sev) {
  switch (sev) {
    case chk_log_sev_none:
    case chk_log_sev_count: break;

    case chk_log_sev_trace: return "\x1b[2;39m";
    case chk_log_sev_debug: return "\x1b[2;34m";
    case chk_log_sev_info:  return "\x1b[34m";
    case chk_log_sev_warn:  return "\x1b[33m";
    case chk_log_sev_error: return "\x1b[31m";
  }

  return "\x1b[39m";
}

b8_t chk_log_raw(chk_log_sev_t sev, cstr_t fmt, cstr_t file, u32_t line, cstr_t fn) {
  chk_check_raw_ret(sev, 0, 0);
  chk_check_raw_ret(fmt, 0, 0);

  if (sev >= g_sev_lvl) {
    cstr_t sev_beg  = chk_log_sev_to_ansi(sev);
    cstr_t sev_name = chk_log_sev_to_str(sev);
    cstr_t sev_end  = "\x1b[0m";

    cstr_t loc_beg  = "\x1b[2;39m";
    cstr_t loc_file = file;
    cstr_t loc_fn   = fn;
    cstr_t loc_end  = "\x1b[0m";

    struct cwk_segment seg;
    if (cwk_path_get_last_segment(file, &seg)) {
      cwk_path_get_previous_segment(&seg);
      loc_file = seg.begin;
    }

    static char_t buf[256];
    if (chk_str_fmt(buf, sizeof(buf), "[%s%s%s] [%s%s:%u:%s%s] %.*s%s\n", //
                    sev_beg, sev_name, sev_end, loc_beg, loc_file, line, loc_fn, loc_end, g_ind_lvl, g_ind_arr, fmt)) {
      fputs(buf, stderr);
    }
  }

  return 1;
}

b8_t chk_log_raw_fmt(chk_log_sev_t sev, cstr_t fmt, cstr_t file, u32_t line, cstr_t fn, ...) {
  chk_check_raw_ret(sev, 0, 0);
  chk_check_raw_ret(fmt, 0, 0);

  args_t args;
  chk_args_init(args, fn);
  b8_t ret = chk_log_raw_args(sev, fmt, file, line, fn, args);
  chk_args_destroy(args);

  return ret;
}

b8_t chk_log_raw_args(chk_log_sev_t sev, cstr_t fmt, cstr_t file, u32_t line, cstr_t fn, args_t args) {
  chk_check_raw_ret(sev, 0, 0);
  chk_check_raw_ret(fmt, 0, 0);

  static char_t buf[256];

  args_t copy;
  chk_args_copy(copy, args);
  b8_t ret = chk_str_fmt_args(buf, sizeof(buf), fmt, copy);
  chk_args_destroy(copy);

  return ret && chk_log_raw(sev, buf, file, line, fn);
}
