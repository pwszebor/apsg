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
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
}

Lms::Lms() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _stopExecution = false;
}

Lms &Lms::sharedInstance() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    static Lms instance;
    return instance;
}

QVariant Lms::changeParameters(const QJSValue &parameters) {
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
    unsigned long long L = Lstr.toULongLong(&success, 10);
    if (!success || L < 2) {
        return ERR_INVALID_L;
    }
    QString alphaStr = parameters.property("alpha").toString();
    double alpha = alphaStr.toDouble(&success);
    if (!success && alpha >= 0.0) {
        return ERR_INVALID_ALPHA;
    }

    _x = xVector;
    _d = dVector;
    _L = L;
    _alpha = alpha;

    return ERR_NONE;
}

arma::Col<double> Lms::parseVector(const QString &filePath) {
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

void Lms::simulate(std::function<void(SIMULATION_STATUS)> changeStatus) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    changeStatus(SIM_SIMULATING);
    auto execute = std::bind(&Lms::executeAlgorithm, this, std::placeholders::_1);
    std::thread(execute, changeStatus).detach();
}

void Lms::stopSimulation() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _stopExecution = true;
}

void Lms::executeAlgorithm(std::function<void(SIMULATION_STATUS)> changeStatus) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";

    const unsigned long long N = _x.n_elem;
    vectorRow e(N, arma::fill::zeros);
    vectorRow y(N, arma::fill::zeros);
    matrix ff(_L, N, arma::fill::zeros);
    vectorCol f_n(_L, arma::fill::zeros);
    vectorCol x_n(_L, arma::fill::zeros);

    for (unsigned long long n = 0; n < N; ++n) {
        if (_stopExecution) {
            _stopExecution = false;
            changeStatus(SIM_STOPPED);
            return;
        }

        x_n = arma::shift(x_n, 1); x_n(0) = _x(n);  // x_n = [x(n); x_n(1:end-1,1)];

        y(n) = arma::as_scalar(f_n.t() * x_n);      // y(n) = f_n' * x_n;
        e(n) = _d(n) - y(n);                        // e(n) = d(n) - y(n);
        f_n = f_n + _alpha * e(n) * x_n;            // f_n = f_n + alpha * e(n) * x_n;

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

std::vector<std::vector<double>> Lms::getData(const QString &plotType) {
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
