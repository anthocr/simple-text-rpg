#pragma once

#include <iosfwd>
#include <string>

class Game {
 public:
  Game(std::istream& input, std::ostream& output);

  void run();

 private:
  enum class GameResult { Victory, Defeat, Quit, InputEnded };

  GameResult playGame();
  GameResult playEncounter(class Player& player, class Enemy enemy);
  bool askToReplay();
  bool readLine(std::string& line);
  void printInputEndedMessage();

  std::istream& input;
  std::ostream& output;
  bool inputEndedMessagePrinted = false;
};
