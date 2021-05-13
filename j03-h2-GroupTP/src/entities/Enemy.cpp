//
// Created by gdemers on 12/7/2020.
//

#include "Enemy.h"


Enemy::Enemy(EnemyType enemyType, float posX, float posZ) : Unit(posX, posZ) {
    switch (enemyType) {
        case EnemyType::Monster:
            this->m_health = 4.0f;
            // need to implement p_animation for a monster
            break;
        case EnemyType::Boss:
            this->m_health = 12.0f;
            // need to implement p_animation for a boss
            break;
        case EnemyType::Soldier:
            this->m_health = 3.0f;
//            for (int i = (int) EnemyAnimationType::Back; i != (int) EnemyAnimationType::Attack; i++) {
//                handleTexture((EnemyAnimationType) i);
//            }
            break;
    }
    p_animation = new Timer();
    m_animationCol = 0;
    m_maxCol = 5;
}

Enemy::~Enemy() {

}

void Enemy::handleTexture(EnemyAnimationType enemyAnimationType) {
    switch (enemyAnimationType) {
        case EnemyAnimationType::Back:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(
                        m_path_soldierT + std::string("movement/back/back_") + std::to_string(i) + std::string(".png"),
                        "soldier_back_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Forward:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(m_path_soldierT + std::string("movement/forward/forward_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_forward_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Left:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(
                        m_path_soldierT + std::string("movement/left/left_") + std::to_string(i) + std::string(".png"),
                        "soldier_left_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Left_Back:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(m_path_soldierT + std::string("movement/left_back/left_back_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_left_back_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Right:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(
                        m_path_soldierT + std::string("movement/right/right_") + std::to_string(i) +
                        std::string(".png"),
                        "soldier_right_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Right_Back:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(m_path_soldierT + std::string("movement/right_back/right_back_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_right_back_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Side_Left:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(m_path_soldierT + std::string("movement/side_left/side_left_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_side_left_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Side_Right:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(m_path_soldierT + std::string("movement/side_right/side_right_") + std::to_string(i) +
                                  std::string(".png"),
                                  "soldier_side_right_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Death:
            for (int i = 1; i <= m_nbTexture; i++) {
                this->loadTexture(
                        m_path_soldierT + std::string("death/death_") + std::to_string(i) + std::string(".png"),
                        "soldier_death_" + std::to_string(i), true);
            }
            break;
        case EnemyAnimationType::Attack:
            for (int i = 1; i <= m_nbTextureAttack; i++) {
                this->loadTexture(
                        m_path_soldierT + std::string("attack/attack_") + std::to_string(i) + std::string(".png"),
                        "soldier_attack_" + std::to_string(i), true);
            }
            break;
    }
}

void Enemy::nextAnimation(Uint32 deltaTime) {
    if (deltaTime > 150) {
        m_animationCol %= m_maxCol;
        m_animationCol++;
        p_animation->restart();
    }
}

Timer *Enemy::getAnimationTimer() {
    return p_animation;
}

void Enemy::setMaxCol(int nbCol) {
    m_maxCol = nbCol;
}

int Enemy::getMaxCol() {
    return m_maxCol;
}

int Enemy::getCurrentCol() {
    return m_animationCol;
}

std::string Enemy::getAnimationForwardPathT() {
    return m_animationForward;
}

std::string Enemy::getAnimationAttackPathT() {
    return m_animationAttack;
}

std::string Enemy::getAnimationDeathPathT() {
    return m_animationDeath;
}