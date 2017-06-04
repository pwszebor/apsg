//
// Created by pwszebor on 04.06.17.
//

#pragma once

#include <QObject>
#include <QString>
#include <map>

enum APSG_ERROR {
    ERR_NONE,
    ERR_INVALID_X,
    ERR_INVALID_D,
    ERR_INVALID_L,
    ERR_INVALID_ALPHA,
    ERR_LENGTH
};

enum SIMULATION_STATUS {
    SIM_STOPPED,
    SIM_SIMULATING,
    SIM_COMPLETED,
    SIM_FAILED
};

static constexpr const char *errorStrings[] = {
        "",
        "Invalid x vector values",
        "Invalid d vector values",
        "Lengths of x and d vectors not matching"
};