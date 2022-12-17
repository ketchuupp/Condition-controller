//
// Created by arekc on 03/11/2022.
//

#include "MainController.h"
#include <debug.hpp>

MainController::~MainController() {
  for (auto ctrlObj: mControlledObjects) delete ctrlObj;
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

  mControlledObjects.push_back(new ControlledObject(name, sensor));
  if (mControlledObjects.back() == nullptr) {
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
  for (auto obj : mControlledObjects){
    if (obj->getMName() == objName)
      controlled_obj = obj;
  }

  if (controlled_obj == nullptr){

  }
  return true;
}


