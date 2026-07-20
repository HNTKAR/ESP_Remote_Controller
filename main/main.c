#include <stdio.h>

#include "driver/ledc.h"
#include "send.h"
#include "recieve.h"

void app_main(void)
{
    // send_init();
    recieve_init();
    recieve_set();
}