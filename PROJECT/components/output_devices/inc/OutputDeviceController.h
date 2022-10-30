//
// Created by arekc on 30/10/2022.
//

#ifndef INC_429TESTS_OUTPUTDEVICECONTROLLER_H
#define INC_429TESTS_OUTPUTDEVICECONTROLLER_H


class OutputDeviceController {

public:
  OutputDeviceController() = default;
  virtual bool turnOn(){};
  virtual bool turnOff(){};
};


#endif//INC_429TESTS_OUTPUTDEVICECONTROLLER_H
