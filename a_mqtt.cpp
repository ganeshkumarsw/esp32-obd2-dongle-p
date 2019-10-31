#include <Arduino.h>
#include "config.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "app.h"
#include "a_mqtt.h"

char MQTT_Server[200] = MQTT_URL;
//char MQTT_Server[200] = {13,126,50,237};

/* create an instance of PubSubClient client */
WiFiClient MQTT_WifiClient;
PubSubClient MQTT_Client(MQTT_WifiClient);


void MQTT_ReceivedCallback(char *topic, byte *payload, unsigned int length)
{
    ESP_LOGI("MQTT", "Message received: %s", topic);

    // ESP_LOGI("MQTT", "payload: ");
    // for (int i = 0; i < length; i++)
    // {
    //     Serial.print((char)payload[i]);
    // }
    // Serial.println();

    APP_ProcessData(payload, length, APP_CHANNEL_MQTT);
}

void MQTT_Init(void)
{
    /* configure the MQTT server with IPaddress and port */
    MQTT_Client.setServer(MQTT_Server, 1883);
    /* this receivedCallback function will be invoked 
  when client received subscribed topic */
    MQTT_Client.setCallback(MQTT_ReceivedCallback);
}

void MQTT_Task(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;

    ESP_LOGI("MQTT", "Task Started");

    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    ESP_LOGI("MQTT", "uxHighWaterMark = %d", uxHighWaterMark);


    while (1)
    {
        if (!MQTT_Client.connected())
        {
            ESP_LOGI("MQTT", "connecting ...");
            /* client ID */
            String clientId = "ESP32Client";

            /* connect now */
            if (MQTT_Client.connect(clientId.c_str(), NULL, NULL))
            {
                ESP_LOGI("MQTT", "connected");
                /* subscribe topic with default QoS 0*/
                MQTT_Client.subscribe("REQUEST");
            }
            else
            {
                ESP_LOGI("MQTT", "failed, status code = %d try again in 5 seconds", MQTT_Client.state());
                /* Wait 5 seconds before retrying */
                vTaskDelay(5000 / portTICK_PERIOD_MS);
            }
        }

        MQTT_Client.loop();

        vTaskDelay(10 * portTICK_PERIOD_MS);
    }
}

void MQTT_Write(uint8_t *payLoad, uint16_t len)
{
    MQTT_Client.publish("RESPONSE", payLoad, len);
}