#include "callback_config.h"
#include "terminal.h"
#include "timer.h"
#include "tim.h"
#include "uart.h"

//TODO: 将整个Config层移至APP中

using namespace cretnas;

Terminal terminal(&huart1);
Timer timer;

/**
  * @brief      定时器中断回调函数
  * @param      htim: 指针指向定时器句柄
  * @retval     无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim == &htim2){
        if(!timer.IsStop()){
            timer.AddSecond();
        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    if(GPIO_Pin == GPIO_PIN_13){

    }
}

/**
  * @brief      UART RX 回调分配函数
  * @param      huart: uart IRQHandler id
  * @retval     无
  */
void Uart_RxIdleCallback(UART_HandleTypeDef* huart) {
    if(huart == &huart1){
        terminal.RxCallBack();
    }
}


void Uart_ReceiveHandler(UART_HandleTypeDef *huart) {
    // clear idle it flag after uart receive a frame data
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE)) {
        /* clear idle it flag avoid idle interrupt all the time */
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        /* handle received data in idle interrupt */
        Uart_RxIdleCallback(huart);
    }
}
