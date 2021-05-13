//
// Created by gpelleti on 12/15/2020.
//

#ifndef J03_H2_GROUPTP_SOUNDMANAGER_H
#define J03_H2_GROUPTP_SOUNDMANAGER_H
#pragma once

#include "../utils/IncludeHeader.h"

class SoundManager {

private:
    static std::map<std::string, Mix_Music*> m_musicMap;
    static std::map<std::string, Mix_Chunk*> m_chunkMap;

public:

    static void init();

    static void loadMusic(const std::string &path, const std::string &name);
    static void loadChunk(const std::string &path, const std::string &name);

    static Mix_Music* getMusic(const std::string &name);
    static Mix_Chunk* getChunk(const std::string &name);

    static void clear();
};
#endif //J03_H2_GROUPTP_SOUNDMANAGER_H
