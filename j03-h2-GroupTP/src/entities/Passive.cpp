//
// Created by gdemers on 12/7/2020.
//

#include "Passive.h"

Passive::Passive(PassiveType type, Vector3D_WHD pos) : m_type(type), m_pos(pos){
    
    m_texturestr = "";

    switch(m_type){
        case AMMO:
            m_texturestr = "ammoc05";
            m_amount = 50;
            break;
        case HEALTH:
            m_texturestr = "medbox";
            m_amount = 25;
            break;
        default:
            break;
    }

    if(TextureManager::getTextureID(m_texturestr) <= 0 ){
        SDL_Log("Invalid Passive texture");
    }

    m_sphereCollider = {pos.x, pos.y, pos.z, pos.w * 4};

    listId = glGenLists(1);
    glNewList(listId, GL_COMPILE);
    glBegin(GL_QUADS);

    // bottom
    glTexCoord2f(0,1); glVertex3f(-1,-1,-1);
    glTexCoord2f(0,0); glVertex3f(-1,-1,1);
    glTexCoord2f(1,0); glVertex3f(1,-1,1);
    glTexCoord2f(1,1); glVertex3f(1,-1,-1);

    // left
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,1,1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,1);

    // front
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(0,0); glVertex3f(1,-1,-1);
    glTexCoord2f(0,1); glVertex3f(1,1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,1,-1);

    // right
    glTexCoord2f(1,1); glVertex3f(1,-1,-1);
    glTexCoord2f(0,1); glVertex3f(1,1,-1);
    glTexCoord2f(0,0); glVertex3f(1,1,1);
    glTexCoord2f(1,0); glVertex3f(1,-1,1);

    // top
    glTexCoord2d(0, 0); glVertex3f(-1, 1, -1);
    glTexCoord2d(1, 0); glVertex3f(-1, 1, 1);
    glTexCoord2d(1, 1); glVertex3f(1, 1, 1);
    glTexCoord2d(0, 1); glVertex3f(1, 1, -1);

    // back
    glTexCoord2d(0, 0); glVertex3f(-1,-1,1);
    glTexCoord2d(1, 0); glVertex3f(1,-1,1);
    glTexCoord2d(1, 1); glVertex3f(1,1,1);
    glTexCoord2d(0, 1); glVertex3f(-1,1,1);

    glEnd();
    glEndList();
}

Passive::~Passive() = default;

void Passive::draw() {
    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID(m_texturestr));
    glColor3f(1, 1, 1);

    glTranslatef(m_pos.x, m_pos.y, m_pos.z);
    glScaled(m_pos.w, m_pos.h, m_pos.d);

    glCallList(listId);

    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

int Passive::getAmount() const {
    return m_amount;
}

SphereCollider &Passive::getSphereCollider() {
    return m_sphereCollider;
}

PassiveType Passive::getType() {
    return m_type;
}
