#pragma once
class Game
{
  void draw();

public:
  Game(void);
  ~Game(void);

  Game& inst();

  void loop();
};

