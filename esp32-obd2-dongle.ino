#include <Arduino.h>
#include "config.h"
#include "a_led.h"
#include "a_ble.h"
#include "a_uart.h"
#include "a_can.h"
#include "a_wifi.h"
#include "a_mqtt.h"
#include "app.h"

void setup()
{
  Serial.begin(115200);
  Serial.setRxBufferSize(4096);
  String ver = "OBDII USB/Wifi/BT Dongle v" + MAJOR_VERSION;
  ver = ver  + "." + MINOR_VERSION + "." + SUB_VERSION + "_" + ESP.getSdkVersion();

  // ver = ver + MAJOR_VERSION + MINOR_VERSION + SUB_VERSION + "\r\n";
  // printf("OBDII USB/Wifi/BT Dongle v%02d.%02d.%02d\r\n", MAJOR_VERSION, MINOR_VERSION, SUB_VERSION);
  Serial.println(ver);

  // MQTT_Init();
  // disableCore0WDT();
  // disableCore1WDT();

  if (xTaskCreate(CreateTask_Task, "CreateTask_Task", 2000, NULL, tskIDLE_PRIORITY + 10, NULL) != pdTRUE)
  {
    configASSERT(0);
  }
}

void loop()
{
  vTaskDelay(5 / portTICK_PERIOD_MS);
  vTaskDelete(NULL);
}

void CreateTask_Task(void *pvParameters)
{
  UBaseType_t uxHighWaterMark;

  LED_SetLedState(HEART_BEAT_LED, GPIO_STATE_TOGGLE, GPIO_TOGGLE_1HZ);

  ESP_LOGI("CREATE", "Task Started");

  uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
  ESP_LOGI("CREATE", "uxHighWaterMark = %d", uxHighWaterMark);

  if (xTaskCreate(LED_Task, "LED_Task", 8000, NULL, tskIDLE_PRIORITY + 1, NULL) != pdTRUE)
  {
    configASSERT(0);
  }

  if (xTaskCreate(WIFI_Task, "WIFI_Task", 30000, NULL, tskIDLE_PRIORITY + 4, NULL) != pdTRUE)
  {
    configASSERT(0);
  }

  if (xTaskCreate(APP_Task, "APP_Task", 15000, NULL, tskIDLE_PRIORITY + 3, NULL) != pdTRUE)
  {
    configASSERT(0);
  }

  if (xTaskCreate(UART_Task, "UART_Task", 15000, NULL, tskIDLE_PRIORITY + 2, NULL) != pdTRUE)
  {
    configASSERT(0);
  }

  // if (xTaskCreate(BLE_Task, "BLE_Task", 30000, NULL, 5, NULL) != pdTRUE)
  // {
  //   configASSERT(0);
  // }

  // if (xTaskCreate(MQTT_Task, "MQTT_Task", 20000, NULL, 8, NULL) != pdTRUE)
  // {
  //   configASSERT(0);
  // }

  if (xTaskCreate(CAN_Task, "CAN_Task", 10000, NULL, tskIDLE_PRIORITY + 5, NULL) != pdTRUE)
  {
    configASSERT(0);
  }

  vTaskDelete(NULL);
}