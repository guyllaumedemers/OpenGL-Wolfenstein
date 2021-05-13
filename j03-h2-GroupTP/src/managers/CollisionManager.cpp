//
// Created by Alex on 2020-12-07.
//

#include "CollisionManager.h"

bool CollisionManager::checkSphereCollisions(SphereCollider sphere1, SphereCollider sphere2) {
    int d2 = (sphere1.x - sphere2.x) * (sphere1.x - sphere2.x) + (sphere1.y - sphere2.y) * (sphere1.y - sphere2.y) +
             (sphere1.z - sphere2.z) * (sphere1.z - sphere2.z);

    if (d2 > (sphere1.rayon + sphere2.rayon) * (sphere1.rayon + sphere2.rayon)) {
        return false;
    } else {
        return true;
    }
}

