#include "GameScene.h"

bool allMoveIllegal = true;
bool noPieceInTheGame = true;

GameScene::GameScene(void)
{
  srand(time(NULL));

  for (int i = 0; i < 4; i++)
    mEnablePiece[i] = true;

  mDieIsThrown = false;
  mDieIsDrawn = true;
  Light::inst().mDiffuseOffset = 0.5;
  Light::inst().updateLight();
  mFullHome = false;

  lightPosition[0] = 0;
  lightPosition[1] = 50;
  lightPosition[2] = 0;
  lightPosition[3] = 1;
  lightAngle = 0.0;
  lightHeight = 20;

  font = GLUT_BITMAP_8_BY_13;

  mPlayerTurn = TURN_RED;
  mTries = 0;

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

  Vector3 home[] = {Vector3(-16, 0, 0),
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
    mHome[i] = Field(home[i]);
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
  memcpy(mConnerIndex, c, sizeof(c));

  Light::inst().setPosition(GameScene::inst().lightPosition[0], GameScene::inst().lightPosition[1], 
    GameScene::inst().lightPosition[2], GameScene::inst().lightPosition[3]);
  Light::inst().updateLight();
}

GameScene& GameScene::inst()
{
  static GameScene Instance;
  return Instance;
}

void GameScene::initModel()
{
  mBoard       = new Board();
  Piece* horse = new Piece();
  mDice        = new Die();

  mBoard->loadModel("Models/board.obj");
  mBoard->setAnchorPoint(Vector3(0, 0.5, 0));

  mDice->loadModel("Models/dice.obj");

  horse->loadModel("Models/knight.obj");
  horse->setAnchorPoint(Vector3(0, -0.5, 0));

  for (int i = 0; i < 4; i++)
  {
    mPieces[i] = new Piece(horse);
    mPieces[i]->setColorTint(0.8, 0, 0);         // RED
    mPieces[i]->setPosition(mStartPos[i]);
    mPieces[i]->setInitPosition(mStartPos[i]);
    mPieces[i]->setType(TURN_RED);

    mPieces[4+i] = new Piece(horse);
    mPieces[4+i]->setColorTint(0, 0, 0.8);        // BLUE
    mPieces[4+i]->setPosition(mStartPos[4+i]);
    mPieces[4+i]->setInitPosition(mStartPos[4+i]);
    mPieces[4+i]->setType(TURN_BLUE);

    mPieces[8+i] = new Piece(horse);
    mPieces[8+i]->setColorTint(0, 0.8, 0);        // GREEN
    mPieces[8+i]->setPosition(mStartPos[8+i]);
    mPieces[8+i]->setInitPosition(mStartPos[8+i]);
    mPieces[8+i]->setType(TURN_GREEN);

    mPieces[12+i] = new Piece(horse);
    mPieces[12+i]->setColorTint(0.8, 0.8, 0);     // YELLOW
    mPieces[12+i]->setPosition(mStartPos[12+i]);
    mPieces[12+i]->setInitPosition(mStartPos[12+i]);
    mPieces[12+i]->setType(TURN_YELLOW);
  }

  mPieces[1]->setPosition(Vector3(0, 5, 0));
  /*mPieces[5]->setPosition(mFields[0].position);
  mFields[0].piece = mPieces[5];
  mFields[10].piece = mPieces[1];*/
  //blue[1]->setPosition(Vector3(4, 0, -20));
  //green[1]->setPosition(Vector3(20, 0, 4));
  //yellow[1]->setPosition(Vector3(-4, 0, 20));
}

void GameScene::drawSence()
{
  // Save current matrix state
  glPushMatrix();

#if SHOW_GRID
  glDisable(GL_LIGHTING);
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
    if (mEnablePiece[0])
    {
      glLoadName(PIECE_RED_1 + i);
      mPieces[i]->drawModel(); 
    }

    if (mEnablePiece[1])
    {
      glLoadName(PIECE_BLUE_1 + i);
      mPieces[4+i]->drawModel(); 
    }

    if (mEnablePiece[2])
    {
      glLoadName(PIECE_GREEN_1 + i);
      mPieces[8+i]->drawModel(); 
    }

    if (mEnablePiece[3])
    {
      glLoadName(PIECE_YELLOW_1 + i);
      mPieces[12+i]->drawModel(); 
    }
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

void GameScene::drawDie()
{
  if (mDieIsDrawn)
  {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
      glLoadIdentity();
      glOrtho(-10*Graphic::inst().screenWidth/Graphic::inst().screenHeight,
        10*Graphic::inst().screenWidth/Graphic::inst().screenHeight,
        -10, 10, -10.0, 10.0);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      {
        glLoadIdentity();
        glDisable(GL_CULL_FACE);

        glClear(GL_DEPTH_BUFFER_BIT);

        mDice->drawModel();
      }
      glPopMatrix();

      // Making sure we can render 3d again
      glMatrixMode(GL_PROJECTION);
    }

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW); 
  }
}


