cmake_minimum_required(VERSION 3.30)
project(chk_playground LANGUAGES C VERSION 0.1.0)

###################
# Enable warnings #
###################

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-implicit-fallthrough -Wno-variadic-macro-arguments-omitted)
endif()

################
# Dependencies #
################

find_package(Cwalk CONFIG REQUIRED)
find_path(DIRENT_INCLUDE_DIRS "dirent.h")

########
# Core #
########

add_library(chk_core)
target_sources(chk_core
PUBLIC FILE_SET HEADERS TYPE HEADERS BASE_DIRS "include" FILES
  "include/chk/core/log.h"
  "include/chk/core/str.h"
  "include/chk/core/types.h"
PRIVATE
  "src/chk/core/str.c"
  "src/chk/core/log.c"
)
target_include_directories(chk_core PUBLIC "include")
target_compile_features(chk_core PUBLIC c_std_11)
target_link_libraries(chk_core PRIVATE cwalk)

##########
# Packer #
##########

add_executable(chk_packer)
target_sources(chk_packer
PUBLIC FILE_SET HEADERS TYPE HEADERS BASE_DIRS "include" FILES
  "include/chk/packer/packer.h"
PRIVATE
  "src/chk/packer/main.c"
  "src/chk/packer/packer.c"
)
target_include_directories(chk_packer PUBLIC "include")
target_include_directories(chk_packer PRIVATE ${DIRENT_INCLUDE_DIRS})
target_compile_features(chk_packer PUBLIC c_std_11)
target_link_libraries(chk_packer PUBLIC chk_core)
target_link_libraries(chk_packer PRIVATE cwalk)
add_custom_command(TARGET chk_packer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:chk_packer>/assets"
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_SOURCE_DIR}/assets_raw"
    "$<TARGET_FILE_DIR:chk_packer>/assets_raw"
)
