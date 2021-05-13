//
// Created by gdemers on 12/7/2020.
//

#include "EnemyManager.h"

std::map<int, Enemy *> EnemyManager::s_enemies;
int EnemyManager::m_cpt = 0;
bool EnemyManager::m_isInitialized = false;
bool EnemyManager::m_isEnemyColliding = false;

void EnemyManager::initialize() {
    const int selectValue = 10;
    glPushMatrix();
    if (!m_isInitialized) {
        int value = 0;
        float cubeScale = 1.0f;
        float xPos = ReadFromFile::getLineCount() - cubeScale;
        float yPos = 1.0f;
        float zPos = -ReadFromFile::getLineLength() + cubeScale;
        glTranslatef(xPos, yPos, zPos);
        for (int i = 0; i < ReadFromFile::getLineCount(); ++i) {
            for (int j = 0; j < ReadFromFile::getLineLength(); ++j) {
                value = rand() % 300;
                std::string index = MapManager::getMapStrings().at(i);
                int textureId = index.at(j) - 48;

                if (textureId == 0 && m_cpt < m_maxEnemies && value == selectValue) {
                    EnemyManager::s_enemies.insert(
                            std::pair<int, Enemy *>(m_cpt++, new Enemy(EnemyType::Soldier, xPos, zPos)));
                }
                if (j < ReadFromFile::getLineLength()) {
                    zPos += cubeScale * 2;
                    glTranslatef(0, 0, cubeScale * 2);
                }
            }
            xPos -= cubeScale * 2;
            zPos -= ReadFromFile::getLineLength() * 2;

            glTranslatef(-cubeScale * 2, 0, -ReadFromFile::getLineLength() * 2);
        }
    }
    glPopMatrix();
    if (m_cpt == m_maxEnemies) {
        m_isInitialized = true;
    }
}

void EnemyManager::update(Player *target) {
    for (auto it = s_enemies.begin(); it != s_enemies.end(); it++) {
        if (!it->second->checkIsAlive()) {
            // dont update position cuz its dead
            if (it->second->getMaxCol() != 5) {
                it->second->setMaxCol(5);
            }
            if (it->second->getCurrentCol() != 4) {
                it->second->nextAnimation(SDL_GetTicks() - it->second->getAnimationTimer()->getStart());
                // death animation
                it->second->draw(it->second->getAnimationDeathPathT() + std::to_string(it->second->getCurrentCol()));
            }
        } else {
            // update position and other behaviour
            it->second->update(SDL_GetTicks() - it->second->getAnimationTimer()->getStart(), target);
            // loop animations
            it->second->nextAnimation(SDL_GetTicks() - it->second->getAnimationTimer()->getStart());
            // select animation sprites
            if (it->second->getInRange()) {
                // select looping values of col
                if (it->second->getMaxCol() != 3) {
                    it->second->setMaxCol(3);
                }
                // shooting animation
                it->second->draw(it->second->getAnimationAttackPathT() + std::to_string(it->second->getCurrentCol()));
            } else {
                // select looping values of col
                if (it->second->getMaxCol() != 5) {
                    it->second->setMaxCol(5);
                }
                // forward animation
                it->second->draw(it->second->getAnimationForwardPathT() + std::to_string(it->second->getCurrentCol()));
            }
        }
    }
}

void EnemyManager::checkCollision() {
    for (int j = 0; j < EnemyManager::s_enemies.size(); j++) {
        for (int k = 0; k < WallManager::getWalls().size(); k++) {
            m_isEnemyColliding = CollisionManager::checkSphereCollisions(
                    EnemyManager::s_enemies.at(j)->getCollider(),
                    WallManager::getWalls()[k]->getSphereCollider());
            if (m_isEnemyColliding) {
                EnemyManager::s_enemies.at(j)->rotateWhenCollidingWithWalls();
                break;
            }
        }
        m_isEnemyColliding = false;
    }
}

void EnemyManager::clear() {
    for (auto it = s_enemies.begin(); it != s_enemies.end(); it++) {
        it->second = nullptr;
    }
    s_enemies.clear();
}

bool EnemyManager::checkIsInitialized() {
    return m_isInitialized;
}

void EnemyManager::checkCollisionBetweenEnemiesAndPlayerBullets(Player *player, Enemy *enemy) {
    for (int i = 0; i < player->getBullets().size(); i++) {
        bool isColliding = CollisionManager::checkSphereCollisions(player->getBullets().at(i)->getCollider(),
                                                                   enemy->getCollider());
        if (isColliding) {
            enemy->hit();
            player->getBullets().at(i)->disable();
        }
    }
}