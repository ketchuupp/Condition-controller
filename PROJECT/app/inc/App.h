//
// Created by arekc on 15/10/2022.
//

#ifndef INC_429TESTS_APP_H
#define INC_429TESTS_APP_H

#include "MainController.h"
#include "cmsis_os.h"
#include "main.h"
#include <ConditionSensor.h>
#include <DHT11.h>
#include <Gpio.hpp>

class App {
public:
  App();

  virtual ~App();

  void run();

private:
  Gpio mGreenLed{GPIOG, LD3_Pin};
  MainController mMainController;
};


#endif//INC_429TESTS_APP_H
