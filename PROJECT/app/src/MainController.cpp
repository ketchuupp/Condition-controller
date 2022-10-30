//
// Created by arekc on 03/11/2022.
//

#include "MainController.h"
#include <debug.hpp>

bool MainController::createControlledObject(std::string name, ConditionSensor *sensor) {
  if (name.size() == 0) {
    TRACE("Name cannot be empty");
    return false;
  }
  if (sensor == nullptr) {
    TRACE("Argument sensor cannot be nullptr");
    return false;
  }

  mControlledObjects.push_back(new ControlledObject(name, sensor));
  if (mControlledObjects.back() == nullptr) {
    TRACE_ARG("Cannot create controlled object %s", name.c_str());
    return false;
  }

  return true;
}

bool MainController::addOutputDeviceToObject(std::string name, OutputDeviceController *dev,
                                             ControlledObject::controlled_by ctrl_by,
                                             ControlledObject::state_device state) {
  ControlledObject *controlled_obj;
  for (auto obj : mControlledObjects){
    if (obj->getMName() == name)
      controlled_obj = obj;
  }

  if (controlled_obj == nullptr){

  }
}

MainController::~MainController() {
  for (auto ctrlObj: mControlledObjects) delete ctrlObj;
}
