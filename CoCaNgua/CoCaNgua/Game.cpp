#include "Game.h"
#include <ctime>

/* -- GLOBAL VARIABLES --------------------------------------------------- */
int index = 0;
Vector3 wayPoints[] = {Vector3(-20, 0, -4), 
  Vector3(-16, 0, -4), 
  Vector3(-12, 0, -4), 
  Vector3(-8, 0, -4), 
  Vector3(-4, 0, -4), 
  Vector3(-4, 0, -8), 
  Vector3(-4, 0, -12), 
  Vector3(-4, 0, -16), 
  Vector3(-4, 0, -20), 
  Vector3(0, 0, -20), 
  Vector3(4, 0, -20), 
  Vector3(4, 0, -16), 
  Vector3(4, 0, -12), 
  Vector3(4, 0, -8), 
  Vector3(4, 0, -4)};


Game::Game(void)
{
  lightPosition[0] = 50;
  lightPosition[1] = 50;
  lightPosition[2] = 50;
  lightPosition[3] = 1;
  lightAngle = 0.0;
  lightHeight = 20;

  font = GLUT_BITMAP_8_BY_13;

  Vector3 redStart[] = {Vector3(-16, 0, -16),
                        Vector3(-16, 0, -20),
                        Vector3(-20, 0, -20),
                        Vector3(-20, 0, -16)};
  memcpy(redStartPos, redStart, sizeof(redStart));

  Vector3 greenStart[] = {Vector3(16, 0, 16),
                          Vector3(16, 0, 20),
                          Vector3(20, 0, 20),
                          Vector3(20, 0, 16)};
  memcpy(greenStartPos, greenStart, sizeof(greenStart));

  Vector3 blueStart[] = {Vector3(16, 0, -16),
                         Vector3(16, 0, -20),
                         Vector3(20, 0, -20),
                         Vector3(20, 0, -16)};
  memcpy(blueStartPos, blueStart, sizeof(blueStart));

  Vector3 yellowStart[] = {Vector3(-16, 0, 16),
                           Vector3(-16, 0, 20),
                           Vector3(-20, 0, 20),
                           Vector3(-20, 0, 16)};
  memcpy(yellowStartPos, yellowStart, sizeof(yellowStart));

  /* ROAD
                x  x  G
                x     x
                x     x
                x     x
    B  x  x  x  x     x  x  x  x  x
    x                             x
    x  x  x  x  x     x  x  x  x  Y
                x     x
                x     x
                x     x
                R  x  x
  */

  Vector3 r[] = {Vector3(-20, 0, -4),

    Vector3(-16, 0, -4),
    Vector3(-12, 0, -4),
    Vector3(-8, 0, -4),
    Vector3(-4, 0, -4),
    Vector3(-4, 0, -8),
    Vector3(-4, 0, -12),
    Vector3(-4, 0, -16),

    Vector3(-4, 0, -20),
    Vector3(0, 0, -20),
    Vector3(4, 0, -20),

    Vector3(4, 0, -16),
    Vector3(4, 0, -12),
    Vector3(4, 0, -8),
    Vector3(4, 0, -4),
    Vector3(8, 0, -4),
    Vector3(12, 0, -4),
    Vector3(16, 0, -4),

    Vector3(20, 0, -4),
    Vector3(20, 0, 0),
    Vector3(20, 0, 4),

    Vector3(16, 0, 4),
    Vector3(12, 0, 4),
    Vector3(8, 0, 4),
    Vector3(4, 0, 4),
    Vector3(4, 0, 8),
    Vector3(4, 0, 12),
    Vector3(4, 0, 16),

    Vector3(4, 0, 20),
    Vector3(0, 0, 20),
    Vector3(-4, 0, 20),

    Vector3(-4, 0, 16),
    Vector3(-4, 0, 12),
    Vector3(-4, 0, 8),
    Vector3(-4, 0, 4),
    Vector3(-8, 0, 4),
    Vector3(-12, 0, 4),
    Vector3(-16, 0, 4),

    Vector3(-20, 0, 4),
    Vector3(-20, 0, 0)
  };

  memcpy(road, r, sizeof(r));
}

