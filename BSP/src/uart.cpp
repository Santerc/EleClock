//
// Created by LENOVO on 2024/10/22.
//
#include "uart.h"

using namespace bsp;

void Uart::InitDMA() {
    /* open uart idle it */
    __HAL_UART_CLEAR_IDLEFLAG(huart_);
    __HAL_UART_ENABLE_IT(huart_, UART_IT_IDLE);
}
void Uart::SendMessage(uint8_t const* txdata, uint16_t size, uint32_t timeout) {
    /* Start the Transmission process */
    uint32_t ret = HAL_UART_Transmit(huart_, txdata, size, timeout);
    if (ret != HAL_OK) {
        /* Transmission request Error */
        //Uart_ErrorHandler(ret);
    }
}
void Uart::SendMessage_IT(uint8_t const* txdata, uint16_t size) {
    /* Start the Transmission process */
    uint32_t ret = HAL_UART_Transmit_IT(huart_, txdata, size);
    if (ret != HAL_OK) {
        /* Transmission request Error */
        Uart_ErrorHandler(ret);
    }
}
void Uart::SendMessage_IT_Force(uint8_t const* txdata, uint16_t size, uint32_t timeout) {
    __HAL_UNLOCK(huart_);
    uint32_t ret = HAL_UART_Transmit_IT(huart_, txdata, size);
    if (ret != HAL_OK) {
        /* Transmission request Error */
        Uart_ErrorHandler(ret);
    }
}

void Uart::ReceiveDMA(uint8_t rxdata[], uint32_t size) {
    uint32_t tmp1 = 0;
    tmp1 = huart_->RxState;
    if (tmp1 == HAL_UART_STATE_READY) {
        if ((rxdata == NULL) || (size == 0)) {
            return;
        }
        huart_->pRxBuffPtr = rxdata;
        huart_->RxXferSize = size;
        huart_->ErrorCode  = HAL_UART_ERROR_NONE;
        /* Enable the DMA Stream */
        HAL_DMA_Start(huart_->hdmarx, (uint32_t)&huart_->Instance->DR, (uint32_t)(rxdata), size);
        /*
         * Enable the DMA transfer for the receiver request by setting the DMAR bit
         * in the UART CR3 register
         */
        SET_BIT(huart_->Instance->CR3, USART_CR3_DMAR);
    }
}