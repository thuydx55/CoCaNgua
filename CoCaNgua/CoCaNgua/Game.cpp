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

  playerTurn = TURN_RED;

  Vector3 start[] = {Vector3(-16, 0, -16),
                     Vector3(-16, 0, -20),
                     Vector3(-20, 0, -20),
                     Vector3(-20, 0, -16),      // RED
  
                     Vector3(16, 0, -16),
                     Vector3(16, 0, -20),
                     Vector3(20, 0, -20),
                     Vector3(20, 0, -16),       // BLUE

                     Vector3(16, 0, 16),
                     Vector3(16, 0, 20),
                     Vector3(20, 0, 20),
                     Vector3(20, 0, 16),        // GREEN

                     Vector3(-16, 0, 16),
                     Vector3(-16, 0, 20),
                     Vector3(-20, 0, 20),
                     Vector3(-20, 0, 16),       // YELLOW
  };
  memcpy(mStartPos, start, sizeof(start));

  Vector3 stable[] = {Vector3(-16, 0, 0),
                      Vector3(-12, 0, 0),
                      Vector3(-8, 0, 0),
                      Vector3(-4, 0, 0),        // RED

                      Vector3(0, 0, -16),
                      Vector3(0, 0, -12),
                      Vector3(0, 0, -8),  
                      Vector3(0, 0, -4),        // BLUE

                      Vector3(16, 0, 0),
                      Vector3(12, 0, 0),
                      Vector3(8, 0, 0),
                      Vector3(4, 0, 0),         // GREEN

                      Vector3(0, 0, 16),
                      Vector3(0, 0, 12),
                      Vector3(0, 0, 8),
                      Vector3(0, 0, 4)          // YELLOW
  };
  memcpy(mStable, stable, sizeof(stable));

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

  memcpy(mRoad, r, sizeof(r));

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
  mDice         = new Model();

  mBoard->loadModel("Models/board.obj");
  mBoard->setAnchorPoint(Vector3(0, 0.5, 0));

  mDice->loadModel("Models/dice.obj");

  horse->loadModel("Models/knight.obj");
  horse->setAnchorPoint(Vector3(0, -0.5, 0));

  for (int i = 0; i < 4; i++)
  {
    mPiece[i] = new Model(horse);
    mPiece[i]->setColorTint(0.8, 0, 0);         // RED
    mPiece[i]->setPosition(mStartPos[i]);
    mPiece[i]->setType(TURN_RED);

    mPiece[4+i] = new Model(horse);
    mPiece[4+i]->setColorTint(0, 0, 0.8);        // BLUE
    mPiece[4+i]->setPosition(mStartPos[4+i]);
    mPiece[4+i]->setType(TURN_BLUE);

    mPiece[8+i] = new Model(horse);
    mPiece[8+i]->setColorTint(0, 0.8, 0);        // GREEN
    mPiece[8+i]->setPosition(mStartPos[8+i]);
    mPiece[8+i]->setType(TURN_GREEN);

    mPiece[12+i] = new Model(horse);
    mPiece[12+i]->setColorTint(0.8, 0.8, 0);     // YELLOW
    mPiece[12+i]->setPosition(mStartPos[12+i]);
    mPiece[12+i]->setType(TURN_YELLOW);
  }

  //red[1]->setPosition(Vector3(-20, 0, -4));
  //blue[1]->setPosition(Vector3(4, 0, -20));
  //green[1]->setPosition(Vector3(20, 0, 4));
  //yellow[1]->setPosition(Vector3(-4, 0, 20));
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
    glLoadName(PIECE_RED_1 + i);
    mPiece[i]->drawModel();

    glLoadName(PIECE_BLUE_1 + i);
    mPiece[4+i]->drawModel();

    glLoadName(PIECE_GREEN_1 + i);
    mPiece[8+i]->drawModel();

    glLoadName(PIECE_YELLOW_1 + i);
    mPiece[12+i]->drawModel();
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
  for (int i = 0; i < 16; i++)
  {
    if (mPiece[i]->getState() != MODEL_IDLE)
      return false;
  }
  return true;
}

int Game::getModelPositionIndex( Vector3 pPos )
{
  for (int i = 0; i < 40; i++)
    if (pPos == mRoad[i])
      return i;

  return -1;
}

Model* Game::getModelByName( int name )
{
  int delta = name - PIECE_RED_1;
  if (delta < 0 || delta > 15)
    return NULL;

  return mPiece[delta];
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
    case TURN_RED:
      cout << "Red Turn" << endl;
      playerTurn = TURN_BLUE;
      break;
    case TURN_BLUE:
      cout << "Blue Turn" << endl;
      playerTurn = TURN_GREEN;
      break;
    case TURN_GREEN:
      cout << "Green Turn" << endl;
      playerTurn = TURN_YELLOW;
      break;
    case TURN_YELLOW:
      cout << "Yellow Turn" << endl;
      playerTurn = TURN_RED;
      break;
    default:
      break;
    }

    vector<Vector3> target;

    int index = getModelPositionIndex(mod->getPosition());

    // From init position
    if (index == -1)
    {
      target.push_back(mRoad[mod->getIndexFirstPos()]);
      mod->jumpTo(mod->getPosition(), target, MOVE_ATTACK);
    }
    else
    {
      int tmp = nextPosition(index, mDiceNumber, mod);

      cout << "Dice: " << mDiceNumber << " Temp: " << tmp << endl;

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
            target.push_back(mRoad[connerIndex[i]]);
      }
      else // corner at index 38 & 0
      {
        if (index < connerIndex[11])
          target.push_back(mRoad[connerIndex[11]]);
        if (tmp > connerIndex[0])
          target.push_back(mRoad[connerIndex[0]]);
      }
      target.push_back(mRoad[tmp]);

      mod->jumpTo(mRoad[index], target, MOVE_NORMAL);
      index = tmp;
    }
  }
}

void Game::throwDice()
{
  mDiceNumber = rand() % 6 + 1;
  mDiceIsThrown = true;

  mPredictPosition[0] = mPredictPosition[1] = mPredictPosition[2] = mPredictPosition[3] = Vector3();
  mPredictMoveState[0] = mPredictMoveState[1] = mPredictMoveState[2] = mPredictMoveState[3] = MOVE_ILLEGAL;
  int predictIndexPos[4] = {-1, -1, -1, -1};

  for (int i = 0; i < 4; i++)
  {
    int indexFirstPos = mPiece[playerTurn*4+i]->getIndexFirstPos();
    int indexCur = getModelPositionIndex(mPiece[playerTurn*4+i]->getPosition());
    if (indexCur == -1 && mDiceNumber == 6)
    {
      predictIndexPos[i] = indexFirstPos;
      continue;
    }

    int indexNext = indexCur + mDiceNumber;
    if (indexNext >= 40)
      indexNext -= 40;

    // checking for GREEN, BLUE & YELLOW
    if (indexFirstPos > indexCur && indexFirstPos <= indexNext)
      continue;
    // checking for RED
    if (indexFirstPos == 0 && indexNext < mDiceNumber)
      continue;

    predictIndexPos[i] = indexNext;
  }

  for (int i = 0; i < 4; i++)
  {
    if (predictIndexPos[i] == -1)
      continue;
    mPredictPosition[i] = mRoad[predictIndexPos[i]];
  }

  //cout << "Dice Number: " << mDiceNumber << endl;
}

Game::~Game(void)
{
}