Game& Game::inst()
{
  static Game Instance;
  return Instance;
}

void Game::initModel()
{
  mBoard       = new Model();
  Model* horse = new Model();
  dice         = new Model();

  mBoard->loadModel("Models/board.obj");
  mBoard->setAnchorPoint(Vector3(0, 0.5, 0));

  dice->loadModel("Models/dice.obj");

  horse->loadModel("Models/knight.obj");
  horse->setAnchorPoint(Vector3(0, -0.5, 0));

  for (int i = 0; i < 4; i++)
  {
    red[i] = new Model(horse);
    red[i]->setColorTint(0.8, 0, 0);    // RED
    red[i]->setPosition(redStartPos[i]);

    green[i] = new Model(horse);
    green[i]->setColorTint(0, 0.8, 0);    // GREEN
    green[i]->setPosition(greenStartPos[i]);

    blue[i] = new Model(horse);
    blue[i]->setColorTint(0, 0, 0.8);    // BLUE
    blue[i]->setPosition(blueStartPos[i]);

    yellow[i] = new Model(horse);
    yellow[i]->setColorTint(0.8, 0.8, 0);    // YELLOW
    yellow[i]->setPosition(yellowStartPos[i]);
  }

  red[1]->setPosition(Vector3(-20, 0, -4));
}

void Game::draw()
{
  // Save current matrix state
  glPushMatrix();

#if SHOW_GRID
  glBegin(GL_LINES);
  glColor3f(0, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(10, 0, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 10, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 10);
  glEnd();

  float posi[3] = {10.0f, 0.0f, 0};
  float color[4] = {1,1,1,1};
  Graphic::inst().drawString3D("x", posi, color, font);

  posi[0] = 0;
  posi[1] = 10;
  Graphic::inst().drawString3D("y", posi, color, font);

  posi[1] = 0;
  posi[2] = 10;
  Graphic::inst().drawString3D("z", posi, color, font);
  /*glBegin(GL_LINES);
  glColor3f(.1, .1, .1);
  for (int i = -100; i < 100; i+=2)
  {
    glVertex3f(100, 0, i);
    glVertex3f(-100, 0, i);

    glVertex3f(i, 0, 100);
    glVertex3f(i, 0, -100);
  }
  glEnd();*/
#endif

  glDisable(GL_COLOR_MATERIAL);

  glLoadName(1);
  mBoard->drawModel();

  for (int i = 0; i < 4; i++)
  {
    glLoadName(RED_1 + i);
    red[i]->drawModel();

    glLoadName(BLUE_1 + i);
    blue[i]->drawModel();

    glLoadName(GREEN_1 + i);
    green[i]->drawModel();

    glLoadName(YELLOW_1 + i);
    yellow[i]->drawModel();
  }

  /*glLoadName(3);
  dice->drawModel();*/

  glEnable(GL_COLOR_MATERIAL);

  /*float pos[3] = {0.0f, 5.0f, 0};
  float colorS[4] = {1,1,1,1};
  drawString3D("Chess board", pos, colorS, font);*/

#if SHOW_LIGHT_SOURCE
  lightPosition[0] = 15*cos(lightAngle);
  lightPosition[1] = lightHeight;
  lightPosition[2] = 15*sin(lightAngle);

  Light::inst().setPosition(lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
  Light::inst().drawLightSource(lightAngle, lightHeight);
#endif // SHOW_LIGHT_SOURCE

  glPopMatrix();
}

void Game::loop()
{
  draw();


}

void Game::demoMove()
{
  if (red[1]->getState() == IDLE)
  {
    srand(time(NULL));
    int diceNum = rand() % 6 + 1;

    int tmp = index + diceNum;
    if (index > 14 || tmp > 14)
    {
      tmp = 0;
      index = 0;
    }

    cout << "Dice: " << diceNum << " Temp: " << tmp << endl;

    red[1]->jumpTo(wayPoints[index], wayPoints[tmp], tmp - index, 1.5);
    index = tmp;
  }
}

Game::~Game(void)
{
}