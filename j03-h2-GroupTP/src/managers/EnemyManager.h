//
// Created by gdemers on 12/7/2020.
//

#ifndef J03_SU_H20_GROUPTP_ENEMYMANAGER_H
#define J03_SU_H20_GROUPTP_ENEMYMANAGER_H
#pragma once

#include "../utils/IncludeHeader.h"
#include "../entities/Enemy.h"
#include "../entities/Player.h"
#include "MapManager.h"
#include "CollisionManager.h"

class EnemyManager {
    static bool m_isInitialized;
    static int m_cpt;
    static const int m_maxEnemies = 10;
    static bool m_isEnemyColliding;
public:
    static std::map<int, Enemy *> s_enemies;

    static void initialize();

    static void update(Player *target);

    static void checkCollision();

    static bool checkIsInitialized();

    static void checkCollisionBetweenEnemiesAndPlayerBullets(Player *player, Enemy *enemy);

    static void clear();
};

#endif //J03_SU_H20_GROUPTP_ENEMYMANAGER_H
