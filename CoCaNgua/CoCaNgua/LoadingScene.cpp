#include "LoadingScene.h"
#include "GameScene.h"
#include "SelectPlayersScene.h"
#include "MainMenuScene.h"


LoadingScene::LoadingScene(void)
{

}

LoadingScene& LoadingScene::inst()
{
  static LoadingScene instance;
  return instance;
}

void LoadingScene::loop()
{
  static int i = 0;
  if (!wait(LOADING_DELAY_PER_LOOP))
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
    GameScene::inst().initBoard();
    cout << "GAME SCENE Board" << endl;
    break;
  case 3:
    GameScene::inst().initDie();
    cout << "GAME SCENE Die" << endl;
    break;
  case 4:
    GameScene::inst().initPieces();
    cout << "GAME SCENE Pieces" << endl;
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
