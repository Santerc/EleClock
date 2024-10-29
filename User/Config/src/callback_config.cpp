#include "callback_config.h"
#include "tim.h"
#include "usart.h"
#include "uart.h"

/**
  * @brief      定时器中断回调函数
  * @param      htim: 指针指向定时器句柄
  * @retval     无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if(htim == &htim2){

    }
}

/**
  * @brief      UART RX 回调分配函数
  * @param      huart: uart IRQHandler id
  * @retval     无
  */
void Uart_RxIdleCallback(UART_HandleTypeDef* huart) {
    if(huart == &huart1){
        /* clear DMA transfer complete flag */
        __HAL_DMA_DISABLE(huart->hdmarx);

        /* handle uart data from DMA */
        int rxdatalen = Const_Remote_RX_BUFF_LEN - bsp::Uart::DMACurrentDataCounter(huart->hdmarx->Instance);


        /* restart dma transmission */
        __HAL_DMA_SET_COUNTER(huart->hdmarx, Const_Remote_RX_BUFF_LEN);
        __HAL_DMA_ENABLE(huart->hdmarx);
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
