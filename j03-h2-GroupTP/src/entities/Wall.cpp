//
// Created by Alex on 2020-12-07.
//

#include "Wall.h"

Wall::Wall(float scale, GLuint textureId, float xPos, float yPos, float zPos) {
    m_scale = scale;
    m_textureId = textureId;
    m_posX = xPos;
    m_posY = yPos;
    m_posZ = zPos;
    m_sphereCollider = {m_posX, m_posY, m_posZ, 1};
    idList = glGenLists(1);
    glNewList(idList, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glBegin(GL_QUADS);
    //left
    glColor3f(1, 1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 1);
    //front
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(0, 0);
    glVertex3f(1, -1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, -1);
    //right
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(1, -1, 1);
    //back
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, 1);
    //top
    glColor3f(0, 0, 0);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    //bottom
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glEndList();
}

Wall::~Wall() {
    glDeleteLists(idList, 1);
}

void Wall::draw() {
    glPushMatrix();
    glScaled(m_scale, m_scale, m_scale);
    glTranslatef(m_posX, m_posY, m_posZ);
    glCallList(idList);
    glPopMatrix();
}

SphereCollider &Wall::getSphereCollider() {
    return m_sphereCollider;
}

float Wall::getWallPosZ() {
    return m_posZ;
}
