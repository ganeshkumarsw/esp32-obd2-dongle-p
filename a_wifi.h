#ifndef __A_WIFI_H__
#define __A_WIFI_H__

#ifdef __cplusplus
extern "C" {
#endif

void WIFI_Init(void);
void WIFI_Task(void *pvParameters);
void WIFI_Soc_Write(uint8_t *payLoad, uint16_t len);
void WIFI_WebSoc_Write(uint8_t *payLoad, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif