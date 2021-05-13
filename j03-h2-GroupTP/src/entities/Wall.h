//
// Created by Alex on 2020-12-07.
//

#ifndef EXO3JOUR8_BUILDING_H
#define EXO3JOUR8_BUILDING_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "SphereCollider.h"

class Wall {
    float m_posX = 0;
    float m_posY = 0;
    float m_posZ = 0;
    float m_scale = 0;
    GLuint m_textureId = 0;
    SphereCollider m_sphereCollider;
    GLuint idList = 0;
public:
    Wall(float scale, GLuint textureId, float xPos, float yPos, float zPos);

    ~Wall();

    void draw();

    SphereCollider &getSphereCollider();

    float getWallPosZ();
};


#endif //EXO3JOUR8_BUILDING_H
