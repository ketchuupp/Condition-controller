//
// Created by arekc on 16/10/2022.
//

#ifndef INC_429TESTS_DHT11_H
#define INC_429TESTS_DHT11_H

#include "IConditionSensor.h"
#include <dht.h>

class DHT11 : public IConditionSensor {
public:
    DHT11();

    ~DHT11() = default;

    bool readSensor() override;

private:
  DHT_Type_t dht_type{DHT_Type_DHT11};
  DHT_t dht;
};


#endif //INC_429TESTS_DHT11_H
