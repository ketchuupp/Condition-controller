//
// Created by arekc on 17/12/2022.
//

#ifndef INC_429TESTS_UARTSERVER_H
#define INC_429TESTS_UARTSERVER_H

#include <CUartDriver.h>
#include <queue>

class UartServer {
private:
  constexpr static int uartInstance = 5;
  CUartDriver *uart;
  static UartServer *instance;
  std::queue<std::string> queueMess;

  UartServer();

  xQueueHandle *m_queueAppToUartServer;


  bool getMessFromQueue();

public:
  static UartServer &getInstance();

  [[noreturn]] void run();

  void addQueueAppToUartServerHandler(xQueueHandle *queueAppToUartServer) { m_queueAppToUartServer = queueAppToUartServer; }
};


#endif //INC_429TESTS_UARTSERVER_H
