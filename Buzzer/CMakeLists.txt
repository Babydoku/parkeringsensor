idf_component_register(SRCS "Buzzer.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver
                    REQUIRES driver freertos
                    REQUIRES esp_timer)
