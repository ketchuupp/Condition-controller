//
// Created by arekc on 03/11/2022.
//

#ifndef INC_429TESTS_MAINCONTROLLER_H
#define INC_429TESTS_MAINCONTROLLER_H

#include "ControlledObject.h"
#include <IOutputDeviceController.h>
#include <IConditionSensor.h>
#include <string>

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

private:
  std::vector<ControlledObject *> mControlledObjects;
};


#endif //INC_429TESTS_MAINCONTROLLER_H
