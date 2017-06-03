//
// Created by pwszebor on 14.05.17.
//

#include <iostream>
#include "apsg.h"

namespace apsg {

using Algorithm = APSG::Algorithm;

std::ostream &operator<<(std::ostream &out, const Algorithm algorithm) {
    out << (algorithm == Algorithm::LMS ? "LMS" : "RLS");
    return out;
}

APSG::APSG() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    _algorithm = Algorithm::LMS;
    connect(this, SIGNAL(algorithmChange(void)), this, SLOT(algorithmChanged(void)));
}

APSG::~APSG() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
}

APSG &APSG::sharedInstance() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    static APSG instance;
    return instance;
}

QObject *APSG::typeProvider(QQmlEngine *, QJSEngine *) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return &APSG::sharedInstance();
}

const Algorithm APSG::algorithm() const {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return _algorithm;
}

void APSG::algorithmChanged() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    std::cout << _algorithm << "\n";
}

void APSG::changeAlgorithm(const Algorithm algorithm) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    _algorithm = algorithm;
    emit algorithmChange();
}

}
