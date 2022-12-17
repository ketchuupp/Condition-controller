//
// Created by arekc on 17/12/2022.
//

#include <Cwrappers.h>
#include <CUartDriver.h>

void uartReceiveGlobalCallback(UART_HandleTypeDef *huart)
{
  CUartDriver &uart = CUartDriver::getInstance();
  uart.uartCallback(huart);
}