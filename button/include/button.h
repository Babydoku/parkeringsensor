#pragma once

#include "driver/gpio.h"
#include <stdbool.h>


typedef struct {
    gpio_num_t pin;        
    bool pullup_enabled;  
    bool system_active;   
} button_config_t;

void button_init(button_config_t *btn_config);
void button_handle_sleep(button_config_t *btn_config);
bool button_is_active(button_config_t *btn_config);






