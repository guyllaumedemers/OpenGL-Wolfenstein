//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_ENEMY_H
#define J03_SU_H20_GROUPTP_ENEMY_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "Unit.h"

enum class EnemyType {
    Monster, Boss, Soldier
};
// Attack Animation only has 3 sprites while all the other animations have 5 sprites
enum class EnemyAnimationType {
    Back, Forward, Left, Left_Back, Right, Right_Back, Side_Left, Side_Right, Death, Attack
};

class Enemy : virtual public Unit {
    int m_maxCol;
    int m_animationCol;
    Timer *p_animation;
    const int m_nbTexture = 5;
    const int m_nbTextureAttack = 3;
    const std::string m_path_soldierT = "assets/textures/enemies/soldier/";
    const std::string m_animationForward = "forward_";
    const std::string m_animationAttack = "attack_";
    const std::string m_animationDeath = "death_";
public:
    Enemy(EnemyType enemyType, float posX, float posZ);

    ~Enemy();

    void handleTexture(EnemyAnimationType enemyAnimationType);

    void nextAnimation(Uint32 deltaTime);

    int getCurrentCol();

    int getMaxCol();

    void setMaxCol(int nbCol);

    Timer *getAnimationTimer();

    std::string getAnimationForwardPathT();

    std::string getAnimationAttackPathT();

    std::string getAnimationDeathPathT();
};

#endif //J03_SU_H20_GROUPTP_ENEMY_H
