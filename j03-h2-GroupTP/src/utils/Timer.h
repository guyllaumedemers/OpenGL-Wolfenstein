//
// Created by gdemers on 12/9/2020.
//

#ifndef J03_H2_GROUPTP_TIMER_H
#define J03_H2_GROUPTP_TIMER_H
#pragma once
#include "IncludeHeader.h"

class Timer {
    Uint32 startTime;
public:
    Timer();

    ~Timer();

    void restart();

    Uint32 getStart();
};

#endif //J03_H2_GROUPTP_TIMER_H
