//
// Created by gpelleti on 12/8/2020.
//

#ifndef J03_H2_GROUPTP_SKYBOX_H
#define J03_H2_GROUPTP_SKYBOX_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "../managers/TextureManager.h"

class Skybox {

private:
    float v1_4 = .25f;
    float v2_4 = .50f;
    float v3_4 = .75f;
    float v4_4 = 1.0f;
    float v1_3 = 1.0f/3.0f;
    float v2_3 = 2.0f/3.0f;
    float v3_3 = 1.0f;

    float m_mapSizeX = 0;
    float m_mapSizeZ = 0;
    GLuint m_textureId;

public:

    Skybox();
    ~Skybox();

    void draw();
};
#endif //J03_H2_GROUPTP_SKYBOX_H
