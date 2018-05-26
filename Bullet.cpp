#include "Bullet.h"

Bullet::Bullet(const char* filename, char direction, bool id, float x=0,
                float y=0, float w=0.5, float h=0.5) : TexRect(filename, x, y, w, h) {
    this->direction = direction;
}

void Bullet::changePosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Bullet::move(float rate) {
    if (direction == 'u') {
        y += rate;
    }
    if (direction == 'l') {
        x -= rate;
    }
    if (direction == 'd') {
        y -= rate;
    }
    if (direction == 'r') {
        x += rate;
    }
}



