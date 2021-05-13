//
// Created by gdemers on 12/7/2020.
//

#include "ReadFromFile.h"

std::vector<std::string> ReadFromFile::m_wallTextureNames;
std::string ReadFromFile::m_wallTexturePath = "assets/textures/walls/";
std::string ReadFromFile::m_mapFilename = "assets/map.txt";
std::vector<std::string> ReadFromFile::m_mapStrings;
std::string ReadFromFile::m_tempLine;
int ReadFromFile::m_lineLength = 0;
int ReadFromFile::m_lineCount = 0;

void ReadFromFile::readWallTextureFiles() {
    for (const auto &entry : std::filesystem::directory_iterator(m_wallTexturePath)) {
        m_wallTextureNames.push_back(entry.path().filename().string());
    }
}

std::vector<std::string> ReadFromFile::getWallTextureNames() {
    return m_wallTextureNames;
}

void ReadFromFile::readMapFile() {
    int i = 0;
    std::ifstream inputStream;
    inputStream = std::ifstream(m_mapFilename);

    if (!inputStream) {
        std::cout << "Unable to load map file" << std::endl;
    }

    if (inputStream.is_open()) {
        while (std::getline(inputStream, m_tempLine)) {
            m_mapStrings.push_back(m_tempLine);
            //Debug
            //std::cout << m_mapStrings[i] << std::endl;
            i++;
        }
        inputStream.close();
    }

    m_lineLength = m_tempLine.length();
    m_lineCount = i;

    //Debug
    //std::cout << "Line length: " << m_lineLength << std::endl;
    //std::cout << "Line count: " << m_lineCount << std::endl;
    //for (auto it : m_mapStrings) {
    //    std::cout << it << std::endl;
    //}
}

int ReadFromFile::getLineLength() {
    return m_lineLength;
}

int ReadFromFile::getLineCount() {
    return m_lineCount;
}

std::vector<std::string> ReadFromFile::getMapStrings() {
    return m_mapStrings;
}

std::string ReadFromFile::getWallTexturePath() {
    return m_wallTexturePath;
}