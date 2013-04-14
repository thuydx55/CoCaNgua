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
  //memcpy(mHome, stable, sizeof(stable));
  for (int i = 0; i < 16; i++)
  {
    mHome[i] = Field(stable[i]);
  }

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

  //memcpy(mFields, r, sizeof(r));
  for (int i = 0; i < 40; i++)
  {
    mFields[i] = Field(r[i]);
  }

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
    mPieces[i] = new Model(horse);
    mPieces[i]->setColorTint(0.8, 0, 0);         // RED
    mPieces[i]->setPosition(mStartPos[i]);
    mPieces[i]->setType(TURN_RED);

    mPieces[4+i] = new Model(horse);
    mPieces[4+i]->setColorTint(0, 0, 0.8);        // BLUE
    mPieces[4+i]->setPosition(mStartPos[4+i]);
    mPieces[4+i]->setType(TURN_BLUE);

    mPieces[8+i] = new Model(horse);
    mPieces[8+i]->setColorTint(0, 0.8, 0);        // GREEN
    mPieces[8+i]->setPosition(mStartPos[8+i]);
    mPieces[8+i]->setType(TURN_GREEN);

    mPieces[12+i] = new Model(horse);
    mPieces[12+i]->setColorTint(0.8, 0.8, 0);     // YELLOW
    mPieces[12+i]->setPosition(mStartPos[12+i]);
    mPieces[12+i]->setType(TURN_YELLOW);
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
    mPieces[i]->drawModel();

    glLoadName(PIECE_BLUE_1 + i);
    mPieces[4+i]->drawModel();

    glLoadName(PIECE_GREEN_1 + i);
    mPieces[8+i]->drawModel();

    glLoadName(PIECE_YELLOW_1 + i);
    mPieces[12+i]->drawModel();
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

void Game::nextTurn()
{
  mDiceIsThrown = false;

  for (int i = 0; i < 4; i++)
  {
    mPieces[playerTurn*4 + i]->highlight(false);
  }

  if (mDiceNumber != 6)
  {
    switch (playerTurn)
    {
    case TURN_RED:
      playerTurn = TURN_BLUE;
      break;
    case TURN_BLUE:
      playerTurn = TURN_GREEN;
      break;
    case TURN_GREEN:
      playerTurn = TURN_YELLOW;
      break;
    case TURN_YELLOW:
      playerTurn = TURN_RED;
      break;
    default:
      break;
    } 
  }
}

bool Game::checkAllModelIdle()
{
  for (int i = 0; i < 16; i++)
  {
    if (mPieces[i]->getState() != MODEL_IDLE)
      return false;
  }
  return true;
}

int Game::getModelPositionIndex( Vector3 pPos , Field pArray[], int pSize)
{
  for (int i = 0; i < pSize; i++)
    if (pPos == pArray[i].position)
      return i;

  return -1;
}

Model* Game::getModelByName( int name )
{
  int delta = name - PIECE_RED_1;
  if (delta < 0 || delta > 15)
    return NULL;

  return mPieces[delta];
}

void Game::demoMove(int name)
{
  if (!mDiceIsThrown)
    return;

  Model* mod = getModelByName(name);
  if (mod != NULL && mod->getType() == playerTurn && checkAllModelIdle())
  {
    vector<Vector3> target;

    int k = (name - PIECE_RED_1) % 4;

    if (mPredictMoveState[k] == MOVE_ILLEGAL)
      return;
    else if (mPredictMoveState[k] == MOVE_START 
      || mPredictMoveState[k] == MOVE_ATTACK
      || mPredictMoveState[k] == MOVE_STABLE)
    {
      target.push_back(mPredictPosition[k]);
      mod->jumpTo(target, mPredictMoveState[k]);
      nextTurn();
    }
    else if (mPredictMoveState[k] == MOVE_NORMAL)
    {
      int index = getModelPositionIndex(mod->getPosition(), mFields, 40);
      int tmp = getModelPositionIndex(mPredictPosition[k], mFields, 40);

      // Move with corner
      if (tmp > index)
      {
        for (int i = 0; i < 12; i++)
          if (index < connerIndex[i] && connerIndex[i] < tmp )
            target.push_back(mFields[connerIndex[i]].position);
      }
      else // corner at index 38 & 0
      {
        if (index < connerIndex[11])
          target.push_back(mFields[connerIndex[11]].position);
        if (tmp > connerIndex[0])
          target.push_back(mFields[connerIndex[0]].position);
      }
      target.push_back(mFields[tmp].position);

      mod->jumpTo(target, MOVE_NORMAL);
      nextTurn();
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
    int indexFirstPos = mPieces[playerTurn*4+i]->getIndexFirstPos();
    int indexCurRoad = getModelPositionIndex(mPieces[playerTurn*4+i]->getPosition(), mFields, 40);
    if (indexCurRoad == -1)
    {
      int indexCurStable = getModelPositionIndex(mPieces[playerTurn*4+i]->getPosition(), mHome, 16);
      if (indexCurStable != -1)
      {
        if (mDiceNumber <= 3 - indexCurStable%4)
        {
          mPredictPosition[i] = mHome[indexCurStable + mDiceNumber].position;
          mPredictMoveState[i] = MOVE_STABLE;
        }
        continue;
      }
      if (mDiceNumber == 6)
      {
        predictIndexPos[i] = indexFirstPos;
        mPredictMoveState[i] = MOVE_START;
      }
      continue;
    }

    int indexNext = indexCurRoad + mDiceNumber;
    if (indexNext >= 40)
      indexNext -= 40;

    // check reaching finish
    if ((indexFirstPos > indexCurRoad && indexFirstPos <= indexNext)
      || (indexFirstPos == 0 && indexNext < mDiceNumber))
    {
      // From road to Stable
      if ((indexCurRoad == indexFirstPos-1 || indexCurRoad == indexFirstPos-1+40) 
        && mDiceNumber <= 4)
      {
        mPredictMoveState[i] = MOVE_STABLE;
        mPredictPosition[i] = mHome[playerTurn*4 + mDiceNumber-1].position;
      }
      continue;
    }

    predictIndexPos[i] = indexNext;
    mPredictMoveState[i] = MOVE_NORMAL;
  }

  for (int i = 0; i < 4; i++)
  {
    if (predictIndexPos[i] == -1)
      continue;
    mPredictPosition[i] = mFields[predictIndexPos[i]].position;
  }

  cout << "Player: " << playerTurn << endl;
  cout << "Dice Number: " << mDiceNumber << endl;
  for (int i = 0; i < 4; i++)
  {
    cout << mPredictMoveState[i] << endl;
  }

  bool allMoveIllegal = true;
  for (int i = 0; i < 4; i++)
  {
    if (mPredictMoveState[i] != MOVE_ILLEGAL)
    {
      mPieces[playerTurn*4+i]->highlight(true);
      allMoveIllegal = false;
    }
  }

  if (allMoveIllegal)
    nextTurn();
}

Game::~Game(void)
{
}
