//
// Created by gpelletier on 12/8/2020.
//

#include "CheckerPlane.h"

CheckerPlane::CheckerPlane(float mapsize) : m_mapsize(mapsize) {
    glGenTextures(1,&m_idTexture);
}

CheckerPlane::~CheckerPlane() {
    glDeleteTextures(1, &m_idTexture);
}

void CheckerPlane::draw() {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, m_idTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texture_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-m_mapsize, 0, -m_mapsize);
    glTexCoord2f(m_mapsize / 2, 0.0);
    glVertex3f(m_mapsize, 0, -m_mapsize);
    glTexCoord2f(m_mapsize / 2, m_mapsize / 2);
    glVertex3f(m_mapsize, 0, m_mapsize);
    glTexCoord2f(0.0, m_mapsize / 2);
    glVertex3f(-m_mapsize, 0, m_mapsize);
    glEnd();
    glPopMatrix();
}