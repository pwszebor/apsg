//
// Created by pwszebor on 09.06.17.
//

#include "rls.h"
#include <iostream>
#include <QFile>
#include <QUrl>
#include <QTextStream>
#include <future>
#include <thread>

using namespace std::chrono;

Rls::~Rls() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
}

Rls::Rls() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _stopExecution = false;
}

Rls &Rls::sharedInstance() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    static Rls instance;
    return instance;
}

QVariant Rls::changeParameters(const QJSValue &parameters) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    if (!parameters.hasProperty("fileX")) {
        return ERR_INVALID_X;
    }
    if (!parameters.hasProperty("fileD")) {
        return ERR_INVALID_D;
    }
    if (!parameters.hasProperty("L")) {
        return ERR_INVALID_L;
    }
    if (!parameters.hasProperty("lambda")) {
        return ERR_INVALID_LAMBDA;
    }
    if (!parameters.hasProperty("gamma")) {
        return ERR_INVALID_GAMMA;
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
    unsigned long long L = Lstr.toULongLong(&success, 10);
    if (!success || L < 2) {
        return ERR_INVALID_L;
    }
    QString lambdaStr = parameters.property("lambda").toString();
    double lambda = lambdaStr.toDouble(&success);
    if (!success || lambda <= 0.0 || lambda > 1.0) {
        return ERR_INVALID_LAMBDA;
    }
    QString gammaStr = parameters.property("gamma").toString();
    double gamma = gammaStr.toDouble(&success);
    if (!success || gamma < 0.0) {
        return ERR_INVALID_GAMMA;
    }

    _x = xVector;
    _d = dVector;
    _L = L;
    _lambda = lambda;
    _gamma = gamma;

    return ERR_NONE;
}

arma::Col<double> Rls::parseVector(const QString &filePath) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    vectorCol vector;
    QFile fileX(QUrl(filePath).path());
    if (!fileX.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return vector;
    }
    QTextStream stream(&fileX);
    bool success = false;
    unsigned long long n = 0;
    while (!stream.atEnd()) {
        QString line = fileX.readLine();
        vector.resize(n + 1);
        vector(n) = line.toDouble(&success);
        ++n;
        if (!success) {
            vector.reset();
            return vector;
        }
    }
    fileX.close();
    return vector;
}

void Rls::simulate(std::function<void(SIMULATION_STATUS)> changeStatus) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    changeStatus(SIM_SIMULATING);
    auto execute = std::bind(&Rls::executeAlgorithm, this, std::placeholders::_1);
    std::thread(execute, changeStatus).detach();
}

void Rls::stopSimulation() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _stopExecution = true;
}

void Rls::executeAlgorithm(std::function<void(SIMULATION_STATUS)> changeStatus) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";

    const unsigned long long N = _x.n_elem;
    vectorRow e(N, arma::fill::zeros);
    vectorRow y(N, arma::fill::zeros);
    matrix ff(_L, N, arma::fill::zeros);
    vectorCol f_n(_L, arma::fill::zeros);
    vectorCol x_n(_L, arma::fill::zeros);
    matrix P = _gamma * arma::eye(_L, _L);
    double alpha_n = 0.0;

    for (unsigned long long n = 0; n < N; ++n) {
        if (_stopExecution) {
            _stopExecution = false;
            changeStatus(SIM_FAILED);
            return;
        }
//        std::this_thread::sleep_for(20ms);

        x_n = arma::shift(x_n, 1); x_n(0) = _x(n);  // x_n = [x(n); x_n(1:end-1,1)];

        y(n) = arma::as_scalar(f_n.t() * x_n);      // y(n) = f_n' * x_n;
        e(n) = _d(n) - y(n);                        // e(n) = d(n) - y(n);
        alpha_n = 1 / (_lambda + arma::as_scalar(x_n.t() * P * x_n));
        f_n = f_n + alpha_n * e(n) * P * x_n;
        P = (1 / _lambda) * (P - alpha_n * P * x_n * x_n.t() * P);

        ff.col(n) = f_n;                            // ff(:,n) = f_n;
    }

    _y = y;
    _e = e;
    _ff = ff;

//    std::cout << "\ny:\n";
//    _y.print();
//    std::cout << "\ne:\n";
//    _e.print();
//    std::cout << "\nff:\n";
//    _ff.print();
    changeStatus(SIM_COMPLETED);
}

std::vector<std::vector<double>> Rls::getData(const QString &plotType) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    std::vector<std::vector<double>> data;
    if (plotType == "x") {
        data.push_back(arma::conv_to<std::vector<double>>::from(_x));
    } else if (plotType == "d") {
        data.push_back(arma::conv_to<std::vector<double>>::from(_d));
    } else if (plotType == "y") {
        data.push_back(arma::conv_to<std::vector<double>>::from(_y));
    } else if (plotType == "e") {
        data.push_back(arma::conv_to<std::vector<double>>::from(arma::abs(_e)));
    } else if (plotType == "f") {
        _ff.each_row([&data](vectorRow &row) {
            data.push_back(arma::conv_to<std::vector<double>>::from(row));
        });
    }
    return data;
}
