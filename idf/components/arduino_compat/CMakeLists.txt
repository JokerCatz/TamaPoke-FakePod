idf_component_register(SRCS "src/arduino_compat.cpp" "src/sd_card.cpp" "src/prefs.cpp" INCLUDE_DIRS "include"
    REQUIRES esp_driver_usb_serial_jtag esp_timer esp_hw_support nvs_flash driver esp_driver_gpio fatfs sdmmc esp_driver_sdmmc fakepod_bsp)
