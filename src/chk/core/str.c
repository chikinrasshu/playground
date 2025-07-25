#include <chk/core/check.h>
#include <chk/core/log.h>
#include <chk/core/str.h>

#include <stdio.h>

b8_t chk_str_fmt(str_t buf, size_t buf_size, cstr_t fmt, ...) {
  chk_check_raw_ret(buf, 0, 0);
  chk_check_raw_ret(buf_size, 0, 0);
  chk_check_raw_ret(fmt, 0, 0);

  args_t args;
  chk_args_init(args, fmt);
  b8_t ret = chk_str_fmt_args(buf, buf_size, fmt, args);
  chk_args_destroy(args);

  return ret;
}

b8_t chk_str_fmt_args(str_t buf, size_t buf_size, cstr_t fmt, args_t args) {
  chk_check_raw_ret(buf, 0, 0);
  chk_check_raw_ret(buf_size, 0, 0);
  chk_check_raw_ret(fmt, 0, 0);

  args_t copy;
  chk_args_copy(copy, args);
  size_t written = (size_t)vsnprintf(buf, buf_size, fmt, copy);
  chk_args_destroy(copy);

  return written > 0 && written < buf_size;
}
