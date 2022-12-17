//
// Created by arekc on 26/11/2022.
//

#ifndef INC_429TESTS_CUARTDRIVER_H
#define INC_429TESTS_CUARTDRIVER_H

#include <string>

#include "main.h"
#include "usart.h"
#include <cmsis_os.h>
#include <stm32f4xx_hal_uart.h>
#include <debug.hpp>
#include <queue>
#include <array>
#include <optional>

class CUartDriver {
private:
  struct uartHandler {
    int ID;
    UART_HandleTypeDef *m_uart;
    const size_t maxQueueSize = 5;
    std::queue<std::string> queueMessages;
    uint8_t rxData[1];
    std::string receiveMsg{};
  };

  constexpr static int uartCount = 2;
  std::array<uartHandler, uartCount> uartInstance;

  static CUartDriver *instance;

  CUartDriver();

  bool send(int uartID, const char *mess, size_t size);

public:

  static CUartDriver &getInstance();

  ~CUartDriver();

  bool sent_message(int uartID, std::string &&mess);

  bool sent_message(int uartID, std::string &mess);

  void uartCallback(UART_HandleTypeDef *huart);

  std::optional<std::string> getMessage(int uartID);

};


#endif //INC_429TESTS_CUARTDRIVER_H
