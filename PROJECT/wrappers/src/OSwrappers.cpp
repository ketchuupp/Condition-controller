//
// Created by arekc on 15/10/2022.
//
#include "OSwrappers.hpp"
#include "UartServer.h"
#include "App.h"

xQueueHandle queueAppToUartServer;

void osStartApp() {
  queueAppToUartServer = xQueueCreate(10, 100*sizeof(char));
  if (queueAppToUartServer == 0)
    TRACE("Cannot create queue");

  App app;
  app.addQueueAppToUartServerHandler(&queueAppToUartServer);
  app.run();
}

void osStartUartServer() {
  UartServer &server = UartServer::getInstance();
  server.addQueueAppToUartServerHandler(&queueAppToUartServer);
  server.run();
}


