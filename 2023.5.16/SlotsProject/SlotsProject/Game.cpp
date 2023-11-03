#include "Game.h"

#include <windows.h>  // Play Sound(1)

#include "Slots.h"
#pragma comment(lib, "winmm.lib")  // Play Sound(2)


/*----------------------------------
         Private Functions
-----------------------------------*/

void Game::wellcome() {
  bool flag = false;

  std::cout << "\n Note: Zoom this window for the best experience with Ctrl + "
               "ScrollUp\n\n\n";
  std::cout << " Warning! The game can be playing sound in some places, so "
               "please, don't be surprised!\n\n\n ";
  system("pause");
  system("cls");
  PlaySound(TEXT("wellcome.wav"), nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);

  while (true) {
    std::cout << "\n Hi! Welcome to Slots made by Edgar Khachatryan!\n\n";
    std::cout << " Here we have 2 kind of slots. The first is the simple one, "
                 "the second is more unique.\n\n\n";
    std::cout << " Please choose one of them to begin.\n\n\n";
    std::cout << " 1) Fruity QuickSpin\n";
    std::cout << " 2) Gold Pot\n\n\n";

    if (flag) {
      std::cout << " Wrong input! Try again!\n\n";
    }

    std::cout << " Type 1 or 2 to choose the slot: ";
    std::string input;
    std::cin >> input;

    if (input.length() > 1 || input[0] != '1' && input[0] != '2') {
      flag = true;
      system("cls");
      continue;
    }

    if (input[0] == '1') {
      slotType = false;
      system("cls");
      PlaySound(nullptr, nullptr, 0);
      PlaySound(TEXT("interior1.wav"), nullptr,
                SND_FILENAME | SND_ASYNC | SND_LOOP);
      break;
    }

    if (input[0] == '2') {
      slotType = true;
      system("cls");
      PlaySound(nullptr, nullptr, 0);
      PlaySound(TEXT("interior2.wav"), nullptr,
                SND_FILENAME | SND_ASYNC | SND_LOOP);
      break;
    }
  }
}

void Game::spin() {
  if (slotType == 0) {
    int result = slotFruity.spinWheel();

    switch (result) {
      case 1:
        CreditsNotEnough = true;
        break;
      case 2:
        wonSomething = true;
        spinResult =
            " Congratulations! You've won 3 times your bet with three Cherry "
            "symbols on the payline!";
        break;
      case 3:
        wonSomething = true;
        spinResult =
            " Big win!! You've won 15 times your bet with three Orange symbols "
            "on the payline!";
        break;
      case 4:
        wonSomething = true;
        spinResult =
            " JACKPOT!!! You've won 50 times your bet with three Lemon symbols "
            "on the payline!";
        break;
      default:
        spinResult = " You made my code go wrong. Congratulations!";
        break;
    }

    return;
  }

  if (slotType == 1) {
    int result = slotGoldPot.spinWheel();

    if (result == 1) {
      CreditsNotEnough = true;
      return;
    }

    if (result == 2) {
      fiveOnLine = true;
      return;
    }
  }
}

void Game::changeBet(int newbet) {
  if (slotType == 0) {
    if (slotFruity.setBet(newbet) == 1) {
      CreditsNotEnough = true;
    }

    return;
  }

  if (slotType == 1) {
    std::cout << "\n Warning! Changing bet will reset current reel. "
                 "Continue?\n 1 - Yes, anything else - No: ";
    std::string input;
    std::cin >> input;
    if (input.length() == 1 && input[0] == '1') {
      if (slotGoldPot.setBet(newbet)) CreditsNotEnough = true;
      slotGoldPot.reset();
    }
    return;
  }
}


/*----------------------------------
             Constructor
-----------------------------------*/

Game::Game() {
  running = true;
  invalidChoice = false;
  CreditsNotEnough = false;
  wonSomething = false;
  fiveOnLine = false;
  bonusSpin = false;
  collectRewards = false;
  noChoice = false;
  slotType = false;
  playSound = false;

  wellcome();
}


/*----------------------------------
          Public Functions
-----------------------------------*/

bool Game::gameRunning() const { return running; }

void Game::display() {
  if (slotType == 0) {
    slotFruity.displaySlot();
  }

  if (slotType == 1) {
    slotGoldPot.displaySlot();
  }
}

