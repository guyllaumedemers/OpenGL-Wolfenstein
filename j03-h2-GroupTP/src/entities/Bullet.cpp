//
// Created by gdemers on 12/15/2020.
//

#include "Bullet.h"

Bullet::Bullet(float posX, float posY, float posZ) {
    m_posX = posX;
    m_posY = posY;
    m_posZ = posZ;
    isFire = false;
    m_sphereCollider = {m_posX, m_posY, m_posZ, m_radius};
    m_isDisable = false;
}

Bullet::~Bullet() {

}

void Bullet::draw() {
    glPushMatrix();
    glTranslatef(m_posX, m_posY - m_radius, m_posZ);
    glColor3f(1, 0, 0);
    GLUquadric *params = gluNewQuadric();
    gluQuadricDrawStyle(params, GLU_FILL);
    gluSphere(params, m_radius, 20, 20);
    glPopMatrix();
}

void Bullet::update(float rotationAngle) {
    if (!isFire) {
        m_rotationAngle = rotationAngle;
        m_posZ += cos(m_rotationAngle * M_PI / 180) * m_speed;
        m_posX += sin(m_rotationAngle * M_PI / 180) * m_speed;
        isFire = true;
    } else {
        m_lastRotation = m_rotationAngle;
        m_posZ += cos(m_lastRotation * M_PI / 180) * m_speed;
        m_posX += sin(m_lastRotation * M_PI / 180) * m_speed;
    }
    m_sphereCollider = {m_posX, m_posY, m_posZ, m_radius};
}

SphereCollider Bullet::getCollider() {
    return m_sphereCollider;
}

void Bullet::disable() {
    m_isDisable = true;
}

bool Bullet::isDisable() {
    return m_isDisable;
}
