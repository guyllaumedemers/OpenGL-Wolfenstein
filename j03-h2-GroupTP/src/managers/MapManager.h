//
// Created by Alex on 2020-12-04.
//

#ifndef EXO2JOUR8_GRIDMANAGER_H
#define EXO2JOUR8_GRIDMANAGER_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "TextureManager.h"
#include "WallManager.h"
#include "PassiveManager.h"

class MapManager {
    static GLuint m_textureId;
    static std::vector<GLuint> m_textureIds;
    static std::vector<std::string> m_mapStrings;
    static bool m_mapGenerated;
public:
    static void destructor();

    static void init();

    static void drawPlane();

    static void generateWalls();

    static std::vector<std::string> getMapStrings();
};


#endif //EXO2JOUR8_GRIDMANAGER_H