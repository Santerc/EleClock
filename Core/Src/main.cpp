/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "clock.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Clock eleclock;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
uint64_t tick = 0;
uint8_t* num;
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  eleclock = Clock(&huart1, HOUR_T_CS_GPIO_Port,
               HOUR_T_CS_Pin, HOUR_O_CS_GPIO_Port, HOUR_O_CS_Pin,
               MIN_T_CS_GPIO_Port, MIN_T_CS_Pin, MIN_O_CS_GPIO_Port,
               MIN_O_CS_Pin, SEC_T_CS_GPIO_Port, SEC_T_CS_Pin,
               SEC_O_CS_GPIO_Port, SEC_O_CS_Pin);
  eleclock.Init();
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (true)
  {
    /* USER CODE END WHILE */
    if(eleclock.AlarmCheck() == true) {  //
      HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_SET);
      HAL_UART_Transmit_IT(&huart1,
                           reinterpret_cast<uint8_t const*>("alarm!\r\n"), 8);
      tick = HAL_GetTick();
    }
    if (HAL_GetTick() - tick > 5000) {
        HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    eleclock.TubeSetNum();
    eleclock.TubeDisplay();
    // HAL_UART_Transmit_IT(&huart1, reinterpret_cast<uint8_t const*>("12\n"), 3);
    // HAL_Delay(2);
    eleclock.RxCallback();

    switch(eleclock.GetCmd()) {
      case cretnas::Terminal::kError:
        eleclock.SendMsg(reinterpret_cast<uint8_t const*>(
            "ErrorMsg ! You Can type Help for more Help :-)\r\n"));
        HAL_Delay(2);
        eleclock.FinishCmd();
        break;
      case cretnas::Terminal::kSetTime:
        eleclock.SetTime();
        eleclock.FinishCmd();
        break;
      case cretnas::Terminal::kSetAlarm:
        eleclock.AlarmAdd();
        eleclock.FinishCmd();
        break;
      case cretnas::Terminal::kDeleteAlarm:
        __NOP();
        eleclock.AlarmDelete();
        eleclock.FinishCmd();
        break;
      case cretnas::Terminal::kShowAlarm:
        eleclock.AlarmShow();

        eleclock.FinishCmd();
        break;
      case cretnas::Terminal::kHelp:
        eleclock.SendMsg(reinterpret_cast<uint8_t const*>(
            "* Time:00:00:00\r\n* Alarm:00:00:00\r\n* ShowAlarm\r\n* "
            "Delete:0\r\n* Help\r\n"));
        HAL_Delay(2);
        eleclock.FinishCmd();
        break;
      default:
        break;
    }

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
 * @brief      定时器中断回调函数
 * @param      htim: 指针指向定时器句柄
 * @retval     无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
  if (htim == &htim2) {
    if (!eleclock.isStop()) {
      eleclock.TikTok();
    }
  }
}

enum class GPIOPin : uint16_t {
  kRight = GPIO_PIN_12,
  kLeft = GPIO_PIN_11,
  kPlus = GPIO_PIN_15,
  kMinus = GPIO_PIN_14,
  kStart = GPIO_PIN_13,
  kStop = GPIO_PIN_10,
};

uint64_t last_exit_tick = 0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  if (HAL_GetTick() - last_exit_tick > 100) {
    last_exit_tick = HAL_GetTick();
  switch(GPIO_Pin) {
    case GPIO_PIN_12:
      eleclock.ConserRight();
    break;
    case GPIO_PIN_11:
      eleclock.ConserLeft();
    break;
    case GPIO_PIN_15:
      if(eleclock.isSetTime()) {
        if(eleclock.GetCorser() == kSecond) {
          eleclock.Splus();
        }else if(eleclock.GetCorser() == kMinute) {
          eleclock.Mplus();
        }else if(eleclock.GetCorser() == kHour) {
          eleclock.Hplus();
        }
      }
    break;
    case GPIO_PIN_14:
      if(eleclock.isSetTime()) {
        if(eleclock.GetCorser() == kSecond) {
          eleclock.SMinus();
        }else if(eleclock.GetCorser() == kMinute) {
          eleclock.MMinus();
        }else if(eleclock.GetCorser() == kHour) {
          eleclock.HMinus();
        }
      }
    break;
    case GPIO_PIN_13:
      if(eleclock.isSetTime()) {
        eleclock.SettingMode(false);
      }else {
        eleclock.Start();
      }
    break;
    case GPIO_PIN_10:
      if(eleclock.isStop()) {
        eleclock.SettingMode(true);
      }else {
        eleclock.Stop();
      }
    break;
    default:
      break;
  }
  }
}

/**
 * @brief      UART RX 回调分配函数
 * @param      huart: uart IRQHandler id
 * @retval     无
 */
// void Uart_RxIdleCallback(UART_HandleTypeDef* huart) {
//   if (huart == &huart1) {
//     eleclock.RxCallback();
//   }
// }

// void Uart_ReceiveHandler(UART_HandleTypeDef* huart) {
//   HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, GPIO_PIN_SET);
//   // clear idle it flag after uart receive a frame data
//   if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) &&
//       __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE)) {
//     /* clear idle it flag avoid idle interrupt all the time */
//     __HAL_UART_CLEAR_IDLEFLAG(huart);
//     /* handle received data in idle interrupt */
//     eleclock.SendMsg(reinterpret_cast<uint8_t const*>("I REC\r\n"));
//         Uart_RxIdleCallback(huart);
//     }
// }
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
