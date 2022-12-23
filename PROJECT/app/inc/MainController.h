//
// Created by arekc on 03/11/2022.
//

#ifndef INC_429TESTS_MAINCONTROLLER_H
#define INC_429TESTS_MAINCONTROLLER_H

#include "ControlledObject.h"
#include "TaskQueue.hpp"
#include <IOutputDeviceController.h>
#include <IConditionSensor.h>
#include <string>
#include <queue>

class MainController {
public:
  bool createControlledObject(const std::string& name, IConditionSensor *sensor);

  bool addOutputDeviceToObject(const std::string& objName, IOutputDeviceController *dev, ControlledObject::controlled_by ctrl_by,
                               ControlledObject::state_device state);

  virtual ~MainController();
  void updateControlledObjectsStates()
  {
    for (auto &obj : mControlledObjects)
      obj->doAllOperations();
  }

  void addSendingQueueToMainApp(TaskQueue<char, 10, 100> *sendingQueue);

  void addReceiveQueue(TaskQueue<char, 10, 100> * receiveQueue);

  [[noreturn]] void run();

private:
  std::string name{"MAIN CONTROLLER"};
  std::queue<std::string> queueMessFromTasks;
  TaskQueue<char, 10, 100> *receiveQueueChar;
  TaskQueue<char, 10, 100> *sendingQueueToMainApp;

  std::vector<ControlledObject *> mControlledObjects;

  bool sendMessageToMainApp(const std::string &mess);

  bool getMessFromQueue();
};


#endif //INC_429TESTS_MAINCONTROLLER_H
