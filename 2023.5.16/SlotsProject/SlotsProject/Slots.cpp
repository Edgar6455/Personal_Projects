#include <windows.h>  // Play Sound(1)

#include <iostream>
#include <random>                  // Random number generation
#pragma comment(lib, "winmm.lib")  // Play Sound(2)
#include "Slots.h"

// Static member initialization
int Slots::credits = 100000;

// Public base functions
bool Slots::setBet(int newbet) {
  if (credits < newbet) {
    return true;
  }

  bet = newbet;
  return false;
}

bool Slots::creditsNot0() {
  if (credits == 0) {
    return false;
  }

  else {
    return true;
  }
}


/*----------------------------------
          Fruity QickSpin
-----------------------------------*/

// Private functions
std::string FruityQuickSpin::getRandom() {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 999);
  int chance = dist(rd);  // [0, 999]

  std::string random = "n";

  if (chance >= 0 && chance < 500) {
    return "C";
  }

  if (chance >= 500 && chance < 800) {
    return "O";
  }

  if (chance >= 800 && chance < 1000) {
    return "L";
  }

  return random;
}

// Constructor
FruityQuickSpin::FruityQuickSpin() {
  left = getRandom();
  mid = getRandom();
  right = getRandom();

  bet = 1;
}

// Public functions
int FruityQuickSpin::spinWheel() {
  if (credits < bet) {
    return 1;
  }

  credits -= bet;
  left = getRandom();
  mid = getRandom();
  right = getRandom();

  if (left == mid && mid == right && right == "C") {
    credits += bet * 4;
    return 2;
  }

  if (left == mid && mid == right && right == "O") {
    credits += bet * 16;
    return 3;
  }

  if (left == mid && mid == right && right == "L") {
    credits += bet * 51;
    return 4;
  }

  return 0;
}

void FruityQuickSpin::displaySlot() {
  std::cout << " ,---.,---.  .-. .-.,-. _______.-.   .-.     .---. .-. .-.,-.  "
               ",--,  ,-. .-.  .---. ,---.  ,-..-. .-.\n";
  std::cout << " | .-'| .-.\\ | | | ||(||__   __|\\ \\_/ )/    ( .-. \\| | | "
               "||(|.' .')  | |/ /  ( .-._)| .-.\\ |(||  \\| |\n";
  std::cout << " | `-.| `-'/ | | | |(_)  )| |    \\   (_)   (_)| | || | | "
               "|(_)|  |(_) | | /  (_) \\   | |-' )(_)|   | | \n";
  std::cout << " | .-'|   (  | | | || | (_) |     ) (       | ||\\ || | | || "
               "|\\  \\    | | \\  _  \\ \\  | |--' | || |\\  |\n";
  std::cout << " | |  | |\\ \\ | `-')|| |   | |     | |       \\ `-\\\\/| "
               "`-')|| | \\  `-. | |) \\( `-'  ) | |    | || | |)|\n";
  std::cout << " )\\|  |_| \\)\\`---(_)`-'   `-'    /(_|        "
               "`---\\|`---(_)`-'  \\____\\|((_)-'`----'  /(     `-'/(  (_)\n";
  std::cout << "(__)      (__)                  (__)                           "
               "      (_)           (__)      (__)     \n\n";

  std::cout << "                                     _______________________\n";
  std::cout
      << " C - Cherry                         |=======================|\n";
  std::cout << "              C C C - x3            ||  _____ _____ _____  ||  "
               "      Credits: "
            << credits << "\n";
  std::cout << " O - Orange                         || |  " << left << "  |"
            << "  " << mid << "  |"
            << "  " << right << "  | ||\n";
  std::cout
      << "              O O O - x15           || |_____|_____|_____| ||\n";
  std::cout << " L - Lemon                          ||                     ||  "
               "      Bet: "
            << bet << " credits\n";
  std::cout
      << "              L L L - x50           |=======================|\n";
  std::cout
      << "                                   /      (__)         ,---, \\\n";
  std::cout
      << "                                  /  (__)      (__)    |___|  \\\n";
  std::cout
      << "                                 /        (__)                 \\\n";
  std::cout << "                                "
               "=================================\n\n";
}

void FruityQuickSpin::reset() {
  left = getRandom();
  mid = getRandom();
  right = getRandom();
}


/*----------------------------------
             Gold Pot
-----------------------------------*/

// Private functions
std::string GoldPot::getRandom() {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 95);

  int chance = dist(rd);
  std::string random = "     ";

  if (chance >= 0 && chance < 7) {
    random = " (1) ";
    return random;
  }

  if (chance >= 7 && chance < 12) {
    random = " (2) ";
    return random;
  }

  if (chance >= 12 && chance < 16) {
    random = " (3) ";
    return random;
  }

  if (chance >= 16 && chance < 19) {
    random = " (4) ";
    return random;
  }

  if (chance == 19) {
    random = " (5!)";
    return random;
  }

  if (chance == 20) {
    random = " (7) ";
    return random;
  }

  if (chance >= 21 && chance < 23) {
    random = " (M) ";
    return random;
  }

  if (chance >= 23) {
    random = "     ";
    return random;
  }

  return random;
}

