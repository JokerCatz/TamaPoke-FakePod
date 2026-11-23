#pragma once
#include <stdint.h>
typedef int gpio_num_t;
#define GPIO_INTR_LOW_LEVEL 4
#define GPIO_INTR_HIGH_LEVEL 5
#define GPIO_INTR_NEGEDGE 2
static inline int gpio_wakeup_enable(int, int) { return 0; }
static inline int gpio_wakeup_disable(int) { return 0; }
static inline int gpio_set_intr_type(int, int) { return 0; }
