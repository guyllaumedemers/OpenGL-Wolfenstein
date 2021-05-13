//
// Created by gpelletier on 12/8/2020.
//
#pragma once
#ifndef J03_SU_H20_GROUPTP_PLAYER_H
#define J03_SU_H20_GROUPTP_PLAYER_H

#include "../utils/IncludeHeader.h"
#include "SphereCollider.h"
#include "Bullet.h"

class Player {

private:
    int m_HP;
    int m_Ammo;
    float m_step;
    float m_camX;
    float m_camY;
    float m_camZ;
    float m_refX;
    float m_refY;
    float m_refZ;
    float m_alpha;
    float m_flySpeed;
    SphereCollider m_sphereCollider;
    std::vector<Bullet *> m_bullets;
public:

    Player(float startPosX, float startPosZ);

    ~Player();

    void cameraPos();

    void move(Direction direction, int dxMouse);

    SphereCollider &getSphereCollider();

    void setCamX(float camX);

    void setCamZ(float camZ);

    float getCamX();

    float getCamZ();

    void setRefX(float refX);

    void setRefZ(float refZ);

    float getRefX();

    float getRefZ();

    float getAlpha();

    int getHP();

    int getAmmo();

    void setHP(int i);

    void setAmmo(int i);

    void fire();

    void drawBullets();

    void updateBulletTrajectory();

    std::vector<Bullet*> getBullets();

    void clear();

    void deleteInGameBullets();
};

#endif //J03_SU_H20_GROUPTP_PLAYER_H