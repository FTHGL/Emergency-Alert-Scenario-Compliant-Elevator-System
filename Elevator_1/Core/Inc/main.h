/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define gas_sensor_Pin GPIO_PIN_5
#define gas_sensor_GPIO_Port GPIOA
#define dc_motor_O1_Pin GPIO_PIN_0
#define dc_motor_O1_GPIO_Port GPIOB
#define dc_motor_O2_Pin GPIO_PIN_1
#define dc_motor_O2_GPIO_Port GPIOB
#define button_0_Pin GPIO_PIN_12
#define button_0_GPIO_Port GPIOB
#define button_1_Pin GPIO_PIN_13
#define button_1_GPIO_Port GPIOB
#define button_2_Pin GPIO_PIN_14
#define button_2_GPIO_Port GPIOB
#define hall_0_Pin GPIO_PIN_15
#define hall_0_GPIO_Port GPIOB
#define hall_1_Pin GPIO_PIN_8
#define hall_1_GPIO_Port GPIOA
#define hall_2_Pin GPIO_PIN_9
#define hall_2_GPIO_Port GPIOA
#define tilt_sensor_Pin GPIO_PIN_10
#define tilt_sensor_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
