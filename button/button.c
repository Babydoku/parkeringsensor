#include "button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"

static const char *TAG = "BUTTON";

static void IRAM_ATTR button_isr_handler(void* arg) {
    button_config_t *btn_config = (button_config_t *)arg;
    btn_config->system_active = !btn_config->system_active;
}

void button_init(button_config_t *btn_config) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << btn_config->pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = btn_config->pullup_enabled ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE  
    };

    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(btn_config->pin, button_isr_handler, (void *)btn_config);
}

bool button_is_active(button_config_t *btn_config) {
    return btn_config->system_active;
}

void button_handle_sleep(button_config_t *btn_config) {
    if (!btn_config->system_active) {
        printf("System är inaktiverat och går i deep sleep...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  

        esp_sleep_enable_ext1_wakeup(1ULL << btn_config->pin, ESP_EXT1_WAKEUP_ANY_LOW);
        esp_deep_sleep_start();
    }
}
