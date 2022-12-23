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

class App {
public:
  App();

  ~App();

  [[noreturn]] void run();

  void addSendingQueueToServer(TaskQueue<char, 10, 100> *sendingQueue);

  void addReceiveQueue(TaskQueue<char, 10, 100> * receiveQueue);

private:
  TaskQueue<char, 10, 100> *m_receivingQueueChar;
  TaskQueue<char, 10, 100> *m_sendingQueueToServer;
  std::queue<std::string> m_queueMessFromTasks;
  std::string name{"MAIN APP"};

  CGpio m_GreenLed{GPIOG, LD3_Pin};

  bool sendMessageToServer(const std::string &mess);

  bool getMessFromQueue();

};


#endif//INC_429TESTS_APP_H
