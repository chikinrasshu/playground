#pragma once

#define chk_check_raw_ret(expr, log, ret)                                                                              \
  do {                                                                                                                 \
    if (!(expr)) {                                                                                                     \
      if ((log)) { chk_log_error("check failure: %s", #expr); }                                                        \
      return ret;                                                                                                      \
    }                                                                                                                  \
  } while (0)

#define chk_check_raw(expr, log)                                                                                       \
  do {                                                                                                                 \
    if (!(expr)) {                                                                                                     \
      if ((log)) { chk_log_error("check failure: %s", #expr); }                                                        \
    }                                                                                                                  \
  } while (0)

#define chk_check_void(expr)    chk_check_raw(expr, 1)
#define chk_check_u8_t(expr)    chk_check_raw_ret(expr, 1, 0)
#define chk_check_s8_t(expr)    chk_check_raw_ret(expr, 1, 0)
#define chk_check_u16_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_s16_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_u32_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_s32_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_u64_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_s64_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_f32_t(expr)   chk_check_raw_ret(expr, 1, 0.0f)
#define chk_check_f64_t(expr)   chk_check_raw_ret(expr, 1, 0.0)
#define chk_check_b8_t(expr)    chk_check_raw_ret(expr, 1, 0)
#define chk_check_b16_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_b32_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_b64_t(expr)   chk_check_raw_ret(expr, 1, 0)
#define chk_check_ptr_t(expr)   chk_check_raw_ret(expr, 1, (void*)0)
#define chk_check_index_t(expr) chk_check_raw_ret(expr, 1, (index_t)0)
#define chk_check_cstr_t(expr)  chk_check_raw_ret(expr, 1, "")
