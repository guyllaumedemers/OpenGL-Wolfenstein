//
// Created by gpelletier on 12/8/2020.
//

#ifndef J03_H2_GROUPTP_CHECKERPLANE_H
#define J03_H2_GROUPTP_CHECKERPLANE_H
#pragma once
#include "IncludeHeader.h"

class CheckerPlane {

    float m_mapsize;
    GLuint m_idTexture;
    unsigned char m_texture_data[2][2][4] = {
            0, 0, 0, 255,       // [0][0][]
            255, 255, 255, 255, // [0][1][]
            255, 255, 255, 255, // [1][0][]
            0, 0, 0, 255        // [1][1][]
    };

public:

    CheckerPlane(float mapsize);

    ~CheckerPlane();

    void draw();
};

#endif //J03_H2_GROUPTP_CHECKERPLANE_H
