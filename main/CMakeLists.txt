idf_component_register(SRCS "send.cpp" "recieve.cpp" "main.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_ledc esp_driver_gpio esp_driver_gptimer)