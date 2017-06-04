//
// Created by pwszebor on 03.06.17.
//

#pragma once

#include "apsgError.h"
#include <iostream>
#include <functional>

class Algorithm {
public:
    virtual ~Algorithm() {
        std::cout << __PRETTY_FUNCTION__ << "\n";
    }

    virtual QVariant changeParameters(const QJSValue &parameters) = 0;
    virtual void simulate(std::function<void(SIMULATION_STATUS)> changeStatus) = 0;
    virtual void stopSimulation() = 0;
};
