#ifndef BULLET_H
#define BULLET_H

#include "TexRect.h"

class Bullet : public TexRect {

public:
    char direction;

    Bullet(const char*, char, bool, float, float, float, float);

    void move(float);

    void changePosition(float, float);
};

#endif
