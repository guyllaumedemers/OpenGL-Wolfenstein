//
// Created by gdemers on 12/15/2020.
//

#ifndef J03_H2_GROUPTP_BULLET_H
#define J03_H2_GROUPTP_BULLET_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "SphereCollider.h"

class Bullet {
    float m_posX, m_posY, m_posZ;
    float m_rotationAngle, m_lastRotation;
    const float m_radius = 0.10f;
    const float m_speed = 3.0f;
    SphereCollider m_sphereCollider;
    bool isFire;
    bool m_isDisable;
public:
    Bullet(float posX, float posY, float posZ);

    ~Bullet();

    void draw();

    void update(float rotationAngle);

    SphereCollider getCollider();

    void disable();

    bool isDisable();

};

#endif //J03_H2_GROUPTP_BULLET_H
