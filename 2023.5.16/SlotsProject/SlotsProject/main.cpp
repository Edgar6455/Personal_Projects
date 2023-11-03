#include <iostream>

#include "Game.h"

int main() {
  // Initializing Game Engine
  Game game;

  // Game Loop
  while (game.gameRunning()) {
    game.display();
    game.getCondition();
    game.choice();
    system("cls");
  }

  game.over();

  return 0;
}