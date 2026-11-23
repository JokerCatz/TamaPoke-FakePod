# TamaPoke-FakePod: ESP-IDF build for the Fake Pod Nano Pro (ESP32-S31). The upstream Arduino sources in the repo root are NOT modified;
# tamapoke_core compiles the portable ones in place, through the arduino_compat shim headers.
cmake_minimum_required(VERSION 3.16)
set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/components")
# exFAT: IDF builds FatFs with FF_FS_EXFAT 0 (hard-coded), so a card as sold at 64 GB and up does not mount. tools/make_fatfs_exfat.sh writes a patched copy of IDF's fatfs
# into .generated/ (a no-op when nothing changed; it fails loudly if an IDF upgrade moves the lines it edits) and a project component named fatfs replaces IDF's.
set(FP_FATFS_DIR ${CMAKE_CURRENT_LIST_DIR}/.generated/fatfs_exfat)
execute_process(COMMAND env IDF_PATH=$ENV{IDF_PATH} bash ${CMAKE_CURRENT_LIST_DIR}/tools/make_fatfs_exfat.sh
                RESULT_VARIABLE FP_FATFS_RC OUTPUT_VARIABLE FP_FATFS_OUT ERROR_VARIABLE FP_FATFS_ERR)
if(NOT FP_FATFS_RC EQUAL 0)
    message(FATAL_ERROR "tools/make_fatfs_exfat.sh failed (${FP_FATFS_RC}):\n${FP_FATFS_OUT}${FP_FATFS_ERR}")
endif()
list(APPEND EXTRA_COMPONENT_DIRS ${FP_FATFS_DIR})
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(tamapoke_fakepod)
