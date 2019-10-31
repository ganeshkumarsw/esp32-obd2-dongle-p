#ifndef __A_LED_H__
#define __A_LED_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "driver/gpio.h"

void LED_Init(void);
void LED_Task(void *pvParameters);
void LED_SetLedState(gpio_num_t gpio, gpio_state_t state, gpio_toggle_t freq);

#ifdef __cplusplus
}
#endif

#endif