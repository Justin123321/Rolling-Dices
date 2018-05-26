 #include "Character.h"

// constructor for both monster and hero
Character::Character(const char* filename, bool id, float x=0,
		     float y=0, float w=0.5, float h=0.5) : TexRect(filename, x, y, w, h) {
  
  // initialize character's status
  this->id = id;      // declare this object is hero or monster
  if (id == 1) {
    maxHealth = health = 10;      // hero has 10 health at start
    damage = 3;       // hero deals 3 damage to monster at start
    direction = 'u';  // when hero is constructed, he is facing up
  } else {
    maxHealth = health = 8;       // monster has 8 health at start
    damage = 3;       // monster has 3 damage to hero at start
    ox = x;           // store original x position which is passed into constructor
    oy = y;           // store original y position which is passed into constructor
  }
  status = 1;         // object is alive
}

// increase character's health according to the score
void Character:: incHealth(int score) {
  float inc;
  if (id == 1) {
    inc = float(score);
    maxHealth += inc;
    health += inc;
  } else {
    inc = float(score);
    maxHealth += inc;
    health += inc;
  }
}

// increase character's damage according to the score
void Character::incDamage(int score) {
  if (id == 1) {
    damage += float(score/3.0);
  } else {
    damage += float(score/1.5);
  }
}

// an interface to update character's status as score is increasing
void Character::upgrade(int score) {
  incHealth(score);
  incDamage(score);
}

// when character gets hurt, calculate character's health
void Character::hurted(float damage) {
  if (health <= damage) {
    health = 0;
    status = 0; // character is dead, when character's health <= damage it taken
  } else {
    health -= damage; // calculate character's health
    x -= 0.05;
    y -= 0.05;
  }
}

// return how many damage dealed by character
float Character::attack() const {
  return damage;
}

// return 0 for hero is dead and return 1 for hero is alive
bool Character::getStatus() const {
  return status;
}

// this function is only used for monster, monster traces hero
// monster keeps moving toward to the hero(center of hero)
// the function takes in upleft coordinates of hero and calculate
// the center of hero
void Character::tracing(float lx, float ly, float rate, float w, float h) {
  // hero's center coordinates
  float cx = lx + (w/2);
  float cy = ly - (h/2);

  // distances between monster and hero
  float distX = cx - x;
  float distY = cy - y;

  if (distX > 0) {
    moveRight(rate);
  } else {
    moveLeft(rate);
  } 

  if (distY > 0) {
    moveUp(rate);
  } else {
    moveDown(rate);
  }
}

bool Character::touch(float lx, float ly, float hw, float hh){
  float rightx = x+w;
  float downy = y-h;
  
  if(contains(lx, ly) || contains(lx + hw, ly) || contains(lx, ly -hh) || contains (lx +hw, ly -hh)){
    return true;	
  }
  return false;
}

void Character::reborn() {
    if (!id && !status) {
        x = ox;
        y = oy;
	health = maxHealth;
	status = !status;
    }
}

float Character::getCX() const {
  return x+w/2;
}

float Character::getCY() const {
  return y-h/2;
}

float Character::getHealth() const {
  return health;
}
