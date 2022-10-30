//
// Created by arekc on 03/11/2022.
//

#ifndef INC_429TESTS_MAINCONTROLLER_H
#define INC_429TESTS_MAINCONTROLLER_H

#include "ControlledObject.h"
#include <OutputDeviceController.h>
#include <ConditionSensor.h>
#include <string>

class MainController {
public:
  bool createControlledObject(std::string name, ConditionSensor *sensor);

  bool addOutputDeviceToObject(std::string name, OutputDeviceController *dev, ControlledObject::controlled_by ctrl_by,
                               ControlledObject::state_device state);

  virtual ~MainController();

private:
  std::vector<ControlledObject *> mControlledObjects;
};


#endif //INC_429TESTS_MAINCONTROLLER_H
