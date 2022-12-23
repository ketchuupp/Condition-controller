//
// Created by arekc on 15/10/2022.
//
#include "OSwrappers.hpp"
#include "UartServer.h"
#include "App.h"
#include "MainController.h"
#include "TaskQueue.hpp"

TRACE_INIT


TaskQueue<char, 10, 100> uartServerReceiveQueue("server");
TaskQueue<char, 10, 100> mainAppReceiveQueue("main_app");
TaskQueue<char, 10, 100> mainControllerReceiveQueue("main_controller");

void osStartApp() {
  App app;
  app.addSendingQueueToServer(&uartServerReceiveQueue);
  app.addReceiveQueue(&mainAppReceiveQueue);
  app.run();
}

void osStartUartServer() {
  UartServer &server = UartServer::getInstance();
  server.addReceiveQueue(&uartServerReceiveQueue);
  server.addSendingQueueToApp(&mainAppReceiveQueue);
  server.run();
}

void osStartMainController()
{
  MainController controller;
  controller.addReceiveQueue(&mainControllerReceiveQueue);
  controller.addSendingQueueToMainApp(&mainAppReceiveQueue);
  controller.run();
}


