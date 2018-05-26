#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "TexRect.h"
#include "Character.h"
#include "AnimatedRect.h"
#include "Bullet.h"
#include <vector>
#include <iostream>
using namespace std;

class App: public GlutApp {
  // Maintain app state here
  float mx;
  float my;
  float score;
    
 public:
  // Constructor, to initialize state
  App(const char* label, int x, int y, int w, int h);
  
  // These are the events we want to handle
  void draw();
  void keyPress(unsigned char key);
  void mouseDown(float x, float y);
  void mouseDrag(float x, float y);
    
  void specialKeyPress(int key);
  
  void specialKeyUp(int key);
    
  void idle();

  ///////////////////////////////////////////////////////////////
  // figures that should draw on screen
  
  Character* prince;               // prince

  vector<Bullet*> clip;              // vector that stores bullets
  
  vector<Character*> monsters;
  
  //Character* monster;                // monster

  TexRect* background;               // background on screen
  
  AnimatedRect* gameOver;            // game over screen
  
  //////////////////////////////////////////////////////////////
  
  // determine Character's moving direction
  bool up;
  bool down;
  bool left;
  bool right;
  
  bool touched;

  // determine game's process
  bool hunting;
  bool game_over;

  int getScore() const;

  void incScore();

};

#endif
