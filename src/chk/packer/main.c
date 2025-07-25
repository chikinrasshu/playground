#include <chk/packer/packer.h>

s32_t main(s32_t argc, str_t argv[]) {
  (void)argc;
  (void)argv;

  chk_packer_t        packer = {0};
  chk_packer_config_t config = chk_packer_config_default();

  s32_t exit_code = 1;
  if (chk_packer_init(&packer, config)) {
    if (chk_packer_run(&packer)) { exit_code = 0; }
    chk_packer_destroy(&packer);
  }

  return exit_code;
}