bool GoldPot::checkWin() {
  bool won = true;

  for (int i = 0; i < 5; ++i) {
    if (symbols[i] == "     ") {
      won = false;
      break;
    }
  }

  if (won) {
    for (int i = 5; i < 15; ++i) {
      symbols[i] = "     ";
    }
    return true;
  }

  won = true;

  for (int i = 5; i < 10; ++i) {
    if (symbols[i] == "     ") {
      won = false;
      break;
    }
  }

  if (won) {
    for (int i = 0; i < 5; ++i) {
      symbols[i] = "     ";
    }
    for (int i = 10; i < 15; ++i) {
      symbols[i] = "     ";
    }
    return true;
  }

  won = true;

  for (int i = 10; i < 15; ++i) {
    if (symbols[i] == "     ") {
      won = false;
      break;
    }
  }

  if (won) {
    for (int i = 0; i < 10; ++i) {
      symbols[i] = "     ";
    }
  }

  return won;
}

int GoldPot::getSymbolValue(const std::string& symbol) {
  int value = 0;

  if (symbol == " (1) ") {
    value = 1;
    return value;
  }

  if (symbol == " (2) ") {
    value = 2;
    return value;
  }

  if (symbol == " (3) ") {
    value = 3;
    return value;
  }

  if (symbol == " (4) ") {
    value = 4;
    return value;
  }

  if (symbol == " (5!)") {
    value = 5;
    return value;
  }

  if (symbol == " (7) ") {
    value = 7;
    return value;
  }

  if (symbol == " (M) ") {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 4);

    int chance = dist(rd);

    if (chance == 0) {
      value = 0;
      return value;
    }

    if (chance == 1) {
      value = 1;
      return value;
    }

    if (chance == 2) {
      value = 2;
      return value;
    }

    if (chance == 3) {
      value = 5;
      return value;
    }

    if (chance == 4) {
      value = 20;
      return value;
    }
  }

  return -1;
}

// Constructor
GoldPot::GoldPot() {
  bet = 1;

  for (int i = 0; i < 15; ++i) {
    symbols[i] = getRandom();
  }
}

// Public functions
int GoldPot::spinWheel() {
  if (credits < bet) {
    return 1;
  }

  credits -= bet;

  for (int i = 0; i < 15; ++i) {
    if (symbols[i] == " (5!)") {
      continue;
    }
    symbols[i] = getRandom();
  }

  if (checkWin()) {
    PlaySound(TEXT("win2.wav"), nullptr, SND_FILENAME | SND_ASYNC);
    return 2;
  }

  return 0;
}

bool GoldPot::bonusSpin() {
  bool gotSomething = false;

  for (int i = 0; i < 15; ++i) {
    if (symbols[i] != "     ") {
      continue;
    }

    symbols[i] = getRandom();

    if (symbols[i] != "     ") {
      gotSomething = true;
    }
  }

  return gotSomething;
}

void GoldPot::displaySlot() {
  std::cout << "       ______      ____      _____      ______           "
               "_______      ____     _________  \n";
  std::cout << "     .' ___  |   .'    `.   |_   _|    |_   _ `.        |_   "
               "__ \\   .'    `.  |  _   _  | \n";
  std::cout << "    / .'   \\_|  /  .--.  \\    | |        | | `. \\         | "
               "|__) | /  .--.  \\ |_/ | | \\_| \n";
  std::cout << "    | |   ____  | |    | |    | |   _    | |  | |         |  "
               "___/  | |    | |     | |     \n";
  std::cout << "    \\ `.___]  | \\  `--'  /   _| |__/ |  _| |_.' /        _| "
               "|_     \\  `--'  /    _| |_    \n";
  std::cout << "     `._____.'   `.____.'   |________| |______.'        "
               "|_____|     `.____.'    |_____|   \n\n\n";

  std::cout
      << "                              |===============================|\n";
  std::cout << "   Get 5 symbols on one row   "
               "||_____________________________||   __\n";
  std::cout << "    to hit the bonus round    ||" << symbols[0] << "|"
            << symbols[1] << "|" << symbols[2] << "|" << symbols[3] << "|"
            << symbols[4] << "||  /  \\\n";
  std::cout << "      and win even more!      "
               "||_____|_____|_____|_____|_____|| |    |   Credits: "
            << credits << "\n";
  std::cout << "                              ||" << symbols[5] << "|"
            << symbols[6] << "|" << symbols[7] << "|" << symbols[8] << "|"
            << symbols[9] << "||  \\__/\n";
  std::cout << "  (5!) will be fixed in it's  "
               "||_____|_____|_____|_____|_____||  | |\n";
  std::cout << "   place to increase chance   ||" << symbols[10] << "|"
            << symbols[11] << "|" << symbols[12] << "|" << symbols[13] << "|"
            << symbols[14] << "||  | |\n";
  std::cout << "        of winning!           "
               "||_____|_____|_____|_____|_____||  | |     Bet: "
            << bet << " credits\n";
  std::cout << "                              |                               "
               "|__| |\n";
  std::cout << "    (M) is mystery symbol     "
               "|===============================|____|\n";
  std::cout
      << "                              |                               |\n\n";
}

void GoldPot::collectRewards() {
  bool first = true;
  int reward = 0;

  for (int i = 0; i < 15; ++i) {
    if (symbols[i] == "     ") {
      continue;
    }

    int current = getSymbolValue(symbols[i]);
    reward += current;

    if (first) {
      std::cout << " ";

      if (symbols[i] == " (M) ") {
        std::cout << "M->";
      }

      std::cout << current;
      first = false;
    }

    else {
      std::cout << " + ";

      if (symbols[i] == " (M) ") {
        std::cout << "M->";
      }

      std::cout << current;
    }
  }
  reset();
  credits += reward;
  std::cout << " = " << reward << "\n\n";
}

void GoldPot::reset() {
  for (int i = 0; i < 15; ++i) {
    symbols[i] = getRandom();
  }
}
