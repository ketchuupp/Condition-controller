//
// Created by arekc on 20/12/2022.
//

#ifndef INC_429TESTS_TASKQUEUE_HPP
#define INC_429TESTS_TASKQUEUE_HPP

#include "debug.hpp"
#include "queue.h"
#include <optional>
#include <string>

template<typename T, unsigned queue_size, unsigned item_size>
class TaskQueue {
  xQueueHandle m_queue;
  std::string m_name;
public:
  TaskQueue(T &&) = delete;
  TaskQueue(T &) = delete;

  TaskQueue(const std::string &&name) : m_name(name) {
    m_queue = xQueueCreate(queue_size, item_size * sizeof(T));
    if (m_queue == 0) { ;
      //TODO
    }
  }

  ~TaskQueue() {
    if (m_queue != 0) {
      vQueueDelete(m_queue);
    }
  }

  bool pushMessage(const T *message) {
    if (xQueueSend(m_queue, message, portMAX_DELAY) != pdPASS) {
      return false;
    }
    return true;
  }

  std::optional<T*> popMessage() {
    T buff[item_size];
    if (!xQueueReceive(m_queue, &buff, 1) == pdPASS) {
      return {};
    }
    return buff;
  }

  [[nodiscard]] unsigned getItemSize() const { return item_size; }
  [[nodiscard]] const std::string & getName() const { return m_name; }

};


#endif //INC_429TESTS_TASKQUEUE_HPP