void Game::getCondition() {
  if (collectRewards) {
    std::cout << " No new symbols on the Reel. Collecting rewards...\n";
    slotGoldPot.collectRewards();
    collectRewards = false;
    std::cout << "\n ";
    noChoice = true;
    system("pause");
    PlaySound(TEXT("interior2.wav"), nullptr,
              SND_FILENAME | SND_ASYNC | SND_LOOP);
    return;
  }

  if (fiveOnLine) {

    if (bonusSpin) {
      std::cout << " New symbol(s) on the Reel!\n";
    } else {
      std::cout << " Gotcha! 5 symbols on one line!\n";
    }

    std::cout << " Bonus spin is yours!\n\n ";
    system("pause");

    if (slotGoldPot.bonusSpin()) {
      bonusSpin = true;
    } else {
      fiveOnLine = false;
      bonusSpin = false;
      collectRewards = true;
    }

    noChoice = true;
    return;
  }

  if (slotGoldPot.creditsNot0() == false) {
    noChoice = true;
    running = false;
    PlaySound(nullptr, nullptr, 0);
    PlaySound(TEXT("spacesong.wav"), nullptr,
              SND_FILENAME | SND_ASYNC | SND_LOOP);
    std::cout << "\n ";
    system("pause");
    return;
  }

  if (playSound)
  {
    PlaySound(TEXT("interior1.wav"), nullptr,
              SND_FILENAME | SND_ASYNC | SND_LOOP);
    playSound = false;
  }

  if (wonSomething) {
    std::cout << spinResult << "\n\n";
    PlaySound(TEXT("win1.wav"), nullptr, SND_FILENAME | SND_ASYNC);
    wonSomething = false;
    playSound = true;
  }

  if (invalidChoice) {
    std::cout << " Invalid choice! Choose again!\n\n";
    invalidChoice = false;
  }

  if (CreditsNotEnough) {
    std::cout << " Not Enough credits! Try again with another value!\n\n";
    CreditsNotEnough = false;
  }
}

void Game::choice() {
  if (noChoice) {
    noChoice = false;
    return;
  }

  std::cout << " Choose action: \n 1) Spin again\n 2) Change bet\n 3) Change "
               "slot\n\n Your choice: ";
  std::string input;
  std::cin >> input;

  if (input.length() > 1 ||
      input[0] != '1' && input[0] != '2' && input[0] != '3') {
    invalidChoice = true;
    return;
  }

  if (input[0] == '1') {
    spin();
    return;
  }

  if (input[0] == '2') {
    int newbet;
    std::cout << " Select new bet (in range 1 - 100000): ";
    std::cin >> newbet;

    if (newbet < 1 || newbet > 100000) {
      invalidChoice = true;
      return;
    }

    changeBet(newbet);
  }

  if (input[0] == '3') {
    if (slotType == 0) {
      PlaySound(nullptr, nullptr, 0);
      PlaySound(TEXT("interior2.wav"), nullptr,
                SND_FILENAME | SND_ASYNC | SND_LOOP);
      slotType = 1;
    }

    else {
      PlaySound(nullptr, nullptr, 0);
      PlaySound(TEXT("interior1.wav"), nullptr,
                SND_FILENAME | SND_ASYNC | SND_LOOP);
      slotType = 0;
    }

    return;
  }
}

void Game::over() {
  std::cout << "  ______     ______     __    __     ______        ______     "
               "__   __   ______     ______   \n";
  std::cout << " /\\  ___\\   /\\  __ \\   /\\ \"-./  \\   /\\  ___\\      /\\ "
               " __ \\   /\\ \\ / /  /\\  ___\\   /\\  == \\   \n";
  std::cout << " \\ \\ \\__ \\  \\ \\  __ \\  \\ \\ \\-./\\ \\  \\ \\  __\\    "
               "  \\ \\ \\/\\ \\  \\ \\ \\'/   \\ \\  __\\   \\ \\  __<    \n";
  std::cout
      << "  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\     "
         "\\ \\_____\\  \\ \\__|    \\ \\_____\\  \\ \\_\\ \\_\\ \n";
  std::cout << "   \\/_____/   \\/_/\\/_/   \\/_/  \\/_/   \\/_____/      "
               "\\/_____/   \\/_/      \\/_____/   \\/_/ /_/ \n\n\n\n";

  std::cout << "                                      You lost all your "
               "money...\n\n\n\n\n\n";
  std::cout << "                               Thanks for playing! I hope you "
               "enjoyed!\n\n\n\n\n\n\n\n";

  std::cout << "                                   ";
  system("pause");
}
