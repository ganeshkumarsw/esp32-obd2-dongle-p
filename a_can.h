#ifndef __A_CAN_H__
#define __A_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/can.h"
#include <ESP32CAN.h>
#include <CAN_config.h>

/** \brief CAN Node Bus speed */
// typedef enum {
// 	CAN_SPEED_100KBPS = 100,  /**< \brief CAN Node runs at 100kBit/s. */
// 	CAN_SPEED_125KBPS = 125,  /**< \brief CAN Node runs at 125kBit/s. */
// 	CAN_SPEED_200KBPS = 200,  /**< \brief CAN Node runs at 250kBit/s. */
// 	CAN_SPEED_250KBPS = 250,  /**< \brief CAN Node runs at 250kBit/s. */
// 	CAN_SPEED_500KBPS = 500,  /**< \brief CAN Node runs at 500kBit/s. */
// 	CAN_SPEED_800KBPS = 800,  /**< \brief CAN Node runs at 800kBit/s. */
// 	CAN_SPEED_1000KBPS = 1000 /**< \brief CAN Node runs at 1000kBit/s. */
// } CAN_speed_t;
		
void CAN_Init(void);
void CAN_SetBaud(CAN_speed_t speed);
void CAN_ConfigFilterterMask(uint32_t acceptance_code, bool extId);
void CAN_DeInit(void);
esp_err_t CAN_ReadFrame(CAN_frame_t *frame, TickType_t ticks_to_wait);
esp_err_t CAN_WriteFrame(CAN_frame_t *frame, TickType_t ticks_to_wait);
void CAN_Task(void *pvParameters);
void CAN_SendCmd(uint8_t cmd, uint32_t data);

#ifdef __cplusplus
}
#endif

#endif