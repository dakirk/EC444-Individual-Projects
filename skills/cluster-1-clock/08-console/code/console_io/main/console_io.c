#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "driver/uart.h"
#include "esp_vfs_dev.h"

#define TOGGLE_GPIO 13

void app_main()
{


    gpio_pad_select_gpio(TOGGLE_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(TOGGLE_GPIO, GPIO_MODE_OUTPUT);

    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0,
      256, 0, 0, NULL, 0) );

    /* Tell VFS to use UART driver */
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

    //char str[20];
    int num = 0;
    int toggle = 0;
    int mode = 0; //0 for toggle, 1 for echo, 2 for hex

    printf("toggle mode\n");

    while(1) {

      //prompt for hex mode
      if (mode == 2) {
        printf("Enter an integer:\n");
      }

      // gets()
      char buf[5];
      gets(buf);

      //catch the mode switch character before anything else is done
      if (buf[0] == 's' && buf[1] == '\0') {
        if (mode == 0) {
            mode = 1;
            printf("Read: s\n");
            printf("echo mode\n");
        } else if (mode == 1) {
            mode = 2;
            printf("echo: s\n");
            printf("echo dec to hex mode\n");
        } else {
            mode = 0;
            printf("toggle mode\n");
        }
      } else {

        //toggle mode
        if (mode == 0) {
            if (buf[0] == 't' && buf[1] == '\0') {
                printf("Read: t\n");
                toggle = !toggle;
                gpio_set_level(TOGGLE_GPIO, toggle);
            }
        } 

        //echo mode
        else if (mode == 1) {
            printf("echo: %s\n", buf);
        }

        //hex mode (uses builtin atio and itoa functions)
        else {
            char hexBuf[20];
            num = atoi(buf);
            itoa(num, hexBuf, 16);
            printf("Hex: %s\n", hexBuf);
        }



      }

      vTaskDelay(50 / portTICK_RATE_MS);
    }
}