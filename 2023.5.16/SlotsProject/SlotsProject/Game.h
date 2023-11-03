#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "Slots.h"

// A class, that acts like a game engine
class Game {
 private:
  // Game logic variables
  FruityQuickSpin slotFruity;
  GoldPot slotGoldPot;

  // 0 - Fruity | 1 - Gold Pot
  bool slotType;

  // Condition flags
  bool running;
  bool invalidChoice;
  bool CreditsNotEnough;
  bool wonSomething;
  bool fiveOnLine;
  bool bonusSpin;
  bool collectRewards;
  bool noChoice;
  bool playSound;

  std::string spinResult;

  // Private Functions
  void wellcome();
  void spin();
  void changeBet(int newbet);

 public:
  // Constructor
  Game();

  // Public Functions
  bool gameRunning() const;

  void display();
  void getCondition();
  void choice();

  void over();
};

#endif  // !GAME_H