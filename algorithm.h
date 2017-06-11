//
// Created by pwszebor on 03.06.17.
//

#pragma once

#include "apsgError.h"
#include <QVariant>
#include <QJSValue>
#include <iostream>
#include <functional>
#include <thread>

class Algorithm {
public:
    virtual ~Algorithm() {
        std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    }

    virtual QVariant changeParameters(const QJSValue &parameters) = 0;
    virtual void simulate(std::function<void(SIMULATION_STATUS)> changeStatus) = 0;
    virtual void stopSimulation() = 0;
    virtual std::vector<std::vector<double>> getData(const QString &plotType) = 0;
};
