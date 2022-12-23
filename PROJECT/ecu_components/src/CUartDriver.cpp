//
// Created by arekc on 26/11/2022.
//

#include "CUartDriver.h"

TRACE_INIT

CUartDriver *CUartDriver::instance = nullptr;

CUartDriver::CUartDriver() {

  uartInstance.at(0).ID = 5;
  uartInstance.at(0).m_uart = &huart5;
  HAL_UART_Receive_IT(uartInstance.at(0).m_uart, uartInstance.at(0).rxData, 1);
}

CUartDriver &CUartDriver::getInstance() {
  if (instance == nullptr)
    instance = new CUartDriver();

  return *instance;
}

CUartDriver::~CUartDriver() = default;

bool CUartDriver::sent_message(int uartID, std::string &&mess) {
  return send(uartID, mess.c_str(), mess.size());
}

bool CUartDriver::sent_message(int uartID, std::string &mess) {
  return send(uartID, mess.c_str(), mess.size());
}

bool CUartDriver::send(int uartID, const char *mess, size_t size) {

  auto uartTransmit = [=](uartHandler &obj) {
    auto result = HAL_UART_Transmit(obj.m_uart, reinterpret_cast<const uint8_t *>(mess),
                                    size, HAL_MAX_DELAY);
    if (result != HAL_OK)
      return false;
    return true;
  };

  for (auto &uart: uartInstance) {
    if (uart.ID == uartID)
      return uartTransmit(uart);
  }

  return false;
}

void CUartDriver::uartCallback(UART_HandleTypeDef *huart) {
  auto receiveDataIT = [=](uartHandler &obj) {
    if (*obj.rxData == '~') {
//      TRACE_ARG("%s", obj.receiveMsg.c_str());
      if (obj.queueMessages.size() == obj.maxQueueSize) {
        TRACE_ARG("UART ID: %d - Unavailable add another message. Queue is overflow.", obj.ID);
        sent_message(obj.ID, "ERROR - the message has not been received");
      } else
        obj.queueMessages.push(std::move(obj.receiveMsg));

      obj.receiveMsg.clear();
    } else {
      obj.receiveMsg += static_cast<char>(*obj.rxData);
    }

    HAL_UART_Receive_IT(obj.m_uart, obj.rxData, 1);
  };

  for (auto &uart: uartInstance) {
    if (uart.m_uart == huart)
      receiveDataIT(uart);
  }
}

std::optional<std::string> CUartDriver::getMessage(int uartID) {
  for (auto &uart: uartInstance) {
    if (uart.ID == uartID) {
      if (uart.queueMessages.empty())
        return {};

      auto buff = std::move(uart.queueMessages.front());
      uart.queueMessages.pop();
      return buff;
    }
  }
  return {};
}





