#pragma once

#include <chk/core/types.h>

#include <chk/core/asset/image.h>

typedef struct chk_glyph {
  u8_t x, y;
  u8_t w, h;
} chk_glyph_t;

typedef struct chk_font {
  chk_image_t atlas;

  s32_t pen_x, pen_y;

  chk_glyph_t* glyphs;
  u32_t        glyph_count;
} chk_font_t;
