//
// Created by arekc on 17/12/2022.
//

#include "UartServer.h"
#include <QueueAppServer.h>
#include "cmsis_os.h"
#include <string>
#include <algorithm>

TRACE_INIT

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
    getMessFromUart();
    if (!queueFromUart.empty()) {
      std::string message(std::move(queueFromUart.front()));
      queueFromUart.pop();

      std::string command = message.substr(0, message.find('*'));
      if (command == "MSG->") {
        message = message.substr(message.find('*') + 1);
        std::string whereSendCommand = message.substr(0, message.find('*'));

        if (whereSendCommand == "MAIN_APP") {
          message = message.substr(message.find('*') + 1);
          sendMessageToApp(message);
        } else {
          TRACE_ARG("Unknown component - \"%s\" ", whereSendCommand.c_str());
        }

      } else {
        TRACE_ARG("Unknown command - \"%s\" ", command.c_str());
      }


    }

    if (!queueMessFromTasks.empty()) {
      uart->sent_message(uartInstance, queueMessFromTasks.front());
      queueMessFromTasks.pop();
    }

    osDelay(7);
  }
}

void UartServer::getMessFromUart() {
  auto result = uart->getMessage(uartInstance);
  if (result.has_value())
    queueFromUart.push(std::move(result.value()));
}

void UartServer::addReceiveQueue(TaskQueue<char, 10, 100> *receiveQueue) {
  if (receiveQueue == nullptr) {
    TRACE("Incoming parameter pass to nullptr");
    return;
  }

  receiveQueueChar = receiveQueue;
}

void UartServer::addSendingQueueToApp(TaskQueue<char, 10, 100> *sendingQueue) {
  if (sendingQueue == nullptr) {
    TRACE("Incoming parameter pass to nullptr");
    return;
  }

  sendingQueueToApp = sendingQueue;
}

bool UartServer::getMessFromQueue() {
  auto result = receiveQueueChar->popMessage();
  if (!result.has_value())
    return false;

  queueMessFromTasks.push(std::move(result.value()));
  return true;
}

bool UartServer::sendMessageToApp(const std::string &mess) {
  auto status = sendingQueueToApp->pushMessage(mess.c_str());
  if (status)
    return true;

  return false;
}





