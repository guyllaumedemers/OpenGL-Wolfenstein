//
// Created by gpelletier on 12/8/2020.
//
#pragma once
#ifndef J03_H2_GROUPTP_NOTIMPLEMENTEDEXCEPTION_H
#define J03_H2_GROUPTP_NOTIMPLEMENTEDEXCEPTION_H

#include <stdexcept>

class NotImplementedException : public std::logic_error {
public:
    NotImplementedException() : std::logic_error("Function not yet implemented") {};
};

#endif //J03_H2_GROUPTP_NOTIMPLEMENTEDEXCEPTION_H