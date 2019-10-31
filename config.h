#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define xstr(s) str(s)
#define str(s) #s

#define IsTimerElapsed(x)   ((x) && (x < (xTaskGetTickCount() / portTICK_PERIOD_MS)))
#define SetTimer(x,y)       {x = (xTaskGetTickCount() / portTICK_PERIOD_MS) + y;}
#define ResetTimer(x)       {x = 0;}

#define MAJOR_VERSION             0
#define MINOR_VERSION             0
#define SUB_VERSION               1

// #define STA_WIFI_SSID       "SMARTRAC Guest"
// #define STA_WIFI_PASSWORD   ""
#define STA_WIFI_SSID       "FRITZ!Box 7560 UU"
#define STA_WIFI_PASSWORD   "aksharaa9003755682"
// #define STA_WIFI_SSID       "AndroidAP"
// #define STA_WIFI_PASSWORD   "9003755682"
#define AP_WIFI_SSID        "ap"
#define AP_WIFI_PASSWORD    "password"
#define MQTT_URL            "ec2-13-126-50-237.ap-south-1.compute.amazonaws.com"

#define CAN_RX_QUEUE_SIZE   50
#define CAN_TX_QUEUE_SIZE   50

#define BLE_CONN_LED    GPIO_NUM_33     // Blue LED
#define HEART_BEAT_LED  BLE_CONN_LED
#define COMM_LED        GPIO_NUM_25     // Yellow LED
#define WIFI_CONN_LED   GPIO_NUM_27     // Green LED
#define SECURITY_LED    GPIO_NUM_26     // Amber LED
#define ERROR_LED       GPIO_NUM_32     // Red LED

typedef enum {
    GPIO_STATE_LOW = 0,
    GPIO_STATE_HIGH,
    GPIO_STATE_TOGGLE,
}gpio_state_t;

typedef enum {
    GPIO_TOGGLE_NONE = 0,
    GPIO_TOGGLE_5HZ = 10,
    GPIO_TOGGLE_1HZ = 50,
}gpio_toggle_t;

#ifdef __cplusplus
}
#endif

#endif