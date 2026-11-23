idf_component_register(SRCS "src/fp_display.c" "src/co5300.c" "src/fp_touch.c" INCLUDE_DIRS "include"
    REQUIRES driver esp_driver_i2c esp_lcd esp_driver_spi esp_driver_gpio esp_timer heap)
