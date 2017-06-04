//
// Created by pwszebor on 03.06.17.
//

#include <iostream>
#include "lms.h"
#include <QFile>
#include <QUrl>
#include <QTextStream>
#include <future>
#include <thread>

Lms::~Lms() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

Lms::Lms() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    _stopExecution = false;
}

Lms &Lms::sharedInstance() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    static Lms instance;
    return instance;
}

QVariant Lms::changeParameters(const QJSValue &parameters) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    if (!parameters.hasProperty("fileX")) {
        return ERR_INVALID_X;
    }
    if (!parameters.hasProperty("fileD")) {
        return ERR_INVALID_D;
    }
    if (!parameters.hasProperty("L")) {
        return ERR_INVALID_L;
    }
    if (!parameters.hasProperty("alpha")) {
        return ERR_INVALID_ALPHA;
    }
    QString pathX = parameters.property("fileX").toString();
    vectorCol xVector = parseVector(pathX);
    if (xVector.is_empty()) {
        return ERR_INVALID_X;
    }
    QString pathD = parameters.property("fileD").toString();
    vectorCol dVector = parseVector(pathD);
    if (dVector.is_empty()) {
        return ERR_INVALID_X;
    }
    if (xVector.n_elem != dVector.n_elem) {
        return ERR_LENGTH;
    }

    bool success = false;
    QString Lstr = parameters.property("L").toString();
    double L = Lstr.toDouble(&success);
    if (!success && L > 0.0) {
        return ERR_INVALID_L;
    }
    QString alphaStr = parameters.property("alpha").toString();
    double alpha = alphaStr.toDouble(&success);
    if (!success && alpha > 0.0) {
        return ERR_INVALID_ALPHA;
    }

    _x = xVector;
    _d = dVector;
    _L = L;
    _alpha = alpha;

    return ERR_NONE;
}

arma::Col<double> Lms::parseVector(const QString &filePath) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    vectorCol vector;
    QFile fileX(QUrl(filePath).path());
    if (!fileX.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return vector;
    }
    QTextStream stream(&fileX);
    bool success = false;
    while (!stream.atEnd()) {
        QString line = fileX.readLine();
        vector << line.toDouble(&success);
        if (!success) {
            vector.reset();
            return vector;
        }
    }
    fileX.close();
    return vector;
}

void Lms::simulate(std::function<void(SIMULATION_STATUS)> changeStatus) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    changeStatus(SIM_SIMULATING);
    std::thread(executeAlgorithm, changeStatus).detach();
}

void Lms::stopSimulation() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    _stopExecution = true;
}

void Lms::executeAlgorithm(std::function<void(SIMULATION_STATUS)> changeStatus) {
    std::cout << __PRETTY_FUNCTION__ << "\n";

    int N = _x.n_elem;
    vectorCol e(N, zeros);
    vectorCol y(N, zeros);
    matrix ff(L, N, zeros);
    vectorRow f_n(L,)

    changeStatus(SIM_COMPLETED);
}
