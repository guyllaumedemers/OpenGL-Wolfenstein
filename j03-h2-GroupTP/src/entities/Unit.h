//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_UNIT_H
#define J03_SU_H20_GROUPTP_UNIT_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "SphereCollider.h"
#include "Player.h"
#include "../managers/TextureManager.h"
#include "../managers/SoundManager.h"

class Unit {
    enum State {
        Patrol, Chase, Idle
    };
protected:
    bool isTriggeringDeathSFX;
    const int dmg = 3;
    bool isAttacking;
    const float m_dstRange = 5.0f;
    float m_health, m_stamina;
    const float m_maxStamina = 10.0f;
    bool m_isInRange;
    bool m_isDetected;
    bool m_isHit;
    bool m_isAlive;
    bool m_isBored;
    float m_posX, m_posY, m_posZ;
    const float m_speed = 1.0f;
    const Uint32 m_rate_of_fire = 750;
    Timer *p_attackRateTimer;
    Timer *p_inChasingStateTimer;
    Timer *p_chasingCooldownTimer;
    const Uint32 m_cooldown = 1500;
    const Uint32 m_time_before_bored = 3000;
    bool m_isChasing;
    float m_chasingToggleValue;
    SphereCollider m_sphereCollider;
    float m_rotationAngle;

    void timerInit();

public:

    Unit(float posX, float posZ);

    ~Unit();

    virtual void loadTexture(std::string pathT, std::string nameT, bool mipmap);

    virtual void move(Uint32 deltaTime, State state, Player *target);

    virtual void checkDistance(Player *target);

    virtual void checkHealth();

    virtual void checkStamina();

    virtual void update(Uint32 deltaTime, Player *target);

    virtual void attack(Player* target);

    virtual void hit();

    virtual void die();

    virtual float getMagnitude(Player *target);

    virtual void draw(std::string nameT);

    virtual SphereCollider getCollider();

    virtual bool getInRange();

    virtual void rotateWhenCollidingWithWalls();

    virtual void rotateToFacePlayer(Player *target);

    virtual bool checkIsAlive();
};

#endif //J03_SU_H20_GROUPTP_UNIT_H