void GameScene::loop()
{
  update();

  drawSence();
  drawDie();

  // Winnnnnnnnnnnnnnnnn
  if (mFullHome && checkAllModelIdle())
  {
    cout << "WINNER: " << mWinner << endl;
    mFullHome = false;
  }

}

void GameScene::nextTurn()
{
  mDieIsThrown = false;
  mDieIsDrawn = true;
  Light::inst().mDiffuseOffset = 0.5;
  Light::inst().updateLight();

  mDice->setState(DIE_WAITING);

  for (int i = 0; i < 4; i++)
  {
    mPieces[mPlayerTurn*4 + i]->highlight(false);
  }

  if (noPieceInTheGame)
  {
    mTries ++;
    if (mTries <= 2)
      return;
    mTries = 0;
  }

  if (mDieNumber != 6)
  {
    int next = (int)mPlayerTurn + 1 >= 4 ? 0 : (int)mPlayerTurn + 1;
    while (!mEnablePiece[next])
    {
      next++;
      if (next >= 4) next = 0;
    }
    mPlayerTurn = (Turn)next;
  }
}

bool GameScene::checkAllModelIdle()
{
  for (int i = 0; i < 16; i++)
  {
    if (mPieces[i]->getState() != MODEL_IDLE)
      return false;
  }
  return true;
}

int GameScene::getModelPositionIndex( Vector3 pPos , Field pArray[], int pSize)
{
  for (int i = 0; i < pSize; i++)
    if (pPos == pArray[i].position)
      return i;

  return -1;
}

Piece* GameScene::getModelByName( int name )
{
  int delta = name - PIECE_RED_1;
  if (delta < 0 || delta > 15)
    return NULL;

  return mPieces[delta];
}

void GameScene::movePiece(int name)
{
  if (!mDieIsThrown)
    return;

  Piece* mod = getModelByName(name);
  Turn playerTurn = mPlayerTurn;

  if (mod != NULL && mod->getType() == mPlayerTurn && checkAllModelIdle())
  {
    vector<Vector3> target;

    int k = (name - PIECE_RED_1) % 4;

    if (mPredictMoveState[k] == MOVE_ILLEGAL)
      return;
    else if (mPredictMoveState[k] == MOVE_START 
      || mPredictMoveState[k] == MOVE_ATTACK
      || mPredictMoveState[k] == MOVE_HOME_INSIDE
      || mPredictMoveState[k] == MOVE_HOME_OUTSIDE
      || mPredictMoveState[k] == MOVE_START_ATTACK)
    {
      target.push_back(mPredictPosition[k]);

      if (mPredictMoveState[k] == MOVE_ATTACK)
      {
        int index = getModelPositionIndex(mod->getPosition(), mFields, 40);
        int tmp = getModelPositionIndex(mPredictPosition[k], mFields, 40);

        mFields[tmp].piece->setArea(AREA_OUT);
        mFields[tmp].piece->setPosition(mFields[tmp].piece->getInitPosition());

        mFields[index].piece = NULL;
        mFields[tmp].piece = mod;
      }

      if (mPredictMoveState[k] == MOVE_START_ATTACK)
      {
        int tmp = getModelPositionIndex(mPredictPosition[k], mFields, 40);

        mFields[tmp].piece->setArea(AREA_OUT);
        mFields[tmp].piece->setPosition(mFields[tmp].piece->getInitPosition());

        mFields[tmp].piece = mod;
        mFields[tmp].piece->setArea(AREA_GAME);
      }

      if (mPredictMoveState[k] == MOVE_START)
      {
        int tmp = getModelPositionIndex(mPredictPosition[k], mFields, 40);

        mFields[tmp].piece = mod;
        mFields[tmp].piece->setArea(AREA_GAME);
      }

      if (mPredictMoveState[k] == MOVE_HOME_INSIDE)
      {
        int index = getModelPositionIndex(mod->getPosition(), mHome, 16);
        int tmp = getModelPositionIndex(mPredictPosition[k], mHome, 16);

        mHome[index].piece = NULL;
        mHome[tmp].piece = mod;
      }

      if (mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
      {
        int index = getModelPositionIndex(mod->getPosition(), mFields, 40);
        int tmp = getModelPositionIndex(mPredictPosition[k], mHome, 16);

        mFields[index].piece = NULL;
        mHome[tmp].piece = mod;
        mHome[tmp].piece->setArea(AREA_HOME);
      }

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
          if (index < mConnerIndex[i] && mConnerIndex[i] < tmp )
            target.push_back(mFields[mConnerIndex[i]].position);
      }
      else // corner at index 38 & 0
      {
        if (index < mConnerIndex[11])
          target.push_back(mFields[mConnerIndex[11]].position);
        if (tmp > mConnerIndex[0])
          target.push_back(mFields[mConnerIndex[0]].position);
      }
      target.push_back(mFields[tmp].position);

      mFields[index].piece = NULL;
      mFields[tmp].piece = mod;

      mod->jumpTo(target, MOVE_NORMAL);
      nextTurn();
    }
  }

  /*---------------- FIND THE WINNER ^^ -------------------*/
  mFullHome = true;
  for (int i = playerTurn*4; i < playerTurn*4+4; i++)
  {
    if (mHome[i].piece == NULL)
    {
      mFullHome = false;
      break;
    }
  }

  if (mFullHome)
  {
    mWinner = playerTurn;
  }
}

