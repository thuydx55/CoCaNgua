#include "GameScene.h"

bool allMoveIllegal = true;
bool noPieceInTheGame = true;
int selectedIndex = -1;

GameScene::GameScene(void)
{
  srand(time(NULL));

  for (int i = 0; i < 4; i++)
    mEnablePiece[i] = true;

  mDieIsThrown = false;
  mDieIsDrawn = true;
  mFullHome = false;
  mPieceIsMoving = false;

  mAutoCam = true;
  
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
  float startDirection[] = { -90, -90, -90, -90,  // RED
                             180, 180, 180, 180,  // BLUE
                              90,  90,  90,  90,  // GREEN
                               0,   0,   0,   0}; // YELLOW
  for (int i = 0; i < 16; i++)
  {
    mStartPos[i].position = start[i];
    mStartPos[i].direction = startDirection[i];
  }
  //memcpy(mStartPos, start, sizeof(start));

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
  float homeDirection[] = {  0,   0,   0,   0,  // RED
                           -90, -90, -90, -90,  // BLUE
                           180, 180, 180, 180,  // GREEN
                            90,  90,  90,  90   // YELLOW
  };
  //memcpy(mHome, stable, sizeof(stable));
  for (int i = 0; i < 16; i++)
  {
    mHome[i] = Field(home[i], homeDirection[i]);
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

  Vector3 road[] = { Vector3(-20, 0, -4),      // RED START

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
  float roadDiretion[] = {   0,   0,   0,   0,
                            90,  90,  90,  90,
                             0,   0,
                           -90, -90, -90, -90,
                             0,   0,   0,   0,
                           -90, -90,
                           180, 180, 180, 180,
                           -90, -90, -90, -90,
                           180, 180,
                            90,  90,  90,  90, 
                           180, 180, 180, 180,
                            90,  90
  };

  //memcpy(mFields, r, sizeof(r));
  for (int i = 0; i < 40; i++)
  {
    road[i].y = 2;         
    mFields[i] = Field(road[i], roadDiretion[i]);
  }

  int c[] = { 0, 4, 8, 10, 14, 18, 20, 24, 28, 30, 34, 38 };
  memcpy(mConnerIndex, c, sizeof(c));
}

GameScene& GameScene::inst()
{
  static GameScene Instance;
  return Instance;
}

void GameScene::initBoard()
{
  mBoard       = new Board();
  mBoard->loadModel("Models/board.obj");
  mBoard->setAnchorPoint(Vector3(0, 0.5, 0));
}

void GameScene::initDie()
{
  mDice        = new Die();
  mDice->loadModel("Models/dice.obj");
}

void GameScene::initPiece()
{
  tmp = new Piece();
  
  tmp->loadModel("Models/knight.obj");
  tmp->setAnchorPoint(Vector3(0, -0.5, 0));

}

void GameScene::initAllPieces()
{
  for (int i = 0; i < 4; i++)
  {
    mPieces[i] = new Piece(tmp);
    mPieces[i]->setPosition(mStartPos[i].position);
    mPieces[i]->setInitPosition(mStartPos[i]);
    mPieces[i]->setType(TURN_RED);
    mPieces[i]->setAngle(-90);

    mPieces[4+i] = new Piece(tmp);
    mPieces[4+i]->setPosition(mStartPos[4+i].position);
    mPieces[4+i]->setInitPosition(mStartPos[4+i]);
    mPieces[4+i]->setType(TURN_BLUE);
    mPieces[4+i]->setAngle(180);

    mPieces[8+i] = new Piece(tmp);
    mPieces[8+i]->setPosition(mStartPos[8+i].position);
    mPieces[8+i]->setInitPosition(mStartPos[8+i]);
    mPieces[8+i]->setType(TURN_GREEN);
    mPieces[8+i]->setAngle(90);

    mPieces[12+i] = new Piece(tmp);
    mPieces[12+i]->setPosition(mStartPos[12+i].position);
    mPieces[12+i]->setInitPosition(mStartPos[12+i]);
    mPieces[12+i]->setType(TURN_YELLOW);
  }

  //delete tmp;
}

void GameScene::initRoad()
{
  Rock* tmp = new Rock();
  tmp->loadModel("Models/rock.obj");
  tmp->setAnchorPoint(Vector3(0, 0.5, 0));
  for (int i = 0; i < 40; i++)
  {
    mFieldModel[i] = new Rock(tmp);
    mFieldModel[i]->setPosition(mFields[i].position);
  }
}

void GameScene::drawSence()
{
  // Save current matrix state
  glPushMatrix();

#if DEBUG_CLICKING_RAY
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  Vector3 a = mViewRay.origin + 100*mViewRay.direction;

  glVertex3f(mViewRay.origin.x, mViewRay.origin.y, mViewRay.origin.z);
  glVertex3f(a.x, a.y, a.z);
  glEnd();
  glEnable(GL_LIGHTING);  
#endif // DEBUG_CLICKING_RAY


#if DEBUG_ORIGIN_AXES
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

  mBoard->drawModel();

  for (int i = 0; i < 40; i++)
    mFieldModel[i]->drawModel();

  for (int i = 0; i < 4; i++)
  {
    if (mEnablePiece[0])
      mPieces[i]->drawModel(); 

    if (mEnablePiece[1])
      mPieces[4+i]->drawModel(); 

    if (mEnablePiece[2])
      mPieces[8+i]->drawModel(); 

    if (mEnablePiece[3])
      mPieces[12+i]->drawModel(); 
  }

#if DEBUG_LIGHT_SOURCE
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
  float left  = -DIE_VIEW_SIZE*Graphic::inst().screenWidth/Graphic::inst().screenHeight;
  float right =  DIE_VIEW_SIZE*Graphic::inst().screenWidth/Graphic::inst().screenHeight;
  float bot   = -DIE_VIEW_SIZE;
  float top   =  DIE_VIEW_SIZE;
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  {
    glLoadIdentity();
    glOrtho(left, right, bot, top, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    {
      glLoadIdentity();
      glDisable(GL_CULL_FACE);

      glClear(GL_DEPTH_BUFFER_BIT);

      mDice->drawModel();

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glColor4f(0, 0, 0, 0.5);
      glDisable(GL_LIGHTING);
      glBegin(GL_QUADS);
        glVertex3f(left,  bot, -5);
        glVertex3f(right, bot, -5);
        glVertex3f(right, top, -5);
        glVertex3f(left,  top, -5);
      glEnd();
      glEnable(GL_LIGHTING);

      glDisable(GL_BLEND);
    }
    glPopMatrix();

    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
  }

  glPopMatrix();
  glMatrixMode(GL_MODELVIEW); 
}


void GameScene::loop()
{
  update();

  drawSence();
  if (mDieIsDrawn)
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
  }
  mTries = 0;

  if (mDieNumber != 6)
  {
    int next = (int)mPlayerTurn + 1 >= 4 ? 0 : (int)mPlayerTurn + 1;
    while (!mEnablePiece[next] || mIsGoHome[next])
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

void GameScene::movePiece(int arrayIndex)
{
  if (!mDieIsThrown)
    return;

  Piece* mod = mPieces[arrayIndex];
  Turn playerTurn = mPlayerTurn;

  if (mod != NULL && mod->getType() == mPlayerTurn && checkAllModelIdle())
  {
    vector<Field> target;

    int k = arrayIndex % 4;

    if (mPredictMoveState[k] == MOVE_ILLEGAL)
      return;
    if (mPredictMoveState[k] == MOVE_NORMAL || mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
    {
      /*if (mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
      {
      int index = getModelPositionIndex(mod->getPosition(), mFields, 40);

      mFields[index].piece = NULL;
      mPredictPosition[k]->piece = mod;
      mPredictPosition[k]->piece->setArea(AREA_HOME);
      }*/

      int index = getModelPositionIndex(mod->getPosition(), mFields, 40);
      int predictIndex;
      if (mPredictMoveState[k] == MOVE_NORMAL)
        predictIndex = getModelPositionIndex(mPredictPosition[k]->position, mFields, 40);
      else if (mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
      {
        predictIndex = mPlayerTurn*10-1;
        predictIndex = predictIndex == -1 ? 39 : predictIndex;
      }

      // Move with corner
      if (predictIndex > index)
      {
        for (int i = 0; i < 12; i++)
          if (index < mConnerIndex[i] && mConnerIndex[i] < predictIndex )
            target.push_back(mFields[mConnerIndex[i]]);
      }
      else // corner at index 38 & 0
      {
        if (index < mConnerIndex[11])
          target.push_back(mFields[mConnerIndex[11]]);
        if (predictIndex > mConnerIndex[0])
          target.push_back(mFields[mConnerIndex[0]]);
      }
      target.push_back(mFields[predictIndex]);

      for (int i = 0; i < target.size(); i++)
      {
        int predictIndex = getModelPositionIndex(target[i].position, mFields, 40);
        predictIndex = predictIndex + 1 == 40 ? 0 : predictIndex + 1;

        if (predictIndex == mPlayerTurn*10)
        {
          target[i].direction = mHome[4*mPlayerTurn].direction;
        }
      }

      mFields[index].piece = NULL;

      if (mPredictMoveState[k] == MOVE_NORMAL)
      {
        mFields[predictIndex].piece = mod;
      }
      else if (mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
      {
        target.push_back(*mPredictPosition[k]);

        mPredictPosition[k]->piece = mod;
        mPredictPosition[k]->piece->setArea(AREA_HOME);
      }

      mod->jumpTo(target, mPredictMoveState[k]);
      mPieceIsMoving = true;
      nextTurn();
    }
    else
    {
      target.push_back(*mPredictPosition[k]);
      int predictIndex = getModelPositionIndex(target[0].position, mFields, 40);
      if (predictIndex%10 == 9)
      {
        int div = (predictIndex+1)/10;
        div = div == 4 ? 0 : div;
        target[0].direction = mHome[4*div].direction;
      }

      if (mPredictMoveState[k] == MOVE_ATTACK)
      {
        int index = getModelPositionIndex(mod->getPosition(), mFields, 40);

        mPredictPosition[k]->piece->setArea(AREA_OUT);
        mPredictPosition[k]->piece->setPosition(mPredictPosition[k]->piece->getInitPosition().position);
        mPredictPosition[k]->piece->setAngle(mPredictPosition[k]->piece->getInitPosition().direction);

        mFields[index].piece = NULL;
        mPredictPosition[k]->piece = mod;
      }

      if (mPredictMoveState[k] == MOVE_START_ATTACK)
      {
        mPredictPosition[k]->piece->setArea(AREA_OUT);
        mPredictPosition[k]->piece->setPosition(mPredictPosition[k]->piece->getInitPosition().position);
        mPredictPosition[k]->piece->setAngle(mPredictPosition[k]->piece->getInitPosition().direction);

        mPredictPosition[k]->piece = mod;
        mPredictPosition[k]->piece->setArea(AREA_GAME);
      }

      if (mPredictMoveState[k] == MOVE_START)
      {
        mPredictPosition[k]->piece = mod;
        mPredictPosition[k]->piece->setArea(AREA_GAME);
      }

      if (mPredictMoveState[k] == MOVE_HOME_INSIDE)
      {
        int index = getModelPositionIndex(mod->getPosition(), mHome, 16);

        mHome[index].piece = NULL;
        mPredictPosition[k]->piece = mod;
      }

      /*if (mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
      {
        int index = getModelPositionIndex(mod->getPosition(), mFields, 40);

        mFields[index].piece = NULL;
        mPredictPosition[k]->piece = mod;
        mPredictPosition[k]->piece->setArea(AREA_HOME);
      }*/

      mod->jumpTo(target, mPredictMoveState[k]);
      mPieceIsMoving = true;
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
    mIsGoHome[playerTurn] = true;
  }
}

// Predict if next move is illegal or not,
// which field pieces will be in
void GameScene::predictNextMove(int number)
{
  if (mDieIsThrown)
    return;
  //mDiceNumber = rand() % 6 + 1;
  mDieIsThrown = true;
  mustBeStart = false;
  allMoveIllegal = true;
  noPieceInTheGame = true;
  mDieNumber = number;

  for (int i = 0; i < 4; i++)
  {
    mPredictPosition[i] = NULL;
    mPredictMoveState[i] = MOVE_ILLEGAL;
    mIsGoHome[i] = false;
  }

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
          // Checking if no allied pieces on the way to target field
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
            mPredictPosition[i] = &mHome[indexCurHome + mDieNumber];
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
      //if ((indexCurRoad == indexFirstPos-1 || indexCurRoad == indexFirstPos-1+40) 
      //  && mDieNumber <= 4)
      //{
        bool blocked = false;
        // Checking if no piece on the way to target field
        for (int j = mPlayerTurn*4; j < mPlayerTurn*4 + indexNext - indexFirstPos + 1; j++)
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
          mPredictPosition[i] = &mHome[mPlayerTurn*4 + indexNext - indexFirstPos];
          mPredictMoveState[i] = MOVE_HOME_OUTSIDE; 
        }
      //}
      // Dice > 4, can not move
      continue;
    }

    /*---------------- ATTACK && NORMAL -------------------*/
    // Checking if target field is not empty
    if (mFields[indexNext].piece != NULL)
    {
      // Target piece is allied
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
    mPredictPosition[i] = &mFields[predictIndexPos[i]];

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
      noPieceInTheGame = false;
    }
  }

  // No piece can move?
  if (allMoveIllegal)
  {
    nextTurn();

    mDieIsDrawn = true;
  }
}

void GameScene::update()
{
  // Checking if die is displayed and show the number to user
  if (mDieIsDrawn && mDice->getState() == DIE_STOP)
  {
    mDieIsDrawn = false;
    this->predictNextMove(mDieNumber);
  }

  if (mPieceIsMoving && !mDieIsDrawn )
  {
    if (checkAllModelIdle())
    {
      if (wait(1))
      {
        mPieceIsMoving = false;

        mDieIsDrawn = true;
      }
    }
  }

  if (mAutoCam)
  {
    float delta = 0.05;

    float curTheta = Camera::inst().theta;

    if (curTheta - mUserViewAngle > Math::PI)
    {
      curTheta -= Math::TWO_PI;
    }
    else if (curTheta - mUserViewAngle < -Math::PI)
    {
      curTheta += Math::TWO_PI;
    }

    if (abs(curTheta - mUserViewAngle) > delta)
    {
      if (curTheta > mUserViewAngle)
        Camera::inst().rotateTheta(curTheta - delta);
      else
        Camera::inst().rotateTheta(curTheta + delta);
    }
    else
    {
      mAutoCam = false;
    }
  }
}

// Disable some Players
void GameScene::setDisablePiece( int index )
{
  mEnablePiece[index] = false;
  if (mPlayerTurn == index)
  {
    for (int i = 0; i < 4; i++)
    {
      // Change start turn if the currently is disabled
      if (!mEnablePiece[i])
      {
        mPlayerTurn = (Turn)(i+1 > 4 ? 0 : i+1);
        break;
      }
    } 
  }
}

void GameScene::processMouseBegan( int x, int y )
{
  // If die is currently displayed
  if (mDieIsDrawn)
  {
    // Roll die
    if (mDice->getState() == DIE_WAITING)
      mDieNumber = mDice->rollDie();
  }
  else
  {
    // Click the Piece
    int index = identifyModelClicked(x, y);
    if (index >= 0)
      movePiece(index);
  }
}

void GameScene::processMousePassiveMotion( int x, int y )
{
  int index = identifyModelClicked(x, y);
  if (index != selectedIndex)
  {
    if (selectedIndex >= 0)
      mPieces[selectedIndex]->selected(false);
    if (index >= 0 && mPieces[index]->isHighlight())
    {
      mPieces[index]->selected(true);
      mUserViewAngle = calcUserViewAngle(mPieces[index]->getPosition());
    }
    selectedIndex = index;
  }
}

// Identify which Piece has been clicked
// Return index of Piece in array
int GameScene::identifyModelClicked( int mouse_x, int mouse_y )
{
  // Get x, y coordinate in zNear plane
  int window_y = mouse_y - Graphic::inst().screenHeight/2;
  double norm_y = double(window_y)/double(Graphic::inst().screenHeight/2);
  int window_x = mouse_x - Graphic::inst().screenWidth/2;
  double norm_x = double(window_x)/double(Graphic::inst().screenWidth/2);

  float aspect = Graphic::inst().screenWidth/Graphic::inst().screenHeight;

  float y = Graphic::inst().near_height * norm_y;
  float x = Graphic::inst().near_height * aspect * norm_x;

  // Get ModelView matrix
  float m[16];
  glGetFloatv(GL_MODELVIEW_MATRIX , m);

  Matrix4 inverseModelViewMatrix = Matrix4(m).inverse();

  // Calculate origin and vector of clicked-ray
  Vector4 rayOrigin = Vector4()*inverseModelViewMatrix;
  Vector3 rayVec = Vector3(x, y, -Graphic::inst().zNear)*inverseModelViewMatrix;

  //cout << rayOrigin.toString();

  mViewRay.set(rayOrigin.toVector3(), rayVec);

  Piece** piecesArray = getPiecesArray();

  float disMin = -1;
  int index = -1;

  for (int i = 0; i < 16; i++)
  {
    // checking click-ray intersected with piece
    if (mViewRay.hasIntersected(piecesArray[i]->boundingbox()))
    {
      //cout << "intersected" << endl;
      
      Vector3 a = Camera::inst().eye;
      Vector3 b = piecesArray[i]->getPosition();
      float dist = (a-b).magnitude();

      // get the nearest piece
      if (disMin < 0)
      {
        disMin = dist;
        index = i;
      }
      else if (dist < disMin)
      {
        disMin = dist;
        index = i;
      }
    }
  }

  return index;
}


float GameScene::calcUserViewAngle( Vector3 pV )
{
  mAutoCam = true;

  Vector2 viewVector = Vector2(pV.x, pV.z) - Vector2(Camera::inst().at.x, Camera::inst().at.z);
  float angle = acos(Vector2::dot(viewVector, Camera::inst().zeroViewVector)/
    (viewVector.magnitude() * Camera::inst().zeroViewVector.magnitude()));

  if (viewVector.x >= 0)
    return angle;
  else
    return -angle;
}

GameScene::~GameScene(void)
{
}
