//
// Created by arekc on 17/12/2022.
//

#include "UartServer.h"
#include <QueueAppServer.h>
#include "cmsis_os.h"

UartServer *UartServer::instance = nullptr;

UartServer::UartServer() {
  uart = &CUartDriver::getInstance();
}

UartServer &UartServer::getInstance() {
  if (instance == nullptr) {
    instance = new UartServer();
  }
  return *instance;
}

[[noreturn]] void UartServer::run() {
  TRACE("UART SERVER START");
  for (;;) {
    getMessFromQueue();
    if (!queueMess.empty()) {
      uart->sent_message(uartInstance, queueMess.front());
      queueMess.pop();
    }

    osDelay(7);
  }
}

bool UartServer::getMessFromQueue() {
  char str[100];
  if (xQueueReceive(*m_queueAppToUartServer,
                    str, portMAX_DELAY) == pdPASS) {
    queueMess.push(str);
  }
  return true;
}




