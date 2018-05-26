#include "App.h"
static App* singleton;
using namespace std;

void move(int value){
  // looping the animation when game is over
  if (singleton->game_over){
    singleton->gameOver->advance();
  }

  // moving character
  if (singleton->up){
    singleton->prince->moveUp(0.03);
  }
  if (singleton->down){
    singleton->prince->moveDown(0.03);
  }
  if (singleton->left){
    singleton->prince->moveLeft(0.03);
  }
  if (singleton->right){
    singleton->prince->moveRight(0.03);
  }

  // monster is tracing hero if hero is alive
  if (singleton->prince->getStatus()) {
    for (int i = 0; i < 4; i++) {
      singleton->monsters[i]->tracing(singleton->prince->x,
				      singleton->prince->y,
				      0.0013,
				      0.3,
				      0.3);
      //glutTimerFunc(9999, move, value);
      singleton->redraw();
      if (singleton->monsters[i]->touch(singleton->prince->x,
				    singleton->prince->y,
				    0.3, 0.3)) {
	singleton->prince->hurted(singleton->monsters[i]->attack());
	singleton->redraw();
      }
    }
  }

  for (int i = 0; i < singleton->clip.size(); i++) {
    singleton->clip[i]->move(0.01);
    singleton->redraw();
  }

  // check whether bullet hits the monster
  for (int i = 0; i < singleton->clip.size(); i++) {
    for (int j = 0; j < 4; j++) {
      if (singleton->monsters[j]->touch(singleton->clip[i]->x, singleton->clip[i]->y,
				    0.05, 0.05)){
	singleton->monsters[j]->hurted(singleton->prince->attack());
	if (i == 0) {
	  singleton->clip.erase(singleton->clip.begin());
	} else {
	  singleton->clip.erase(singleton->clip.begin()+i-1);
	}
	if (!singleton->monsters[j]->getStatus()) {
	  singleton->incScore();
	  cout << "Score: " << singleton->getScore() << endl;
	  singleton->prince->upgrade(singleton->getScore());
	  singleton->monsters[j]->upgrade(singleton->getScore());
	  singleton->monsters[j]->reborn();
	  cout << "Reborn" << endl;
	}
	cout << "Health: " << singleton->prince->getHealth() << endl;
	cout << "Damage: " << singleton->prince->attack() << endl;
	cout << "Monster Health: " << singleton->monsters[j]->getHealth() << endl;
      }
      singleton->redraw();
    }
  }

  if (singleton->up || singleton->down || singleton->left || singleton->right
      || singleton->hunting){
    singleton->redraw();
    glutTimerFunc(32, move, value);
  }
  
  // hero is dead
  if (!singleton->prince->getStatus()){
    singleton->hunting = false;
    singleton->game_over = true;
    singleton->gameOver->animate();
    glutTimerFunc(32, move, value);
  }
 
  if (singleton->game_over){
    singleton->redraw();
  }
}

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h) {
  // Initialize state variables
  
  singleton = this;
  mx = 0.0;
  my = 0.0;
  
  // initialize score
  score = 0;
  
  background = new TexRect("images/Dungeon.png", -1, 1, 2, 2);
  
  monsters.resize(4);
  
  monsters[0] = new Character("images/monster0.png", 0, 0.75, 0.55, 0.15, 0.15);
  monsters[1] = new Character("images/monster2.png", 0, -0.85, 0.55, 0.15, 0.15);
  monsters[2] = new Character("images/monster3.png", 0, -0.85, -0.45, 0.15, 0.15);
  monsters[3] = new Character("images/monster4.png", 0, 0.65, -0.45, 0.15, 0.15);
  
  prince = new Character("Texture/CHA_Stand.png", 1, 0, 0, 0.28, 0.28);
  
  gameOver = new AnimatedRect("images/game_over.png", 7, 1, -1.0, 0.8, 2, 1.2);
  
  up = down = left = right = game_over = false;
    
  hunting = true;
  
  cout << "Health: ";
  cout << prince->getHealth() << endl;
  cout << "Damage: ";
  cout << prince->attack() << endl;
  
  move(1);
}


void App::specialKeyPress(int key){
  if (key == 100){
    up = false;
    right = false;
    down = false;
    left = true;
    prince->change_Picture_File("Texture/CHA_Left.png");
    prince->direction = 'l';
  }
  if (key == 101){
    up = true;
    right = false;
    down = false;
    left = false;
    prince->change_Picture_File("Texture/CHA_Front.png");
    prince->direction = 'u';
  }
  if (key == 102){
    right = true;
    left = false;
    up = false;
    down = false;
    prince->change_Picture_File("Texture/CHA_Right.png");
    prince->direction = 'r';
  }
  if (key == 103){
    down = true;
    up = false;
    left = false;
    right = false;
    prince->change_Picture_File("Texture/CHA_Back.png");
    prince->direction = 'd';
  } 
  move(1); 
}
void App::specialKeyUp(int key){
  if (key == 100) {
    left = false;
  }
  if (key == 101) {
    up = false;
  }
  if (key == 102) {
    right = false;
  }
  if (key == 103) {
    down = false;
  }
}

void App::draw() {
  
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);
  
  // Set background color to black
  glClearColor(0.0, 0.0, 1.0, 1.0);
  
  // Set up the transformations stack
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  background->draw();

  for (int i = 0; i < 4; i++) {
    monsters[i]->draw();
  }
  //monster->draw();
  
  prince->draw();

  for (int i = 0; i < clip.size(); i++) {
    clip[i]->draw();
  }
  
  gameOver->draw();
     
  // We have been drawing everything to the back buffer
  // Swap the buffers to see the result of what we drew
  glFlush();
  glutSwapBuffers();
}

void App::mouseDown(float x, float y){
  // Update app state
  mx = x;
  my = y; 
}

void App::mouseDrag(float x, float y){
  // Update app state
  mx = x;
  my = y;
}

void App::idle(){}

void App::keyPress(unsigned char key) {
  if (key == 27){
    // Exit the app when Esc key is pressed
    
    delete prince;
    delete background;
    delete this;
    delete gameOver;
    exit(0);
  } 
  if (key == 32){
    clip.push_back(new Bullet("images/ball.png",
			      prince->direction,
			      0,
			      prince->getCX(),
			      prince->getCY(),
			      0.05,
			      0.05));
  }
  //moving = true;
  move(1);
}

int App::getScore() const {
  return score;
}

void App::incScore() {
  score += 1;
}
