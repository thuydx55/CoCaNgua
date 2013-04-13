#include "Game.h"
#include <ctime>

Game::Game(void)
{
  srand(time(NULL));
  mDiceIsThrown = false;

  lightPosition[0] = 50;
  lightPosition[1] = 50;
  lightPosition[2] = 50;
  lightPosition[3] = 1;
  lightAngle = 0.0;
  lightHeight = 20;

  font = GLUT_BITMAP_8_BY_13;

  playerTurn = RED;

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

  Vector3 rStable[] = {
    Vector3(-16, 0, 0),
    Vector3(-12, 0, 0),
    Vector3(-8, 0, 0),
    Vector3(-4, 0, 0)
  };
  memcpy(redStable, rStable, sizeof(rStable));

  Vector3 gStable[] = {
    Vector3(16, 0, 0),
    Vector3(12, 0, 0),
    Vector3(8, 0, 0),
    Vector3(4, 0, 0)
  };
  memcpy(greenStable, gStable, sizeof(gStable));

  Vector3 bStable[] = {
    Vector3(0, 0, -16),
    Vector3(0, 0, -12),
    Vector3(0, 0, -8),
    Vector3(0, 0, -4)
  };
  memcpy(blueStable, bStable, sizeof(bStable));

  Vector3 yStable[] = {
    Vector3(0, 0, 16),
    Vector3(0, 0, 12),
    Vector3(0, 0, 8),
    Vector3(0, 0, 4)
  };
  memcpy(yellowStable, yStable, sizeof(yStable));

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

  Vector3 r[] = { Vector3(-20, 0, -4),      // RED START

                  Vector3(-16, 0, -4),
                  Vector3(-12, 0, -4),
                  Vector3(-8, 0, -4),
                  Vector3(-4, 0, -4),
                  Vector3(-4, 0, -8),
                  Vector3(-4, 0, -12),
                  Vector3(-4, 0, -16),

                  Vector3(-4, 0, -20),
                  Vector3(0, 0, -20),
                  Vector3(4, 0, -20),       // BLUE START

                  Vector3(4, 0, -16),
                  Vector3(4, 0, -12),
                  Vector3(4, 0, -8),
                  Vector3(4, 0, -4),
                  Vector3(8, 0, -4),
                  Vector3(12, 0, -4),
                  Vector3(16, 0, -4),

                  Vector3(20, 0, -4),
                  Vector3(20, 0, 0),
                  Vector3(20, 0, 4),        // GREEN START

                  Vector3(16, 0, 4),
                  Vector3(12, 0, 4),
                  Vector3(8, 0, 4),
                  Vector3(4, 0, 4),
                  Vector3(4, 0, 8),
                  Vector3(4, 0, 12),
                  Vector3(4, 0, 16),

                  Vector3(4, 0, 20),
                  Vector3(0, 0, 20),
                  Vector3(-4, 0, 20),       // YELLOW START

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

  int c[] = { 0, 4, 8, 10, 14, 18, 20, 24, 28, 30, 34, 38 };
  memcpy(connerIndex, c, sizeof(c));
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
    red[i]->setType(RED);

    green[i] = new Model(horse);
    green[i]->setColorTint(0, 0.8, 0);    // GREEN
    green[i]->setPosition(greenStartPos[i]);
    green[i]->setType(GREEN);

    blue[i] = new Model(horse);
    blue[i]->setColorTint(0, 0, 0.8);    // BLUE
    blue[i]->setPosition(blueStartPos[i]);
    blue[i]->setType(BLUE);

    yellow[i] = new Model(horse);
    yellow[i]->setColorTint(0.8, 0.8, 0);    // YELLOW
    yellow[i]->setPosition(yellowStartPos[i]);
    yellow[i]->setType(YELLOW);
  }

  red[1]->setPosition(Vector3(-20, 0, -4));
  blue[1]->setPosition(Vector3(4, 0, -20));
  green[1]->setPosition(Vector3(20, 0, 4));
  yellow[1]->setPosition(Vector3(-4, 0, 20));
}

