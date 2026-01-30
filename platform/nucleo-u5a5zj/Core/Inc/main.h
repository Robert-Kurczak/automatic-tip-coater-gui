/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32u5xx_hal.h"

#include "stm32u5xx_nucleo.h"

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
void ATC_Init();
void ATC_Loop();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Spindle_DIR_Pin GPIO_PIN_2
#define Spindle_DIR_GPIO_Port GPIOE
#define xAxis_STEP_Pin GPIO_PIN_3
#define xAxis_STEP_GPIO_Port GPIOE
#define Spindle_FAULT_Pin GPIO_PIN_4
#define Spindle_FAULT_GPIO_Port GPIOE
#define xAxis_DIR_Pin GPIO_PIN_5
#define xAxis_DIR_GPIO_Port GPIOE
#define xAxis_CS_Pin GPIO_PIN_6
#define xAxis_CS_GPIO_Port GPIOE
#define xAxis_DIAG_Pin GPIO_PIN_1
#define xAxis_DIAG_GPIO_Port GPIOF
#define xAxis_MIN_LIMIT_Pin GPIO_PIN_2
#define xAxis_MIN_LIMIT_GPIO_Port GPIOF
#define xAxis_MIN_LIMIT_EXTI_IRQn EXTI2_IRQn
#define xAxis_MAX_LIMIT_Pin GPIO_PIN_3
#define xAxis_MAX_LIMIT_GPIO_Port GPIOF
#define xAxis_MAX_LIMIT_EXTI_IRQn EXTI3_IRQn
#define LCD_RS_Pin GPIO_PIN_4
#define LCD_RS_GPIO_Port GPIOF
#define tip_LIMIT_Pin GPIO_PIN_5
#define tip_LIMIT_GPIO_Port GPIOF
#define zAxis_STEP_Pin GPIO_PIN_6
#define zAxis_STEP_GPIO_Port GPIOF
#define zAxis_DIR_Pin GPIO_PIN_7
#define zAxis_DIR_GPIO_Port GPIOF
#define zAxis_CS_Pin GPIO_PIN_8
#define zAxis_CS_GPIO_Port GPIOF
#define Spindle_SPEED_Pin GPIO_PIN_9
#define Spindle_SPEED_GPIO_Port GPIOF
#define zAxis_DIAG_Pin GPIO_PIN_10
#define zAxis_DIAG_GPIO_Port GPIOF
#define zAxis_MIN_LIMIT_Pin GPIO_PIN_1
#define zAxis_MIN_LIMIT_GPIO_Port GPIOC
#define zAxis_MIN_LIMIT_EXTI_IRQn EXTI1_IRQn
#define zAxis_MAX_LIMIT_Pin GPIO_PIN_0
#define zAxis_MAX_LIMIT_GPIO_Port GPIOA
#define zAxis_MAX_LIMIT_EXTI_IRQn EXTI0_IRQn
#define Termistor_IN_Pin GPIO_PIN_2
#define Termistor_IN_GPIO_Port GPIOA
#define TouchPanel_IRQ_Pin GPIO_PIN_4
#define TouchPanel_IRQ_GPIO_Port GPIOA
#define TouchPanel_CS_Pin GPIO_PIN_5
#define TouchPanel_CS_GPIO_Port GPIOA
#define yAxis_MAX_LIMIT_Pin GPIO_PIN_10
#define yAxis_MAX_LIMIT_GPIO_Port GPIOB
#define yAxis_MAX_LIMIT_EXTI_IRQn EXTI10_IRQn
#define yAxis_MIN_LIMIT_Pin GPIO_PIN_11
#define yAxis_MIN_LIMIT_GPIO_Port GPIOB
#define yAxis_MIN_LIMIT_EXTI_IRQn EXTI11_IRQn
#define yAxis_DIAG_Pin GPIO_PIN_13
#define yAxis_DIAG_GPIO_Port GPIOB
#define UCPD_FLT_Pin GPIO_PIN_14
#define UCPD_FLT_GPIO_Port GPIOB
#define yAxis_CS_Pin GPIO_PIN_11
#define yAxis_CS_GPIO_Port GPIOD
#define yAxis_STEP_Pin GPIO_PIN_12
#define yAxis_STEP_GPIO_Port GPIOD
#define yAxis_DIR_Pin GPIO_PIN_13
#define yAxis_DIR_GPIO_Port GPIOD
#define Heater_EN_Pin GPIO_PIN_3
#define Heater_EN_GPIO_Port GPIOG
#define UCPD_DBn_Pin GPIO_PIN_5
#define UCPD_DBn_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