void GameScene::rollDice(int number)
{
  if (mDieIsThrown)
    return;
  //mDiceNumber = rand() % 6 + 1;
  mDieIsThrown = true;
  mustBeStart = false;
  allMoveIllegal = true;
  noPieceInTheGame = true;
  mDieNumber = number;

  mPredictPosition[0] = mPredictPosition[1] = mPredictPosition[2] = mPredictPosition[3] = Vector3();
  mPredictMoveState[0] = mPredictMoveState[1] = mPredictMoveState[2] = mPredictMoveState[3] = MOVE_ILLEGAL;
  int predictIndexPos[4] = {-1, -1, -1, -1};

  for (int i = 0; i < 4; i++)
  {
    int indexFirstPos = mPieces[mPlayerTurn*4+i]->getIndexFirstPos();
    int indexCurRoad = getModelPositionIndex(mPieces[mPlayerTurn*4+i]->getPosition(), mFields, 40);
    
    // Piece not on the road
    if (indexCurRoad == -1)
    {
      int indexCurHome = getModelPositionIndex(mPieces[mPlayerTurn*4+i]->getPosition(), mHome, 16);

      // Piece in the home
      if (indexCurHome != -1)
      {
        if (mDieNumber <= 3 - indexCurHome%4)
        {
          bool blocked = false;
          // Checking if no piece on the way to target field
          for (int j = indexCurHome+1; j <= indexCurHome + mDieNumber; j++)
          {
            if (mHome[j].piece != NULL)
            {
              // There is
              blocked = true;
              break;
            }
          }

          // Piece move if the way is cleared
          if (!blocked)
          {
            mPredictPosition[i] = mHome[indexCurHome + mDieNumber].position;
            mPredictMoveState[i] = MOVE_HOME_INSIDE;
          }

          // Dice Number is too big, piece can't move
          continue; 
        }
      }

      /*---------------- DICE 6 -------------------*/
      // Piece move to start field
      if (mDieNumber == 6 && mPieces[mPlayerTurn*4+i]->getArea() == AREA_OUT)
      {
        mustBeStart = true;
        // Other piece on start field already
        if (mFields[indexFirstPos].piece != NULL)
        {
          // Other piece is the same
          if (mFields[indexFirstPos].piece->getType() == mPlayerTurn)
          {
            mustBeStart = false;
            continue;
          }
          // Start && Attack
          else
          {
            predictIndexPos[i] = indexFirstPos;
            mPredictMoveState[i] = MOVE_START_ATTACK;
          }
        }
        // Start field is empty
        else
        {
          predictIndexPos[i] = indexFirstPos;
          mPredictMoveState[i] = MOVE_START;
        }
      }
      // Piece is on Init position, die number < 6, can't start
      continue;
    }

    // Piece is on the road
    int indexNext = indexCurRoad + mDieNumber;
    if (indexNext >= 40)
      indexNext -= 40;

    /*---------------- GO HOME FROM OUTSIDE -------------------*/
    // check reaching finish
    if ((indexFirstPos > indexCurRoad && indexFirstPos <= indexNext)
      || (indexFirstPos == 0 && indexNext < mDieNumber))
    {
      // From road to Home
      if ((indexCurRoad == indexFirstPos-1 || indexCurRoad == indexFirstPos-1+40) 
        && mDieNumber <= 4)
      {
        bool blocked = false;
        // Checking if no piece on the way to target field
        for (int j = mPlayerTurn*4; j < mPlayerTurn*4 + mDieNumber; j++)
        {
          if (mHome[j].piece != NULL)
          {
            // There is
            blocked = true;
            break;
          }
        }

        // Piece move if the way is cleared
        if (!blocked)
        {
          mPredictPosition[i] = mHome[mPlayerTurn*4 + mDieNumber-1].position;
          mPredictMoveState[i] = MOVE_HOME_OUTSIDE; 
        }
      }
      // Dice > 4, can not move
      continue;
    }

    /*---------------- ATTACK && NORMAL -------------------*/
    // Checking if target field is not empty
    if (mFields[indexNext].piece != NULL)
    {
      // Target piece is the same
      if (mFields[indexNext].piece->getType() == mPlayerTurn)
      {
        // There is
        continue;
      }
      // Attack
      else
      {
        predictIndexPos[i] = indexNext;
        mPredictMoveState[i] = MOVE_ATTACK;
      }
    }
    // Target field is empty, normal move
    else
    {
      predictIndexPos[i] = indexNext;
      mPredictMoveState[i] = MOVE_NORMAL;
    }
  }

  bool startFieldMustMove = false;
  int startPieceID;
  int indexFirstPos = mPieces[mPlayerTurn*4]->getIndexFirstPos();

  for (int i = 0; i < 4; i++)
  {
    // Mapping index to position
    if (predictIndexPos[i] == -1)
      continue;
    mPredictPosition[i] = mFields[predictIndexPos[i]].position;

    // Must be start
    if (mustBeStart && mPredictMoveState[i] != MOVE_START && mPredictMoveState[i] != MOVE_START_ATTACK)
    {
      mPredictMoveState[i] = MOVE_ILLEGAL;
    }

    // Checking if start field has piece
    if (mFields[indexFirstPos].piece != NULL && !startFieldMustMove)
    {
      int indexCurField = getModelPositionIndex(mPieces[mPlayerTurn*4+i]->getPosition(), mFields, 40);
      if (indexCurField == indexFirstPos && mPredictMoveState[i] != MOVE_ILLEGAL)
      {
        startFieldMustMove = true;
        startPieceID = i;
      }
    }
  }

  cout << "Player: " << mPlayerTurn << endl;
  cout << "Dice Number: " << mDieNumber << endl;
  for (int i = 0; i < 4; i++)
  {
    cout << mPredictMoveState[i] << endl;
  }

  // Checking if pieces can move
  for (int i = 0; i < 4; i++)
  {
    // Start field must move first
    if (startFieldMustMove)
    {
      if (mPredictMoveState[i] != MOVE_ILLEGAL && i != startPieceID)
      {
        mPredictMoveState[i] = MOVE_ILLEGAL;
      }
    }

    // Checking if no piece in the game
    if (mPieces[mPlayerTurn*4+i]->getArea() == AREA_GAME)
    {
      noPieceInTheGame = false;
    }

    // Checking if all move are illegal
    if (mPredictMoveState[i] != MOVE_ILLEGAL)
    {
      mPieces[mPlayerTurn*4+i]->highlight(true);
      allMoveIllegal = false;
    }
  }

  // No piece can move?
  if (allMoveIllegal)
  {
    nextTurn();
  }
}

void GameScene::update()
{
  if (mDieIsDrawn && mDice->getState() == DIE_STOP)
  {
    mDieIsDrawn = false;
    this->rollDice(mDieNumber);
    Light::inst().mDiffuseOffset = 0.0;
    Light::inst().updateLight();
  }
}

void GameScene::setDisablePiece( int index )
{
  mEnablePiece[index] = false;
  if (mPlayerTurn == index)
  {
    for (int i = 0; i < 4; i++)
    {
      if (!mEnablePiece[i])
      {
        mPlayerTurn = (Turn)(i+1 > 4 ? 0 : i+1);
        break;
      }
    } 
  }
}

GameScene::~GameScene(void)
{
}

bool GameScene::processMouseBegan( int x, int y )
{
  if (mDieIsDrawn)
  {
    if (mDice->getState() == DIE_WAITING)
      mDieNumber = GameScene::inst().mDice->rollDie();
    return true;
  }

  return false;
}