void Game::draw()
{
  // Save current matrix state
  glPushMatrix();

  glDisable(GL_LIGHTING);
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
  glEnable(GL_LIGHTING);

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

  //glDisable(GL_COLOR_MATERIAL);

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

  //glEnable(GL_COLOR_MATERIAL);

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

int Game::nextPosition( int pIndexCurPos, int pDiceNumber, Model* pModel )
{
  int indexFirstPos = pModel->getIndexFirstPos();

  int indexNextPos = pIndexCurPos + pDiceNumber;
  if (indexNextPos >= 40)
    indexNextPos -= 40;

  // checking for GREEN, BLUE & YELLOW
  if (indexFirstPos > pIndexCurPos && indexFirstPos <= indexNextPos)
    return -1;
  // checking for RED
  if (indexFirstPos == 0 && indexNextPos < pDiceNumber)
    return -1;

  return indexNextPos;
}

bool Game::checkAllModelIdle()
{
  for (int i = 0; i < 4; i++)
  {
    if (red[i]->getState() != IDLE)
      return false;
    if (green[i]->getState() != IDLE)
      return false;
    if (blue[i]->getState() != IDLE)
      return false;
    if (yellow[i]->getState() != IDLE)
      return false;
  }
  return true;
}

int Game::getModelPositionIndex( Vector3 pPos )
{
  for (int i = 0; i < 40; i++)
    if (pPos == road[i])
      return i;

  return -1;
}

Model* Game::getModelByName( int name )
{
  int delta = name - RED_1;
  if (delta < 0)
    return NULL;

  if (delta < 4)
    return red[delta];
  if (delta < 8)
    return green[delta-4];
  if (delta < 12)
    return blue[delta-8];
  if (delta < 16)
    return yellow[delta-12];

  return NULL;
}

void Game::demoMove(int name)
{
  if (!mDiceIsThrown)
    return;

  Model* mod = getModelByName(name);
  if (mod != NULL && mod->getType() == playerTurn && checkAllModelIdle())
  {
    mDiceIsThrown = false;
    switch (playerTurn)
    {
    case RED:
      //cout << "Red Turn" << endl;
      playerTurn = BLUE;
      break;
    case BLUE:
      //cout << "Blue Turn" << endl;
      playerTurn = GREEN;
      break;
    case GREEN:
      //cout << "Green Turn" << endl;
      playerTurn = YELLOW;
      break;
    case YELLOW:
      //cout << "Yellow Turn" << endl;
      playerTurn = RED;
      break;
    default:
      break;
    }

    vector<Vector3> target;

    int index = getModelPositionIndex(mod->getPosition());

    // From init position
    if (index == -1)
    {
      target.push_back(road[mod->getIndexFirstPos()]);
      mod->jumpTo(mod->getPosition(), target, JUMP_ATTACK);
    }
    else
    {
      int tmp = nextPosition(index, mDiceNumber, mod);

      //cout << "Dice: " << mDiceNumber << " Temp: " << tmp << endl;

      if (tmp < 0 && (index == mod->getIndexFirstPos()-1 || index == mod->getIndexFirstPos()-1+40))
      {
        cout << "abc"; 
        return;
      } 
      else if (tmp < 0)
        return;

      // Move with corner
      if (tmp > index)
      {
        for (int i = 0; i < 12; i++)
          if (index < connerIndex[i] && connerIndex[i] < tmp )
            target.push_back(road[connerIndex[i]]);
      }
      else // corner at index 38 & 0
      {
        if (index < connerIndex[11])
          target.push_back(road[connerIndex[11]]);
        if (tmp > connerIndex[0])
          target.push_back(road[connerIndex[0]]);
      }
      target.push_back(road[tmp]);

      mod->jumpTo(road[index], target, JUMP_MOVE);
      index = tmp;
    }
  }
}

void Game::throwDice()
{
  mDiceNumber = rand() % 6 + 1;
  mDiceIsThrown = true;
  //cout << "Dice Number: " << mDiceNumber << endl;
}

Game::~Game(void)
{
}
