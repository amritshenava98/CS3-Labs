// Dice game with Game template
// Dan Fabian
// 3/14/2019

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl; using std::cin;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
  Game():playersCount_(0), movesCount_(0), 
	 playerWon_(noWinner){}

  // template method
  void playGame(const int playersCount = 0) {
    playersCount_ = playersCount;
    movesCount_=0;

    initializeGame();

    for(int i=0; !endOfGame(); 
	i = (i+1) % playersCount_ ){
      makeMove(i);
      if (i==playersCount_-1) 
	++movesCount_; 
    }

    printWinner();
  }

  virtual ~Game(){}

protected:
  // primitive operations
  virtual void initializeGame() = 0;
  virtual void makeMove(int player) = 0;
  virtual void printWinner() = 0;
  virtual bool endOfGame() {
    return playerWon_ != noWinner;} // this is a hook
  // returns true if winner is decided
  static const int noWinner=-1;

  int playersCount_;
  int movesCount_;
  int playerWon_;
};

//////////////////////////////////////////////////////////////////////
class Dice: public Game {
public:
  void initializeGame() override final 
  {
    playersCount_ = numPlayers_;
    for (bool e: pass_) e = false;
  }

  void makeMove(int) override final;

  void printWinner() override final
  {
    if (playerWon_ == 0) cout << "You lost\n";
    else cout << "You Win!\n";
  }

private:
  static const int numPlayers_ = 2; // computer = player 0, human = player 1
  static const int maxRounds_ = 3; // 3 rounds max
  static const int numRolls_ = 5; // 5 rolls per turn
  bool pass_[numPlayers_]; // stores whether or not player passed
  int highScore_[numPlayers_]; // stores highest totals
};
//////////////////////////////////////////////////////////////////////

void Dice::makeMove(int player)
{
  // check total moves
  if (movesCount_ == maxRounds_ || (pass_[0] && pass_[1]))
    {
      playerWon_ = highScore_[0] >= highScore_[1] ? 0 : 1; 
      return;
    }
    
  // print whos going
  if (player == 0) cout << "Computer ";
  else cout << "You ";
    
  if (!pass_[player])  // check if player passed
    {
      cout << "rolled: ";
      
      // roll the dice and calc total
      int rolls[numRolls_];
      int total = 0;
      for (int e: rolls) 
	{
	  e = rand() % 6 + 1;
	  total += e;
	  cout << e << ' ';
	}
      cout << " = " << total << ", ";
      
      // check high score
      if (highScore_[player] < total) 
	highScore_[player] = total;
    }
  else // player passed 
    cout << "passed, ";

  // printing highest scores
  if (player == 0) cout << "computer's ";
  else cout << "your ";
  cout << "highest score = " << highScore_[player] << '\n';

  // check if player wants to roll again and if its the last round
  if (!pass_[player] && player == 1 && movesCount_ < maxRounds_ - 1)
    {
      cout << "Roll again? [y/n] ";
      char ans; cin >> ans;
      if (ans == 'n') pass_[player] = true; 
    }
  else if (!pass_[player] && player == 0)
    {
      int choice = rand() % 2; // 0 is to not roll again
      if (choice == 0)  pass_[player] = true;
    }
}


int main() {
  srand(time(nullptr));

  Game* gp = new Dice;
  gp->playGame();
  delete gp;
}
