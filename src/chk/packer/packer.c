#include <chk/packer/packer.h>

#include <chk/core/check.h>
#include <chk/core/log.h>

#include <cwalk.h>
#include <dirent.h>

#include <string.h>

chk_packer_config_t chk_packer_config_default(void) {
  chk_packer_config_t config = {0};

  config._unused = 420;

  return config;
}

b8_t chk_packer_init(chk_packer_t* packer, chk_packer_config_t config) {
  chk_check_b8_t(packer);

  *packer = (chk_packer_t){0};

  packer->_unused = config._unused;

  return 1;
}

b8_t chk_packer_destroy(chk_packer_t* packer) {
  chk_check_b8_t(packer);

  *packer = (chk_packer_t){0};

  return 1;
}

b8_t chk_packer_run(chk_packer_t* packer) {
  chk_check_b8_t(packer);

  chk_log_info("Running packer...");
  chk_packer_iterate(packer, "assets_raw", "assets", 0);

  return 1;
}

b8_t chk_packer_iterate(chk_packer_t* packer, cstr_t i_path, cstr_t o_path, s32_t depth) {
  b8_t ret = 0;

  chk_check_b8_t(packer);
  chk_check_b8_t(i_path);
  chk_check_b8_t(o_path);
  chk_check_b8_t(depth < 8);

  char_t i_buf[1024];
  char_t o_buf[1024];

  DIR* dir = opendir(i_path);
  if (dir) {
    struct dirent* entry;

    while ((entry = readdir(dir))) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) { continue; }

      snprintf(i_buf, sizeof(i_buf), "%s/%s", i_path, entry->d_name);
      snprintf(o_buf, sizeof(o_buf), "%s/%s", o_path, entry->d_name);

      chk_log_set_indentation(depth);

      if (entry->d_type == DT_DIR) {
        // Make the output directory if it does not exist

        chk_log_info("entering dir '%s' -> '%s'", i_buf, o_buf);
        ret = chk_packer_iterate(packer, i_buf, o_buf, depth + 1);
      } else {
        if (cwk_path_change_extension(o_buf, "chk", o_buf, sizeof(o_buf))) {
          if (chk_packer_pack(packer, i_buf, o_buf)) {
            chk_log_info("packed '%s' -> '%s'", i_buf, o_buf);

            ret = 1;
          } else {
            chk_log_error("failed to pack file '%s'", i_buf);
          }
        } else {
          chk_log_error("failed to change extension to '%s'", o_buf);
        }
      }
    }

    chk_log_set_indentation(0);

    closedir(dir);
  } else {
    chk_log_error("failed to open '%s'", i_path);
  }

  return ret;
}

b8_t chk_packer_pack(chk_packer_t* packer, cstr_t i_path, cstr_t o_path) {
  chk_check_b8_t(packer);
  chk_check_b8_t(i_path);
  chk_check_b8_t(o_path);

  b8_t ret = 0;

  cstr_t ext;
  size_t ext_size;
  if (cwk_path_get_extension(i_path, &ext, &ext_size)) {
    static cstr_t image_exts[] = {".png", ".jpg", ".jpeg", ".bmp"};
    static cstr_t audio_exts[] = {".wav", ".mp3", ".ogg"};
    static cstr_t font_exts[]  = {".ttf", ".otf"};

    b8_t packed = 0;

    // Common image extensions
    for (index_t i = 0; i < sizeof(image_exts) / sizeof(image_exts[0]); ++i) {
      if (strcmp(ext, image_exts[i]) == 0) {
        packed = chk_packer_pack_image(packer, i_path, o_path);
        break;
      }
    }

    // Common audio extensions
    for (index_t i = 0; i < sizeof(audio_exts) / sizeof(audio_exts[0]); ++i) {
      if (strcmp(ext, audio_exts[i]) == 0) {
        packed = chk_packer_pack_audio(packer, i_path, o_path);
        break;
      }
    }

    // Common font extensions
    for (index_t i = 0; i < sizeof(font_exts) / sizeof(font_exts[0]); ++i) {
      if (strcmp(ext, font_exts[i]) == 0) {
        packed = chk_packer_pack_font(packer, i_path, o_path);
        break;
      }
    }

    ret = packed;
    if (!packed) { chk_log_error("invalid file extension '%s'", ext); }
  } else {
    chk_log_info("unable to get the file extension for file '%s'", i_path);
  }

  return ret;
}

b8_t chk_packer_pack_image(chk_packer_t* packer, cstr_t i_path, cstr_t o_path) {
  chk_check_b8_t(packer);
  chk_check_b8_t(i_path);
  chk_check_b8_t(o_path);

  b8_t res = 1;

  return res;
}

b8_t chk_packer_pack_audio(chk_packer_t* packer, cstr_t i_path, cstr_t o_path) {
  chk_check_b8_t(packer);
  chk_check_b8_t(i_path);
  chk_check_b8_t(o_path);

  b8_t res = 1;

  return res;
}

b8_t chk_packer_pack_font(chk_packer_t* packer, cstr_t i_path, cstr_t o_path) {
  chk_check_b8_t(packer);
  chk_check_b8_t(i_path);
  chk_check_b8_t(o_path);

  b8_t res = 1;

  return res;
}
