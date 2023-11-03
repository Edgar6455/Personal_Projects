#ifndef SLOTS_H
#define SLOTS_H

class Slots {
 protected:
  // Variables
  static int credits;
  int bet;

  // Private pure virtual funcitons
  virtual std::string getRandom() = 0;

 public:
  // Public base functions
  bool setBet(int newbet);
  bool creditsNot0();

  // Public pure virtual functions
  virtual int spinWheel() = 0;
  virtual void displaySlot() = 0;
  virtual void reset() = 0;
};

class FruityQuickSpin : public Slots {
 private:
  // Local variables
  std::string left, mid, right;

  // Private functions
  std::string getRandom() override;

 public:
  // Constructor
  FruityQuickSpin();

  // Public functions
  int spinWheel() override;
  void displaySlot() override;
  void reset() override;
};

class GoldPot : public Slots {
 private:
  // Local variables
  std::string symbols[15];

  // Private functions
  std::string getRandom() override;
  bool checkWin();
  int getSymbolValue(const std::string& symbol);

 public:
  // Constructor
  GoldPot();

  // Public functions
  int spinWheel() override;
  bool bonusSpin();
  void displaySlot() override;
  void collectRewards();
  void reset() override;
};

#endif