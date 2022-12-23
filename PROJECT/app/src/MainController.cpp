//
// Created by arekc on 03/11/2022.
//

#include "MainController.h"
#include "cmsis_os.h"
#include <debug.hpp>
#include <task.h>

TRACE_INIT(MainController.cpp)

MainController::MainController() {
  m_name = "MAIN CONTROLLER";
}

MainController::~MainController() {
  for (auto ctrlObj: m_ControlledObjects) delete ctrlObj;
}

[[noreturn]] void MainController::run() {
  TRACE("MAIN CONTROLLER START")
  for (;;)
  {
    osDelay(1000);
//    std::string mess = "chuj";
//    sendMessageToMainApp(mess);
//    TRACE("TEST");
  }
}

void MainController::addSendingQueueToMainApp(TaskQueue<char, 10, 100> *sendingQueue) {
  if (sendingQueue == nullptr) {
    TRACE("Incoming parameter pass to nullptr");
    return;
  }
  m_sendingQueueToMainApp = sendingQueue;
}

bool MainController::sendMessageToMainApp(const std::string &mess) {
  std::string toSend = m_name + ' ' + mess;
  auto status = m_sendingQueueToMainApp->pushMessage(toSend.c_str());
  if (status)
    return true;
  return false;
}

bool MainController::createControlledObject(const std::string& name, IConditionSensor *sensor) {
  if (name.empty()) {
    TRACE("Name cannot be empty");
    return false;
  }
  if (sensor == nullptr) {
    TRACE("Argument sensor cannot be nullptr");
    return false;
  }

  m_ControlledObjects.push_back(new ControlledObject(name, sensor));
  if (m_ControlledObjects.back() == nullptr) {
    TRACE_ARG("Cannot create controlled object %s", name.c_str());
    return false;
  }

  return true;
}
// TODO
bool MainController::addOutputDeviceToObject(const std::string& objName, IOutputDeviceController *dev,
                                             ControlledObject::controlled_by ctrl_by,
                                             ControlledObject::state_device state) {
  ControlledObject *controlled_obj;
  for (auto obj : m_ControlledObjects){
    if (obj->getMName() == objName)
      controlled_obj = obj;
  }

  if (controlled_obj == nullptr){

  }
  return true;
}






