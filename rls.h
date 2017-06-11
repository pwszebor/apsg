//
// Created by pwszebor on 09.06.17.
//

#pragma once

#include "algorithm.h"
#include <armadillo>
#include <QtCore/QVariant>
#include <QtQml/QJSValue>

class Rls : public Algorithm {
    typedef arma::Col<double> vectorCol;
    typedef arma::Row<double> vectorRow;
    typedef arma::Mat<double> matrix;

public:
    static Rls &sharedInstance();

    QVariant changeParameters(const QJSValue &parameters) override;
    void simulate(std::function<void(SIMULATION_STATUS)> changeStatus) override;
    void stopSimulation() override;
    std::vector<std::vector<double>> getData(const QString &plotType) override;

private:
    arma::Col<double> parseVector(const QString &filePath);

    void executeAlgorithm(std::function<void(SIMULATION_STATUS)> changeStatus);

private:
    Rls();
    virtual ~Rls();
    Rls(const Rls &) = delete;
    Rls(Rls &&) = delete;

    std::atomic<bool> _stopExecution;

    vectorCol _x;
    vectorCol _d;
    unsigned long long _L;
    double _lambda;
    double _gamma;

    vectorRow _e;
    vectorRow _y;
    matrix _ff;
};



