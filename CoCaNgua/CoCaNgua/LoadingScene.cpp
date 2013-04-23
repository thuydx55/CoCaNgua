#include "LoadingScene.h"
#include "GameScene.h"
#include "SelectPlayersScene.h"
#include "MainMenuScene.h"


LoadingScene::LoadingScene(void)
{
  mTimer.start();
}

LoadingScene& LoadingScene::inst()
{
  static LoadingScene instance;
  return instance;
}

void LoadingScene::loop()
{
  static int i = 0;
  if (mTimer.elapsed() < i*LOADING_DELAY_PER_LOOP)
    return;

  switch (i)
  {
  case 0:
    SelectPlayersScene::inst().initSprite();
    cout << "SELECT PLAYERS SCENE" << endl;
    break;
  case 1:
    MainMenuScene::inst().initSprite();
    cout << "MAIN MENU SCENE" << endl;
    break;
  case 2:
    GameScene::inst().initModel();
    cout << "GAME SCENE" << endl;
    break;
  default:
    Graphic::inst().setAppScene(APP_MENU);
    break;
  }

  i++;
}

LoadingScene::~LoadingScene(void)
{
}
