//
// Created by Alex on 2020-12-09.
//

#include "WallManager.h"

std::vector<Wall*> WallManager::m_walls;

void WallManager::addBuildingToVector(Wall* wall) {
    m_walls.push_back(wall);
}

std::vector<Wall*> WallManager::getWalls() {
    return m_walls;
}

void WallManager::drawWalls() {
    for(Wall* wall : m_walls){
        wall->draw();
    }
}

void WallManager::destructor() {
    for(Wall* wall : m_walls){
        delete wall;
    }
}
