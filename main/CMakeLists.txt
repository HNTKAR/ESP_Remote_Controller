idf_component_register(SRCS "send.cpp" "recieveSignal.cpp" "main.cpp" "recieveMain.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_ledc esp_driver_gpio esp_driver_gptimer)