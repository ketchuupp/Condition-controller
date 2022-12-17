//
// Created by arekc on 15/10/2022.
//

#ifndef INC_429TESTS_APP_H
#define INC_429TESTS_APP_H

#include "MainController.h"
#include "cmsis_os.h"
#include "main.h"
#include <IConditionSensor.h>
#include <DHT11.h>
#include <CGpio.hpp>

class App {
public:
  App();

  virtual ~App();

  [[noreturn]] void run();

  void
  addQueueAppToUartServerHandler(xQueueHandle *queueAppToUartServer) { m_queueAppToUartServer = queueAppToUartServer; }



private:
  xQueueHandle *m_queueAppToUartServer;
  CGpio mGreenLed{GPIOG, LD3_Pin};
  MainController mMainController;


  bool pushMessToQueue(std::string &mess);

};


#endif//INC_429TESTS_APP_H
