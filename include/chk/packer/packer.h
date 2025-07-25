#pragma once

#include <chk/core/str.h>
#include <chk/core/types.h>

typedef struct chk_packer {
  s32_t _unused;
} chk_packer_t;

typedef struct chk_packer_config {
  s32_t _unused;
} chk_packer_config_t;

chk_packer_config_t chk_packer_config_default(void);

b8_t chk_packer_init(chk_packer_t* packer, chk_packer_config_t config);
b8_t chk_packer_destroy(chk_packer_t* packer);
b8_t chk_packer_run(chk_packer_t* packer);

b8_t chk_packer_iterate(chk_packer_t* packer, cstr_t i_path, cstr_t o_path, s32_t depth);
b8_t chk_packer_pack(chk_packer_t* packer, cstr_t i_path, cstr_t o_path);

b8_t chk_packer_pack_image(chk_packer_t* packer, cstr_t i_path, cstr_t o_path);
b8_t chk_packer_pack_audio(chk_packer_t* packer, cstr_t i_path, cstr_t o_path);
b8_t chk_packer_pack_font(chk_packer_t* packer, cstr_t i_path, cstr_t o_path);
