//
// Created by gpelleti on 12/8/2020.
//

#include "Skybox.h"


Skybox::Skybox(){
    m_mapSizeX = ReadFromFile::getLineLength();
    m_mapSizeZ = ReadFromFile::getLineCount();
}

Skybox::~Skybox()  {
    glDeleteTextures(1, &m_textureId);
}

void Skybox::draw(){

    glPushMatrix();
    glTranslatef(0,0,0);
    glScaled(m_mapSizeX, m_mapSizeX, m_mapSizeZ);
    glBindTexture(GL_TEXTURE_2D, TextureManager::getTextureID("grimmnight_skybox"));

    glBegin(GL_QUADS);
    glColor3f(1,1,1);

    //bottom
    glTexCoord2f(v1_4, v1_3); glVertex3f(-1,-1,-1);
    glTexCoord2f(v1_4,0); glVertex3f(-1,-1,1);
    glTexCoord2f(v2_4,0); glVertex3f(1,-1,1);
    glTexCoord2f(v2_4,v1_3); glVertex3f(1,-1,-1);

    //left
    glTexCoord2f(v1_4,v1_3); glVertex3f(-1,-1,-1);
    glTexCoord2f(v1_4,v2_3); glVertex3f(-1,1,-1);
    glTexCoord2f(0,v2_3); glVertex3f(-1,1,1);
    glTexCoord2f(0,v1_3); glVertex3f(-1,-1,1);

    //front
    glTexCoord2f(v1_4,v1_3); glVertex3f(-1,-1,-1);
    glTexCoord2f(v2_4,v1_3); glVertex3f(1,-1,-1);
    glTexCoord2f(v2_4,v2_3); glVertex3f(1,1,-1);
    glTexCoord2f(v1_4,v2_3); glVertex3f(-1,1,-1);

    //back
    glTexCoord2f(v4_4,v1_3); glVertex3f(-1, -1, 1);
    glTexCoord2f(v3_4,v1_3); glVertex3f(1, -1, 1);
    glTexCoord2f(v3_4,v2_3); glVertex3f(1, 1, 1);
    glTexCoord2f(v4_4,v2_3); glVertex3f(-1, 1, 1);

    // right
    glTexCoord2f(v2_4,v1_3); glVertex3f(1, -1, -1);
    glTexCoord2f(v2_4,v2_3); glVertex3f(1, 1, -1);
    glTexCoord2f(v3_4,v2_3); glVertex3f(1, 1, 1);
    glTexCoord2f(v3_4,v1_3); glVertex3f(1, -1, 1);

    //top
    glTexCoord2f(v1_4, v2_3); glVertex3f(-1, 1, -1);
    glTexCoord2f(v1_4, v3_3); glVertex3f(-1, 1, 1);
    glTexCoord2f(v2_4, v3_3); glVertex3f(1, 1, 1);
    glTexCoord2f(v2_4,v2_3); glVertex3f(1, 1, -1);
    glEnd();

    glPopMatrix();
}