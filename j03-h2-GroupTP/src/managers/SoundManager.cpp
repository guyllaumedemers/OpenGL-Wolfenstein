//
// Created by gpelleti on 12/15/2020.
//

#include "SoundManager.h"

std::map<std::string, Mix_Music*> SoundManager::m_musicMap;
std::map<std::string, Mix_Chunk*> SoundManager::m_chunkMap;


void SoundManager::init() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,  2, 2048 ) >= 0 ){

        for (auto &m : glob::rglob({"assets/music/*.wav", "assets/music/*.mp3"})) {
            std::string music_name = m.filename().string().substr(0, m.filename().string().find_last_of('.'));
            loadMusic(m.string(), music_name);
        }

        for (auto &m : glob::rglob({"assets/sounds/*.wav", "assets/sounds/*.mp3"})) {
            std::string chunk_name = m.filename().string().substr(0, m.filename().string().find_last_of('.'));
            loadChunk(m.string(), chunk_name);
        }
    }
    else{
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void SoundManager::loadMusic(const std::string &path, const std::string &name) {

    if(m_musicMap.find(name) == m_musicMap.end()){
        Mix_Music *music = Mix_LoadMUS(path.c_str());
        if(music != NULL){
            m_musicMap.insert({name, music});
        }
        else{
            SDL_Log("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        }
    }
}

void SoundManager::loadChunk(const std::string &path, const std::string &name) {

    if(m_chunkMap.find(name) == m_chunkMap.end()){
        Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
        if(chunk != NULL){
            m_chunkMap.insert({name, chunk});
        }
        else{
            SDL_Log("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        }
    }
}

Mix_Music *SoundManager::getMusic(const std::string &name) {
    if(m_musicMap.find(name) != m_musicMap.end())
        return m_musicMap.find(name)->second;
    return nullptr;
}

Mix_Chunk *SoundManager::getChunk(const std::string &name) {
    if(m_chunkMap.find(name) != m_chunkMap.end())
        return m_chunkMap.find(name)->second;
    return nullptr;
}

void SoundManager::clear() {

    for(const auto& mm : m_musicMap){
        Mix_FreeMusic(mm.second);
        m_chunkMap.erase(mm.first);
    }
    m_musicMap.clear();

    m_chunkMap.clear();
    for(const auto& mc : m_chunkMap){
        Mix_FreeChunk(mc.second);
        m_chunkMap.erase(mc.first);
    }
    m_chunkMap.clear();
}
