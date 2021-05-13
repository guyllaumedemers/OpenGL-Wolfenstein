#ifndef J03_H2_GROUPTP_UIMANAGER_H
#define J03_H2_GROUPTP_UIMANAGER_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "../entities/Player.h"
#include "TextureManager.h"

using namespace std;

class UiManager {
private:
    int health;
    int ammo;
    TTF_Font *font;
    static GLuint m_barTextureId;
    static GLuint m_weaponTextureId;
    static std::vector<GLuint> m_weaponTextureIds;
public:
    static bool hasFired;

    UiManager();

    ~UiManager();

    void init();

    void update(Player *_player);

    void renderBar(const double &X, const double &Y, const double &Z, const double &width, const double &height);

    void renderWeapon(const int weapon_nb, const double &X, const double &Y, const double &Z, const double &width,
                      const double &height);

    void renderText(const TTF_Font *Font, const GLubyte &R, const GLubyte &G, const GLubyte &B, const double &X,
                    const double &Y, const double &Z, const std::string &Text);

    void render();

    void quit();

    void setHealth(int value);

    void renderWeapon();


    void setAmmo(int value);

    int getHealth();

    int getAmmo();
};


#endif //J03_H2_GROUPTP_UIMANAGER_H
