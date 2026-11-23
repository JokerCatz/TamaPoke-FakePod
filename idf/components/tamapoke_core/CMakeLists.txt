# Upstream game logic, compiled in place from the repo root (no copies: `git merge upstream/main` keeps working).
set(UP ${CMAKE_CURRENT_LIST_DIR}/../../..)
idf_component_register(
    SRCS "${UP}/pet.cpp" "${UP}/i18n.cpp" "${UP}/trainingtouch.cpp" "audio_stub.cpp"
    INCLUDE_DIRS "${UP}"
    REQUIRES arduino_compat)
# Upstream is built by arduino-esp32 without -Werror; its printf formats assume 32-bit `unsigned` (uint32_t is `unsigned long` on this toolchain). Keep the warning, do not edit upstream.
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-error=format)
