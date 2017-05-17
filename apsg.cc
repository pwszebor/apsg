//
// Created by pwszebor on 14.05.17.
//

#include <iostream>
#include "apsg.h"

namespace apsg {

APSG::APSG() {
    connect(this, SIGNAL(numChanged(void)), this, SLOT(numChange(void)));
}

APSG::~APSG() {

}

APSG &APSG::sharedInstance() {
    static APSG instance;
    return instance;
}

QObject *APSG::typeProvider(QQmlEngine *, QJSEngine *) {
    return &APSG::sharedInstance();
}

void APSG::numChange() {
    std::cout << _num;
};

}
