//
// Created by arekc on 23/12/2022.
//

#include "ThreadClass.h"
#include "debug.hpp"

TRACE_INIT(ThreadClass.cpp)

bool ThreadClass::getMessFromQueue() {
  if (m_receivingQueueChar == nullptr) {
    TRACE("Receiving queue is pointing to nullptr")
    return false;
  }

  while (true) {
    auto result = m_receivingQueueChar->popMessage();
    if (!result.has_value())
      break;
    m_queueMessFromTasks.push(result.value());
  }

  return true;
}

void ThreadClass::addReceiveQueue(TaskQueue<char, 10, 100> *receivingQueue) {
  if (receivingQueue == nullptr) {
    TRACE("Incoming parameter pass to nullptr");
    return;
  }

  m_receivingQueueChar = receivingQueue;
}

