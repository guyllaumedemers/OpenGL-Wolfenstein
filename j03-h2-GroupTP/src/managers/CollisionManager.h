//
// Created by Alex on 2020-12-07.
//

#ifndef J03_SU_H20_GROUPTP_COLLISIONMANAGER_H
#define J03_SU_H20_GROUPTP_COLLISIONMANAGER_H
#pragma once
#include "../utils/IncludeHeader.h"
#include "../entities/SphereCollider.h"

class CollisionManager {

public:
    static bool checkSphereCollisions(SphereCollider sphere1, SphereCollider sphere2);
};


#endif //J03_SU_H20_GROUPTP_COLLISIONMANAGER_H