#include "LoadingScene.h"
#include "GameScene.h"
#include "SelectPlayersScene.h"
#include "MainMenuScene.h"

//float colorW[4] = {1,1,1,1};
//void* font = GLUT_BITMAP_8_BY_13;

LoadingScene::LoadingScene(void)
{
  ;
}

LoadingScene& LoadingScene::inst()
{
  static LoadingScene instance;
  return instance;
}

void LoadingScene::initSprite()
{
  mBackground = Sprite2D::create("img/loading/background.png");
  mBackground->setAnchorPoint(Vector2(-0.5, -0.5));

  mProgress = ProgressTimerSprite2D::create("img/loading/progress.png");
  mProgress->setPosition(Vector2(400, 162));

  /*sprintf(buffer, "0%");*/
}

void LoadingScene::drawScene()
{
  mBackground->drawImg();
  mProgress->drawImg();
  
  //Graphic::inst().drawString(buffer, 400, 162, colorW, font);
}

void LoadingScene::loop()
{
  load();

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  {
    glLoadIdentity();
    glOrtho(0, Graphic::inst().screenWidth,
      0, Graphic::inst().screenHeight,
      -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    {
      glLoadIdentity();
      glDisable(GL_CULL_FACE);

      glClear(GL_DEPTH_BUFFER_BIT);

      drawScene();
    }
    glPopMatrix();

    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
  }

  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

LoadingScene::~LoadingScene(void)
{
}

void LoadingScene::load()
{
  static int i = 0;
  if (!wait(LOADING_DELAY_PER_LOOP))
    return;

  switch (i)
  {
  case 0:
    SelectPlayersScene::inst().initSprite();
    cout << "SELECT PLAYERS SCENE" << endl;
    mProgress->setPercent(10);
    break;
  case 1:
    MainMenuScene::inst().initSprite();
    cout << "MAIN MENU SCENE" << endl;
    mProgress->setPercent(20);
    break;
  case 2:
    GameScene::inst().initBoard();
    cout << "GAME SCENE Board" << endl;
    mProgress->setPercent(45);
    break;
  case 3:
    GameScene::inst().initDie();
    cout << "GAME SCENE Die" << endl;
    mProgress->setPercent(75);
    break;
  case 4:
    GameScene::inst().initPieces();
    cout << "GAME SCENE Pieces" << endl;
    mProgress->setPercent(100);
    break;
  default:
    Graphic::inst().setAppScene(APP_MENU);
    break;
  }

  i++;
}
