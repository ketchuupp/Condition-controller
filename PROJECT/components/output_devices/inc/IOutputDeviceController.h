//
// Created by arekc on 30/10/2022.
//

#ifndef INC_429TESTS_IOUTPUTDEVICECONTROLLER_H
#define INC_429TESTS_IOUTPUTDEVICECONTROLLER_H


class IOutputDeviceController {

public:
  IOutputDeviceController() = default;
  virtual bool turnOn() = 0;
  virtual bool turnOff() = 0;
};


#endif//INC_429TESTS_IOUTPUTDEVICECONTROLLER_H
