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
  mFullHome = false;
  mPieceIsMoving = false;
  
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
    r[i].y = 2;
    mFields[i] = Field(r[i]);
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
    mPieces[i]->setPosition(mStartPos[i]);
    mPieces[i]->setInitPosition(mStartPos[i]);
    mPieces[i]->setType(TURN_RED);

    mPieces[4+i] = new Piece(tmp);
    mPieces[4+i]->setPosition(mStartPos[4+i]);
    mPieces[4+i]->setInitPosition(mStartPos[4+i]);
    mPieces[4+i]->setType(TURN_BLUE);

    mPieces[8+i] = new Piece(tmp);
    mPieces[8+i]->setPosition(mStartPos[8+i]);
    mPieces[8+i]->setInitPosition(mStartPos[8+i]);
    mPieces[8+i]->setType(TURN_GREEN);

    mPieces[12+i] = new Piece(tmp);
    mPieces[12+i]->setPosition(mStartPos[12+i]);
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
  Vector3 a = viewRay.origin + 100*viewRay.direction;

  glVertex3f(viewRay.origin.x, viewRay.origin.y, viewRay.origin.z);
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
  float left = -10*Graphic::inst().screenWidth/Graphic::inst().screenHeight;
  float right = 10*Graphic::inst().screenWidth/Graphic::inst().screenHeight;
  float bot = -10;
  float top = 10;
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

void GameScene::movePiece(int index)
{
  if (!mDieIsThrown)
    return;

  Piece* mod = mPieces[index];
  Turn playerTurn = mPlayerTurn;

  if (mod != NULL && mod->getType() == mPlayerTurn && checkAllModelIdle())
  {
    vector<Vector3> target;

    int k = index % 4;

    if (mPredictMoveState[k] == MOVE_ILLEGAL)
      return;
    if (mPredictMoveState[k] == MOVE_NORMAL)
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
      mPieceIsMoving = true;
      nextTurn();
    }
    else
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
    mPredictPosition[i] = Vector3();
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
    identifyModelClicked(x, Graphic::inst().screenHeight - y);
  }
}

// Identify which Piece has been clicked
void GameScene::identifyModelClicked( int mouse_x, int mouse_y )
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

  viewRay.set(rayOrigin.toVector3(), rayVec);

  Piece** piecesArray = getPiecesArray();

  float disMin = -1;
  int index = -1;

  for (int i = 0; i < 16; i++)
  {
    // checking click-ray intersected with piece
    if (viewRay.hasIntersected(piecesArray[i]->boundingbox()))
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

  if (index < 0)
    return;
  movePiece(index);
}

GameScene::~GameScene(void)
{
}
