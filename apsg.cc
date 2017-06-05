//
// Created by pwszebor on 14.05.17.
//

#include <iostream>
#include <thread>
#include "apsg.h"
#include "lms.h"

std::ostream &operator<<(std::ostream &out, const APSG::AlgorithmType algorithm) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    out << (algorithm == APSG::AlgorithmType::LMS ? "LMS" : "RLS");
    return out;
}

APSG::APSG() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _algorithmType = AlgorithmType::LMS;
    _algorithm = &Lms::sharedInstance();
    _simulation = SIM_STOPPED;
    connect(this, SIGNAL(algorithmChange(void)), this, SLOT(algorithmChanged(void)));
}

APSG::~APSG() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
}

APSG &APSG::sharedInstance() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    static APSG instance;
    return instance;
}

QObject *APSG::typeProvider(QQmlEngine *, QJSEngine *) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    return &APSG::sharedInstance();
}

const APSG::AlgorithmType APSG::algorithm() const {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    return _algorithmType;
}

void APSG::algorithmChanged() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    std::cout << _algorithmType << "\n";
}

void APSG::changeAlgorithm(const APSG::AlgorithmType algorithm) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _algorithmType = algorithm;
    this->_algorithm = &Lms::sharedInstance();
    emit algorithmChange();
}

QVariant APSG::changeParameters(const QJSValue parameters) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    return _algorithm->changeParameters(parameters);
}

const QString APSG::errorString(int errorCode) const {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    return QString(errorStrings[errorCode]);
}

const int APSG::simulation() const {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    return (int)_simulation;
}

int APSG::simulate() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    auto function = std::bind(&APSG::changeStatus, this, std::placeholders::_1);
    _algorithm->simulate(function);
}

int APSG::stopSimulation() {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _algorithm->stopSimulation();
}

void APSG::changeStatus(SIMULATION_STATUS status) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    _simulation = status;
    emit simulationStatusChanged();
}

void APSG::setDataForPlotter(Plot *plotter, const QString &plotType, const QString &xAxis, const QString &yAxis, bool logarithmic) {
    std::cout << __PRETTY_FUNCTION__ << std::this_thread::get_id() << "\n";
    if (!plotter) {
        return;
    }
    plotter->setData(_algorithm->getData(plotType), xAxis, yAxis, logarithmic);
}
