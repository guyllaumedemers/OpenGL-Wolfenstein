//
// Created by gdemers on 12/8/2020.
//

#include "Unit.h"

Unit::Unit(float posX, float posZ) {
    m_health = 3, m_stamina = m_maxStamina, m_isAlive = true, m_isInRange = false, m_isHit = false;
    m_isDetected = false, m_isBored = false, m_isChasing = false;
    m_posX = posX;
    m_posZ = posZ;
    m_posY = 1.0f;
    timerInit();
    m_chasingToggleValue = 0.0f; // important value so that we do not reset the timer while chasing every turn
    m_rotationAngle = 0;
    m_sphereCollider = {m_posX, m_posY, m_posZ, 0.5f};
    isAttacking = false;
    isTriggeringDeathSFX = false;
}

Unit::~Unit() {
    delete p_attackRateTimer;
    delete p_inChasingStateTimer;
    delete p_chasingCooldownTimer;
}

void Unit::loadTexture(std::string pathT, std::string nameT, bool mipmap) {
    TextureManager::loadT(pathT, nameT, mipmap);
}

void Unit::move(Uint32 deltaTime, State state, Player *target) {
    if (!m_isInRange && state == State::Patrol) {
        if (deltaTime > 150) {
            // reverse, when angle is 180 cos equals -1 so should do a change in direction
            m_posZ += cos(m_rotationAngle * M_PI / 180) * m_speed;
            m_posX += sin(m_rotationAngle * M_PI / 180) * m_speed;
        }
    } else if (!m_isInRange && state == State::Chase) {
        if (SDL_GetTicks() - p_inChasingStateTimer->getStart() >= m_time_before_bored) {
            m_isBored = true;
            m_isDetected = false;
            p_inChasingStateTimer->restart();
        }
        // TRASH CODE NEED TO CAP THE UNIT MOVEMENT WHEN CHASING
//        if (deltaTime > 150) {
//            m_posZ += abs(target.getCamZ() - m_posZ) * cos(m_rotationAngle * M_PI / 180);
//            m_posX += abs(target.getCamX() - m_posX) * sin(m_rotationAngle * M_PI / 180);
//        }
    } else if (m_isInRange && state == State::Chase) {
        // set position to current position
    } else if (m_isBored && state == State::Idle) {
        // set the position to the current position of the unit
        if (SDL_GetTicks() - p_chasingCooldownTimer->getStart() >= m_cooldown) {
            m_chasingToggleValue = 0;
            p_chasingCooldownTimer->restart();
        }
    }
    m_sphereCollider = {m_posX, m_posY, m_posZ, 0.5f};
}
// could be moved in a math class
/***************************************************************************/
float Unit::getMagnitude(Player *target) {
    float magnitude = 0;
    magnitude = pow((target->getCamX() - m_posX), 2) + pow((target->getCamZ() - m_posZ), 2);
    magnitude = sqrt(magnitude);
    return magnitude;
}

void Unit::checkDistance(Player *target) {
    float magnitude = getMagnitude(target);
    if (magnitude < m_dstRange) {
        m_isInRange = true;
        m_isDetected = true;
        // trigger into chasing mode only the first time, than there is a timer to let
        // the player some time before switching it back to 0.
        if (m_chasingToggleValue == 0) {
            m_isChasing = true;
            m_chasingToggleValue++;
        }
    } else {
        m_isInRange = false;
    }
}

/***************************************************************************/

void Unit::update(Uint32 deltaTime, Player *target) {
    checkDistance(target);
    if (!m_isDetected) {
        move(deltaTime, State::Patrol, target);
    } else {
        rotateToFacePlayer(target);
        if (m_isChasing) {
            // assign current SDL_GetTick to the chasing timer since its at 0 the first Time
            p_inChasingStateTimer->restart();
            m_isChasing = false;
        }
        move(deltaTime, State::Chase, target);
        if (m_isInRange) {
            if (m_isBored) {
                move(deltaTime, State::Idle, target);
            }
            // checkStamina and attack
            checkStamina();
            if (isAttacking) {
                attack(target);
                isAttacking = false;
            }
        }
    }
}

void Unit::attack(Player *target) {
    m_stamina--;
    target->setHP(-dmg);
}

void Unit::checkHealth() {
    if (m_health <= 0) {
        die();
    }
}

void Unit::checkStamina() {
    if (m_stamina <= 0) {
        // using the same timer for the cooldown of the stamina bar but should still work
        if (SDL_GetTicks() - p_attackRateTimer->getStart() >= m_cooldown) {
            m_stamina = m_maxStamina;
            p_attackRateTimer->restart();
        }
    } else {
        if (SDL_GetTicks() - p_attackRateTimer->getStart() >= m_rate_of_fire) {
            isAttacking = true;
            p_attackRateTimer->restart();
        }
    }
}

void Unit::hit() {
    m_health--;
    checkHealth();
}

void Unit::die() {
    m_isAlive = false;
    Mix_Chunk *chunk = SoundManager::getChunk("Death 1");
    if (chunk != nullptr) {
        Mix_PlayChannel(-1, chunk, 0);
    }
}

/*******************************************************************/

void Unit::timerInit() {
    p_attackRateTimer = new Timer();
    p_inChasingStateTimer = new Timer();
    p_chasingCooldownTimer = new Timer();
}

/*******************************************************************/

void Unit::draw(std::string nameT) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(nameT));
    glTranslatef(m_posX, m_posY, m_posZ);
    glRotatef(m_rotationAngle, 0, 1, 0);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2d(0, 0);
    glVertex3d(-1, -1, -1);
    glTexCoord2d(1, 0);
    glVertex3d(1, -1, -1);
    glTexCoord2d(1, 1);
    glVertex3d(1, 1, -1);
    glTexCoord2d(0, 1);
    glVertex3d(-1, 1, -1);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

SphereCollider Unit::getCollider() {
    return m_sphereCollider;
}

bool Unit::getInRange() {
    return m_isInRange;
}

// USE TO CHANGE DIRECTION WHEN COLLIDING
void Unit::rotateWhenCollidingWithWalls() {
    m_rotationAngle += 180;
    if (m_rotationAngle >= 360) {
        m_rotationAngle = 0;
    }
}

void Unit::rotateToFacePlayer(Player *target) {
    m_rotationAngle = target->getAlpha() + 180;
    if (m_rotationAngle >= 360) {
        m_rotationAngle = 0;
    }
}

bool Unit::checkIsAlive() {
    return m_isAlive;
}
