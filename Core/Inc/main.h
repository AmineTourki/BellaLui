/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_dma.h"

#include "stm32f4xx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CAN_communication.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* USER CODE BEGIN Private defines */
#define LED_TIM_ARR 1000
#define LED_nR_Pin GPIO_PIN_7
#define LED_nR_GPIO_Port GPIOA
#define LED_nG_Pin GPIO_PIN_14
#define LED_nG_GPIO_Port GPIOB
#define LED_nB_Pin GPIO_PIN_15
#define LED_nB_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define BOARD_LED_R (255)
#define BOARD_LED_G ( 31)
#define BOARD_LED_B (  0)
#define CAN_ID CAN_ID_DEFAULT

#ifdef MAIN_BOARD
#define BOARD_LED_R (0)
#define BOARD_LED_G (100)
#define BOARD_LED_B (0)
#define CAN_ID CAN_ID_MAIN_BOARD
#endif

#ifdef BLACK_BOX_BOARD
#define BOARD_LED_R (0)
#define BOARD_LED_G (100)
#define BOARD_LED_B (0)
#define CAN_ID CAN_ID_BLACK_BOX_BOARD
#endif

#ifdef TELEMETRY_BOARD
#define BOARD_LED_R (80)
#define BOARD_LED_G (50)
#define BOARD_LED_B (0)
#define CAN_ID CAN_ID_TELEMETRY_BOARD
#endif

#ifdef AIRBRAKE_BOARD
#define BOARD_LED_R (100)
#define BOARD_LED_G (0)
#define BOARD_LED_B (100)
#define CAN_ID CAN_ID_AIBRAKE_BOARD
#endif

#ifdef DEBUG_BOARD
#define BOARD_LED_R (50)
#define BOARD_LED_G (50)
#define BOARD_LED_B (50)
#define CAN_ID CAN_ID_DEBUG_BOARD
#endif

// define board config
#ifdef MAIN_BOARD
#define GPS
#define KALMAN
#define CAN_LED
//#define CERNIER_LEGACY_DATA
#define SDCARD
#endif

#ifdef BLACK_BOX_BOARD
#define SDCARD
#define SENSOR
#define GPS
#endif

#ifdef TELEMETRY_BOARD
#define SDCARD
#define XBEE
#define CAN_LED
#endif

#ifdef AIRBRAKE_BOARD
#define AB_CONTROL
#define ROCKET_FSM
#define SENSOR
#define CAN_LED
//#define SDCARD
#endif

#ifdef DEBUG_BOARD
#define SENSOR
#define SDCARD
#endif

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
