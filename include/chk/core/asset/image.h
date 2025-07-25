#pragma once

#include <chk/core/types.h>

typedef struct chk_image {
  u8_t* data;
  u32_t data_size;

  u32_t w, h;
  u32_t pitch;
} chk_image_t;
