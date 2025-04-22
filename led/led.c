#include "led.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_rom_gpio.h"

static bool current_led_state = false;
static uint32_t last_toggle_time = 0;

void led_init(led_config_t *config) {
    esp_rom_gpio_pad_select_gpio(config->pin);
    gpio_set_direction(config->pin, GPIO_MODE_OUTPUT);
    gpio_set_level(config->pin, config->is_active_low ? 1 : 0);
    config->is_blinking = false;
}

void led_blink(int milliseconds_on, int milliseconds_off, led_config_t *config) {
    config->is_blinking = true;
    config->milliseconds_on = milliseconds_on;
    config->milliseconds_off = milliseconds_off;
    last_toggle_time = xTaskGetTickCount() * portTICK_PERIOD_MS;
}

void led_set(bool state, led_config_t *config) {
    config->is_blinking = false;
    gpio_set_level(config->pin, state ^ config->is_active_low);
    current_led_state = state;
}

void led_update(led_config_t *config) {
    if (!config->is_blinking)
        return;
    
    uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;
    uint32_t elapsed = now - last_toggle_time;

    if (current_led_state && (elapsed >= config->milliseconds_on)) {
        gpio_set_level(config->pin, config->is_active_low ? 1 : 0);
        current_led_state = false;
        last_toggle_time = now;
    } else if (!current_led_state && (elapsed >= config->milliseconds_off)) {
        gpio_set_level(config->pin, config->is_active_low ? 0 : 1);
        current_led_state = true;
        last_toggle_time = now;
    }
}
