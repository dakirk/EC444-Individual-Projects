/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "pins.h"

/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/

void app_main(void)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(A6);
    gpio_pad_select_gpio(A7);
    gpio_pad_select_gpio(A8);
    gpio_pad_select_gpio(A9);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(A6, GPIO_MODE_OUTPUT);
    gpio_set_direction(A7, GPIO_MODE_OUTPUT);
    gpio_set_direction(A8, GPIO_MODE_OUTPUT);
    gpio_set_direction(A9, GPIO_MODE_OUTPUT);
    /*while(1) {
      //Blink off (output low)
	    printf("Turning off the LED\n");
        gpio_set_level(A6, 0);
        gpio_set_level(A7, 0);
        gpio_set_level(A8, 0);
        gpio_set_level(A9, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      //Blink on (output high)
	    printf("Turning on the LED\n");
        gpio_set_level(A6, 1);
        gpio_set_level(A7, 1);
        gpio_set_level(A8, 1);
        gpio_set_level(A9, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }*/

    int count = 0;
    int i;

    while(1) {
      if (count > 15) {
        count = 0;
      }


      gpio_set_level(A9, ((count >> 0) & 1));
      gpio_set_level(A8, ((count >> 1) & 1));
      gpio_set_level(A7, ((count >> 2) & 1));
      gpio_set_level(A6, ((count >> 3) & 1));

      

      count++;

      vTaskDelay(1000 / portTICK_PERIOD_MS);

    }

}
