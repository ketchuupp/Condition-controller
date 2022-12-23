//
// Created by arekc on 15/10/2022.
//

#ifndef INC_429TESTS_APP_H
#define INC_429TESTS_APP_H

#include "MainController.h"
#include "cmsis_os.h"
#include "main.h"
#include "TaskQueue.hpp"
#include <IConditionSensor.h>
#include <DHT11.h>
#include <CGpio.hpp>
#include <queue>
#include <ThreadClass.h>

class App : public ThreadClass {
public:
  App();

  [[noreturn]] void run() override;

  void addSendingQueueToServer(TaskQueue<char, 10, 100> *sendingQueue);

private:
  TaskQueue<char, 10, 100> *m_sendingQueueToServer;

  CGpio m_GreenLed{GPIOG, LD3_Pin};

  bool sendMessageToServer(const std::string &mess);

};


#endif//INC_429TESTS_APP_H
