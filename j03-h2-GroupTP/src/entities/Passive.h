//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_PASSIVE_H
#define J03_SU_H20_GROUPTP_PASSIVE_H
#pragma once
#include "../utils/IncludeHeader.h"
#include "SphereCollider.h"
#include "../managers/TextureManager.h"

using namespace std;

class Passive {

private:
    int m_amount;
    string m_texturestr;
    GLuint listId;
    PassiveType m_type;
    SphereCollider m_sphereCollider;

public:
    Vector3D_WHD m_pos;
    Passive(PassiveType type, Vector3D_WHD pos);
    ~Passive();

    void draw();
    int getAmount() const;
    SphereCollider &getSphereCollider();
    PassiveType getType();
};

#endif //J03_SU_H20_GROUPTP_PASSIVE_H
