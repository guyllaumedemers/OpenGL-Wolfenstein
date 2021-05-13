//
// Created by gdemers on 12/7/2020.
//

#include "TextureManager.h"

std::map<std::string, Texture *> TextureManager::s_textureMap;


void TextureManager::addT(GLuint idTexture, const std::string &nameT) {
    Texture *tempT = new Texture{idTexture, 1};
    s_textureMap[nameT] = tempT;
}

void TextureManager::deleteT(const std::string &nameT) {
    for (auto it = s_textureMap.begin(); it != s_textureMap.end(); ++it) {
        if (it->first == nameT) {
            s_textureMap.erase(it->first);
            break;
        }
    }
}

void TextureManager::loadT(const std::string &path, const std::string &nameT, bool mipmap) {
    bool isLoaded = false;
    GLuint idTexture = loadTexture(path.c_str(), mipmap);
    if (idTexture != 0) {
        for (auto it = s_textureMap.begin(); it != s_textureMap.end(); ++it) {
            if (it->first == nameT) {
                isLoaded = true;
                s_textureMap.at(it->first)->m_nbTime++;
                break;
            }
        }
        if (!isLoaded) {
            addT(idTexture, nameT);
        }
    } else { SDL_Log("GLuint idTexture invalid"); }
}

GLuint TextureManager::getTextureID(const std::string &nameT) {
    for (auto it = s_textureMap.begin(); it != s_textureMap.end(); ++it) {
        if (it->first == nameT) {
            return s_textureMap.at(it->first)->m_idTexture;
        }
    }
    return -1;
}

void TextureManager::clear() {
    s_textureMap.clear();
}

void TextureManager::init() {
    for (auto &p : glob::rglob({"assets/**/*.png", "assets/**/*.jpg", "assets/**/*.bmp"})) {
        std::string texture_name = p.filename().string().substr(0, p.filename().string().find_last_of('.'));
        loadT(p.string(), texture_name, false);
    }
}
