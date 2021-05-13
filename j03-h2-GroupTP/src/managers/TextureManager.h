//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_TEXTUREMANAGER_H
#define J03_SU_H20_GROUPTP_TEXTUREMANAGER_H
#pragma once

#include "../utils/IncludeHeader.h"

struct Texture {
    GLuint m_idTexture;
    int m_nbTime;
};

class TextureManager {
    static void addT(GLuint idTexture, const std::string &nameT);

public:

    static std::map<std::string, Texture *> s_textureMap;

    static void init();

    static void loadT(const std::string &path, const std::string &nameT, bool mipmap);

    static void deleteT(const std::string &nameT);

    static GLuint getTextureID(const std::string &nameT);

    static void clear();
};

#endif //J03_SU_H20_GROUPTP_TEXTUREMANAGER_H
