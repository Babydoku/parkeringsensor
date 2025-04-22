#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int pin;                  
    bool is_active_low;       
} buzzer_config_t;

void buzzer_init(buzzer_config_t *config);
void buzzer_set(bool state, buzzer_config_t *config);

