//
// Created by arekc on 17/12/2022.
//

#ifndef INC_429TESTS_QUEUEAPPSERVER_H
#define INC_429TESTS_QUEUEAPPSERVER_H

#include <queue>
#include <string>
#include <optional>
#include "cmsis_os.h"
#include <debug.hpp>




//public:
  void QueueAppServer();

  void addMessage(std::string mess);

  std::optional<std::string> popMessage();
//};





#endif //INC_429TESTS_QUEUEAPPSERVER_H
