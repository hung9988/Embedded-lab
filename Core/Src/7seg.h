/*
 * 7seg.h - Simple driver for 2x7seg modules
 *
 *  Created on: Mar 20, 2025
 *      Author: TrungNL
 */

#ifndef INC_7SEG_H_
#define INC_7SEG_H_

#include "stm32f4xx_hal.h"

/* Module pin definition */
#define PORT_7SEG_A GPIOA
#define PORT_7SEG_B GPIOA
#define PORT_7SEG_C GPIOA
#define PORT_7SEG_D GPIOB
#define PORT_7SEG_E GPIOB
#define PORT_7SEG_F GPIOB
#define PORT_7SEG_G GPIOB
#define PORT_7SEG_P GPIOB

#define PIN_7SEG_A GPIO_PIN_11
#define PIN_7SEG_B GPIO_PIN_12
#define PIN_7SEG_C GPIO_PIN_15
#define PIN_7SEG_D GPIO_PIN_3
#define PIN_7SEG_E GPIO_PIN_4
#define PIN_7SEG_F GPIO_PIN_5
#define PIN_7SEG_G GPIO_PIN_6
#define PIN_7SEG_P GPIO_PIN_7

#define PORT_7SEG_CONTROL0 GPIOB
#define PIN_7SEG_CONTROL0 GPIO_PIN_9
#define PORT_7SEG_CONTROL1 GPIOB
#define PIN_7SEG_CONTROL1 GPIO_PIN_8

void Set7SegDisplayValue(int val);
void Run7SegDisplay();

#endif /* INC_7SEG_H_ */
