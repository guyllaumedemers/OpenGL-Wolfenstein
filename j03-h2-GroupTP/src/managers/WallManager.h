//
// Created by Alex on 2020-12-09.
//

#ifndef J03_H2_GROUPTP_WALLMANAGER_H
#define J03_H2_GROUPTP_WALLMANAGER_H
#pragma once
#include "../entities/Wall.h"

class WallManager {
    static std::vector<Wall *> m_walls;
public:
    static void destructor();

    static void addBuildingToVector(Wall *wall);

    static std::vector<Wall *> getWalls();

    static void drawWalls();
};


#endif //J03_H2_GROUPTP_WALLMANAGER_H
