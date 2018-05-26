#ifndef CHARACTER_H
#define CHARACTER_H
#include "TexRect.h"

class Character : public TexRect {
 private:
  
  bool id;         // 0 for monster and 1 for hero
  float maxHealth; // maximum health
  float health;    // character's health
  float damage;    // character's attack damage
  bool status;     // 1 for alive and 0 for dead
  float ox;        // store original x position
  float oy;        // store original y position

  void incHealth(int); // increase health
  void incDamage(int); // increase damage

 public:
  
  char direction; // hero's direction
  
  // constructor
  Character(const char*, bool, float, float, float, float);

  float getCX() const;

  float getCY() const;

  void upgrade(int);

  void hurted(float);

  float attack() const;

  bool getStatus() const;
  
  bool touch(float, float, float, float);

  void tracing(float, float, float, float, float);
    
  void reborn();

  float getHealth() const;
};

#endif
