//
// Created by arekc on 03/11/2022.
//

#ifndef INC_429TESTS_MAINCONTROLLER_H
#define INC_429TESTS_MAINCONTROLLER_H

#include "ControlledObject.h"
#include "TaskQueue.hpp"
#include "ThreadClass.h"
#include <IOutputDeviceController.h>
#include <IConditionSensor.h>
#include <string>
#include <queue>

class MainController : public ThreadClass {
public:
  MainController();
  bool createControlledObject(const std::string& name, IConditionSensor *sensor);

  bool addOutputDeviceToObject(const std::string& objName, IOutputDeviceController *dev,
                               ControlledObject::controlled_by ctrl_by,
                               ControlledObject::state_device state);

  ~MainController() override;

  void updateControlledObjectsStates()
  {
    for (auto &obj : m_ControlledObjects)
      obj->doAllOperations();
  }

  void addSendingQueueToMainApp(TaskQueue<char, 10, 100> *sendingQueue);

  [[noreturn]] void run() override;

private:
  TaskQueue<char, 10, 100> *m_sendingQueueToMainApp;

  std::vector<ControlledObject *> m_ControlledObjects;

  bool sendMessageToMainApp(const std::string &mess);

};


#endif //INC_429TESTS_MAINCONTROLLER_H
