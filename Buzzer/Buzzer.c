#include "Buzzer.h"
#include "driver/gpio.h"
#include "esp_rom_gpio.h"

void buzzer_init(buzzer_config_t *config) {
    esp_rom_gpio_pad_select_gpio(config->pin);
    gpio_set_direction(config->pin, GPIO_MODE_OUTPUT);
    gpio_set_level(config->pin, config->is_active_low ? 1 : 0);
}

void buzzer_set(bool state, buzzer_config_t *config) {
    gpio_set_level(config->pin, state ^ config->is_active_low);
}
