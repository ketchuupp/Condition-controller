//
// Created by arekc on 16/10/2022.
//

#ifndef INC_429TESTS_DHT11_H
#define INC_429TESTS_DHT11_H

#include "ConditionSensor.h"

class DHT11 : public ConditionSensor {
public:
    DHT11() {};

    ~DHT11() = default;

    bool readSensor() override;
};


#endif //INC_429TESTS_DHT11_H
