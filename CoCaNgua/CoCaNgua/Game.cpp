#include "Game.h"


Game::Game(void)
{
}

Game& Game::inst()
{
  static Game Instance;
  return Instance;
}

void Game::loop()
{

}


Game::~Game(void)
{
}
