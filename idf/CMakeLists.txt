# TamaPoke-FakePod: ESP-IDF build for the Fake Pod Nano Pro (ESP32-S31). The upstream Arduino sources in the repo root are NOT modified;
# tamapoke_core compiles the portable ones in place, through the arduino_compat shim headers.
cmake_minimum_required(VERSION 3.16)
set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/components")
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(tamapoke_fakepod)
