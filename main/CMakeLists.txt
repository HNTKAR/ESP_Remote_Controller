idf_component_register(
    
SRCS
"base/decoder_base.cpp"
"main.cpp"
"decoder_AEHA.cpp"
"decoder_DAIKIN.cpp"
"recieveSignal.cpp"
"recieveMain.cpp"
"send.cpp"
    
INCLUDE_DIRS
"."

REQUIRES
esp_driver_ledc
esp_driver_gpio
esp_driver_gptimer

)

add_compile_definitions(USE_IOSTREAM_FOR_DEBUG)
