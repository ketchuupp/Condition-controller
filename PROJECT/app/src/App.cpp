//
// Created by arekc on 15/10/2022.
//

#include <App.h>
#include <debug.hpp>

App::App() {}

void App::run() {
  for (;;) {
    mGreenLed.toggle();
    osDelay(500);
  }
}

App::~App() {

}
