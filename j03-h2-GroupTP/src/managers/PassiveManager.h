//
// Created by gpelleti on 12/10/2020.
//

#ifndef J03_H2_GROUPTP_PASSIVEMANAGER_H
#define J03_H2_GROUPTP_PASSIVEMANAGER_H

#include "../utils/IncludeHeader.h"
#include "../entities/Passive.h"
#include "../entities/Player.h"
#include "CollisionManager.h"

using namespace std;

class PassiveManager {

private:
    static vector<Passive*> m_vecPassives;
    static float m_size;

public:
    static void destructor();

    static void draw();
    static void checkCollision(Player *player);
    static void add(float xpos, float zpos);
    static void addAmmo(Player *pPlayer, int amount);
    static void addHP(Player *pPlayer, int amount);
};

#endif //J03_H2_GROUPTP_PASSIVEMANAGER_H
