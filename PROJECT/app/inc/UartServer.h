//
// Created by arekc on 17/12/2022.
//

#ifndef INC_429TESTS_UARTSERVER_H
#define INC_429TESTS_UARTSERVER_H

#include <CUartDriver.h>
#include <queue>
#include <unordered_map>
#include "TaskQueue.hpp"
#include "ThreadClass.h"

class UartServer : public ThreadClass {
public:
  static UartServer &getInstance();

  [[noreturn]] void run() override;

  void addSendingQueueToApp(TaskQueue<char, 10, 100> *sendingQueue);

private:
  constexpr static int uartInstance = 5;
  CUartDriver *uart;
  static UartServer *instance;
  std::queue<std::string> queueFromUart;
  TaskQueue<char, 10, 100> *sendingQueueToApp;

  UartServer();

  void getMessFromUart();

  bool sendMessageToApp(const std::string &mess);

};


#endif //INC_429TESTS_UARTSERVER_H
