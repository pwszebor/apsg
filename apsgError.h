//
// Created by pwszebor on 04.06.17.
//

#pragma once

enum APSG_ERROR {
    ERR_NONE,
    ERR_INVALID_X,
    ERR_INVALID_D,
    ERR_INVALID_L,
    ERR_INVALID_ALPHA,
    ERR_INVALID_LAMBDA,
    ERR_INVALID_GAMMA,
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
        "Invalid L value",
        "Invalid alpha value",
        "Invalid lambda value",
        "Invalid gamma value",
        "Lengths of x and d vectors not matching"
};
