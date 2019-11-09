/* UART asynchronous example, that uses separate RX and TX tasks

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

static const int RX_BUF_SIZE = 1024;

//#define TXD_PIN (GPIO_NUM_4)
//#define RXD_PIN (GPIO_NUM_5)
static const uint8_t TXD_PIN = 17;
static const uint8_t RXD_PIN = 16;

void init(void) {
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
}

int sendData(const char* logName, const char* data)
{
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);
    ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}

static void tx_task(void *arg)
{
    static const char *TX_TASK_TAG = "TX_TASK";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    while (1) {
        sendData(TX_TASK_TAG, "Hello world");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

static void rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE+1);
    int avgDist = 0;
    int distConcat = 0;
    
    //read raw input
    const int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE, 100 / portTICK_RATE_MS);
    
    while(1) {

    
        //if got data back
        if (rxBytes > 0) {
            data[rxBytes] = 0;
            
            int i;
            int distCounter = 0;
            
            //scan for first instance of 2 0x59 bytes in a row (data header)
            for (i = 0; i < rxBytes; i++) {
                if (data[i] == 0x59 && data[i+1] == 0x59) {
                    break;
                }
            }
            
            //until the end of the data stream, read the 3rd and 4th byte in every 9 bytes (distance data)
            for (i+=2; i < rxBytes; i+= 9) {
                
                distConcat = (((uint16_t)data[i+1] << 8) | data[i]);
                avgDist += distConcat;
                distCounter++;
                
            }
            
            avgDist /= distCounter;
            printf("distance: %d\n", avgDist);
            
            //ESP_LOGI(RX_TASK_TAG, "Distance: %d", avgDist);
            
            vTaskDelay(1000 / portTICK_RATE_MS);
        }
    
    }
    
    free(data);
}

void app_main(void)
{
    init();
    xTaskCreate(rx_task, "uart_rx_task", 1024*2, NULL, configMAX_PRIORITIES, NULL);
    //xTaskCreate(tx_task, "uart_tx_task", 1024*2, NULL, configMAX_PRIORITIES-1, NULL);
}
