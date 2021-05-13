#ifndef OPENGL_UTIL_H
#define OPENGL_UTIL_H
#pragma once
#include "IncludeHeader.h"


#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

GLuint loadTexture(const char * filename,bool useMipMap = true);
void drawAxis(double scale = 1);


#endif //OPENGL_UTIL_H
