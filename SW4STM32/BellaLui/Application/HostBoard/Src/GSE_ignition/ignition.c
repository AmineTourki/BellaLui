/*
 * ignition.c
 *
 *  Created on: 8 Jul 2020
 *      Author: lucaspallez
 */

#include <GSE_ignition/ignition.h>
#include <stm32f446xx.h>
#include "stm32f4xx_hal.h"
#include <cmsis_os.h>
#include <misc/Common.h>
#include <debug/console.h>
#include <CAN_communication.h>
#include <CAN_handling.h>
#include <debug/led.h>

void ignition_sys_init(void)
{
	//Initialise GPIOs on S2 socket
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	rocket_log("Ignition systems initialised.\n");

	//Set Ignition values to low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
}


void TK_ignition_control(void const * argument)
{
	//if xbee code = ignition (D0)
	//if xbee code = ignition sec (D1)

	uint32_t ignition_order = 0;
	uint32_t current_ignition_state = 0;

	 for(;;)
	 {
		 ignition_order = can_getIgnitionState();
		 switch (ignition_order)
		 {
			case 0x22:
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
				if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
					current_ignition_state = STATE_IGNITION_ACTIVE;
				break;
			}
			case 0x44:
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
				if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
					current_ignition_state = STATE_IGNITION_SEC_ACTIVE;
				break;
			}
			case STATE_DISCONNECT_HOSE:
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
					current_ignition_state = STATE_DISCONNECT_HOSE;
				break;
			}
		 }
		 can_setFrame(current_ignition_state, DATA_ID_IGNITION, HAL_GetTick());
		 osDelay(1000);
	 }
}
