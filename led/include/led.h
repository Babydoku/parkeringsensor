#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int pin;                   
    uint32_t is_active_low;          
    bool is_blinking;           
    int milliseconds_on;        
    int milliseconds_off;       
} led_config_t;

void led_init(led_config_t *config);
void led_blink(int milliseconds_on, int milliseconds_off, led_config_t *config);
void led_update(led_config_t *config);
void led_set(bool state, led_config_t *config);




