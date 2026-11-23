idf_component_register(SRCS "main.cpp" "tamapoke_app.cpp" INCLUDE_DIRS "." REQUIRES fakepod_bsp gfx_compat tamapoke_core arduino_compat nvs_flash)
# upstream is written without -Werror (arduino-esp32 builds it that way): warnings stay visible, they just do not stop the build
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-error)
