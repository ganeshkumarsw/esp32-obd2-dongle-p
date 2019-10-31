#ifndef __A_MQTT_H__
#define __A_MQTT_H__


#ifdef __cplusplus
extern "C" {
#endif

void MQTT_Init(void);
void MQTT_Task(void *pvParameters);
void MQTT_Write(uint8_t *payLoad, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif