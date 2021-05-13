//
// Created by Alex on 2020-12-04.
//

#include "MapManager.h"

GLuint MapManager::m_textureId = 0;
std::vector<GLuint> MapManager::m_textureIds;
std::vector<std::string> MapManager::m_mapStrings;
bool MapManager::m_mapGenerated = false;

void MapManager::init() {
    ReadFromFile::readMapFile();
    ReadFromFile::readWallTextureFiles();
    m_mapStrings = ReadFromFile::getMapStrings();

    for (int i = 0; i < ReadFromFile::getWallTextureNames().size(); ++i) {
        std::string textureName = ReadFromFile::getWallTexturePath() + ReadFromFile::getWallTextureNames()[i];
        std::string texture_name = ReadFromFile::getWallTextureNames()[i].substr(0, ReadFromFile::getWallTextureNames()[i].find_last_of('.'));
        m_textureIds.push_back(TextureManager::getTextureID(texture_name));
    }
    glEnable(GL_TEXTURE_2D);
}

void MapManager::drawPlane() {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-ReadFromFile::getLineCount(), 0, -ReadFromFile::getLineLength());
    glVertex3f(-ReadFromFile::getLineCount(), 0, ReadFromFile::getLineLength());
    glVertex3f(ReadFromFile::getLineCount(), 0, ReadFromFile::getLineLength());
    glVertex3f(ReadFromFile::getLineCount(), 0, -ReadFromFile::getLineLength());
    glEnd();
    glPopMatrix();
}

void MapManager::generateWalls() {
    if (!m_mapGenerated) {
        float cubeScale = 1;
        float xPos = ReadFromFile::getLineCount() - cubeScale;
        float yPos = 1;
        float zPos = -ReadFromFile::getLineLength() + cubeScale;

        glTranslatef(xPos, yPos, zPos);

        for (int i = 0; i < ReadFromFile::getLineCount(); ++i) {
            for (int j = 0; j < ReadFromFile::getLineLength(); ++j) {

                std::string index = m_mapStrings[i];
                int textureId = index.at(j) - 48;

                if (textureId > 0 && textureId < 9) {
                    Wall *wall = new Wall(cubeScale, m_textureIds[textureId - 1], xPos, yPos, zPos);
                    WallManager::addBuildingToVector(wall);
                }
                else if(textureId == 9){
                    PassiveManager::add(xPos, zPos);
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
    m_mapGenerated = true;
}

void MapManager::destructor() {
    for (int i = 0; i < m_textureIds.size(); ++i) {
        glDeleteTextures(1, &m_textureIds[i]);
    }
}

std::vector<std::string> MapManager::getMapStrings() {
    return m_mapStrings;
}
