//
// Created by pwszebor on 03.06.17.
//

#pragma once

#include <QtQml/QJSValue>
#include <QVariant>
#include "algorithm.h"
#include <armadillo>

class Lms : public Algorithm {
    typedef arma::Col<double> vectorCol;
    typedef arma::Row<double> vectorRow;
    typedef arma::Mat<double> matrix;

public:
    static Lms &sharedInstance();

    QVariant changeParameters(const QJSValue &parameters) override;
    void simulate(std::function<void(SIMULATION_STATUS)> changeStatus) override;
    void stopSimulation() override;

private:
    arma::Col<double> parseVector(const QString &filePath);
    void executeAlgorithm(std::function<void(SIMULATION_STATUS)> changeStatus);

private:
    Lms();
    virtual ~Lms();
    Lms(const Lms &) = delete;
    Lms(Lms &&) = delete;

    std::atomic<bool> _stopExecution;

    vectorCol _x;
    vectorCol _d;
    unsigned long long _L;
    double _alpha;

    vectorRow _e;
    vectorRow _y;
    matrix _ff;
};
