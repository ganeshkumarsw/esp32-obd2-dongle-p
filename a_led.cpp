#include <Arduino.h>
#include "config.h"
#include "a_led.h"

gpio_state_t LED_HeartBeatLedState;
gpio_state_t LED_ErrorLedState;
gpio_state_t LED_CommLedState;
gpio_state_t LED_SecurityLedState;
gpio_state_t LED_WifiConnLedState;

uint8_t LED_HeartBeatLedFreq;
uint8_t LED_ErrorLedFreq;
uint8_t LED_CommLedFreq;
uint8_t LED_SecurityLedFreq;
uint8_t LED_WifiConnLedFreq;

void LED_Init(void)
{
    pinMode(GPIO_NUM_18, OUTPUT);
    pinMode(GPIO_NUM_19, OUTPUT);
    pinMode(GPIO_NUM_25, OUTPUT);
    pinMode(GPIO_NUM_26, OUTPUT);
    pinMode(GPIO_NUM_27, OUTPUT);
    pinMode(GPIO_NUM_32, OUTPUT);
    pinMode(GPIO_NUM_33, OUTPUT);

    LED_HeartBeatLedState = GPIO_STATE_TOGGLE;
    LED_HeartBeatLedFreq = GPIO_TOGGLE_1HZ;

    LED_ErrorLedState = GPIO_STATE_LOW;
    LED_CommLedState = GPIO_STATE_LOW;
    LED_SecurityLedState = GPIO_STATE_TOGGLE;
    LED_WifiConnLedState = GPIO_STATE_TOGGLE;
}

void LED_Task(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;
    uint32_t heartBeatLedState;
    uint32_t errorLedState;
    uint32_t commLedState;
    uint32_t securityLedState;
    uint32_t wifiConnState;
    uint32_t freqCntr;

    ESP_LOGI("LED", "Task Started");

    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    ESP_LOGI("LED", "uxHighWaterMark = %d", uxHighWaterMark);

    LED_Init();

    freqCntr = 0;

    while (1)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
        freqCntr++;

        if (LED_HeartBeatLedState == GPIO_STATE_TOGGLE)
        {
            if (LED_HeartBeatLedFreq && ((freqCntr % LED_HeartBeatLedFreq) == 0))
            {
                // if the LED is off turn it on and vice-versa:
                if (heartBeatLedState == GPIO_STATE_LOW)
                {
                    heartBeatLedState = GPIO_STATE_HIGH;
                }
                else
                {
                    heartBeatLedState = GPIO_STATE_LOW;
                }
            }
        }
        else
        {
            heartBeatLedState = LED_HeartBeatLedState;
        }

        if (LED_CommLedState == GPIO_STATE_TOGGLE)
        {
            if (LED_CommLedFreq && ((freqCntr % LED_CommLedFreq) == 0))
            {
                // if the LED is off turn it on and vice-versa:
                if (commLedState == GPIO_STATE_LOW)
                {
                    commLedState = GPIO_STATE_HIGH;
                }
                else
                {
                    commLedState = GPIO_STATE_LOW;
                }
            }
        }
        else
        {
            commLedState = LED_CommLedState;
        }

        if (LED_WifiConnLedState == GPIO_STATE_TOGGLE)
        {
            if (LED_WifiConnLedFreq && ((freqCntr % LED_WifiConnLedFreq) == 0))
            {
                // if the LED is off turn it on and vice-versa:
                if (wifiConnState == GPIO_STATE_LOW)
                {
                    wifiConnState = GPIO_STATE_HIGH;
                }
                else
                {
                    wifiConnState = GPIO_STATE_LOW;
                }
            }
        }
        else
        {
            wifiConnState = LED_WifiConnLedState;
        }

        if (LED_SecurityLedState == GPIO_STATE_TOGGLE)
        {
            if (LED_SecurityLedFreq && ((freqCntr % LED_SecurityLedFreq) == 0))
            {
                // if the LED is off turn it on and vice-versa:
                if (securityLedState == GPIO_STATE_LOW)
                {
                    securityLedState = GPIO_STATE_HIGH;
                }
                else
                {
                    securityLedState = GPIO_STATE_LOW;
                }
            }
        }
        else
        {
            securityLedState = LED_SecurityLedState;
        }

        if (LED_ErrorLedState == GPIO_STATE_TOGGLE)
        {
            if (LED_ErrorLedFreq && ((freqCntr % LED_ErrorLedFreq) == 0))
            {
                // if the LED is off turn it on and vice-versa:
                if (errorLedState == GPIO_STATE_LOW)
                {
                    errorLedState = GPIO_STATE_HIGH;
                }
                else
                {
                    errorLedState = GPIO_STATE_LOW;
                }
            }
        }
        else
        {
            errorLedState = LED_ErrorLedState;
        }

        // set the LED with the ledState of the variable:
        digitalWrite(HEART_BEAT_LED, heartBeatLedState);
        digitalWrite(COMM_LED, commLedState);
        digitalWrite(WIFI_CONN_LED, wifiConnState);
        digitalWrite(SECURITY_LED, securityLedState);
        digitalWrite(ERROR_LED, errorLedState);
    }
}

void LED_SetLedState(gpio_num_t gpio, gpio_state_t state, gpio_toggle_t freq)
{
    switch (gpio)
    {
    case HEART_BEAT_LED:
        LED_HeartBeatLedState = state;
        LED_HeartBeatLedFreq = (uint8_t)freq;
        break;

    case COMM_LED:
        LED_CommLedState = state;
        LED_CommLedFreq = (uint8_t)freq;
        break;

    case WIFI_CONN_LED:
        LED_WifiConnLedState = state;
        LED_WifiConnLedFreq = (uint8_t)freq;
        break;

    case SECURITY_LED:
        LED_SecurityLedState = state;
        LED_SecurityLedFreq = (uint8_t)freq;
        break;

    case ERROR_LED:
        LED_ErrorLedState = state;
        LED_ErrorLedFreq = (uint8_t)freq;
        break;

    default:
        break;
    }
}