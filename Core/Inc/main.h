/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SEC_O_CS_Pin GPIO_PIN_0
#define SEC_O_CS_GPIO_Port GPIOB
#define SEC_T_CS_Pin GPIO_PIN_1
#define SEC_T_CS_GPIO_Port GPIOB
#define MIN_O_CS_Pin GPIO_PIN_2
#define MIN_O_CS_GPIO_Port GPIOB
#define CLEAR_Pin GPIO_PIN_10
#define CLEAR_GPIO_Port GPIOB
#define CLEAR_EXTI_IRQn EXTI15_10_IRQn
#define START_Pin GPIO_PIN_13
#define START_GPIO_Port GPIOB
#define START_EXTI_IRQn EXTI15_10_IRQn
#define UP_Pin GPIO_PIN_14
#define UP_GPIO_Port GPIOB
#define UP_EXTI_IRQn EXTI15_10_IRQn
#define DOWN_Pin GPIO_PIN_15
#define DOWN_GPIO_Port GPIOB
#define DOWN_EXTI_IRQn EXTI15_10_IRQn
#define CURSER_LEFT_Pin GPIO_PIN_11
#define CURSER_LEFT_GPIO_Port GPIOA
#define CURSER_LEFT_EXTI_IRQn EXTI15_10_IRQn
#define CURSER_RIGHT_Pin GPIO_PIN_12
#define CURSER_RIGHT_GPIO_Port GPIOA
#define CURSER_RIGHT_EXTI_IRQn EXTI15_10_IRQn
#define MIN_T_CS_Pin GPIO_PIN_3
#define MIN_T_CS_GPIO_Port GPIOB
#define HOUR_O_CS_Pin GPIO_PIN_4
#define HOUR_O_CS_GPIO_Port GPIOB
#define HOUR_T_CS_Pin GPIO_PIN_5
#define HOUR_T_CS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
