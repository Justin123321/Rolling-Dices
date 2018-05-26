#ifndef TexRect_h
#define TexRect_h

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif
#include "RgbImage.h"


class TexRect {
public:
    float x;
    float y;
    float w;
    float h;
    GLuint texture_id;
    
    float xinc;
    float yinc;

    
    bool complete;


    TexRect (const char*, float, float, float, float);
    
    void draw();
    
    bool contains(float, float);
    
    void moveUp(float rate=0.01);
    void moveDown(float rate=0.01);
    void moveLeft(float rate=0.01);
    void moveRight(float rate=0.01);
    
    void jump();
    
    bool movingLeft;
    
    bool rising;
    void change_Picture_File(const char*);
    
  


};

#endif
