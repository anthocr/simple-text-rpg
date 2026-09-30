#include "game.hpp"

#include "combat.hpp"
#include "enemy.hpp"
#include "player.hpp"

#include <array>
#include <istream>
#include <ostream>
#include <string>
#include <utility>

namespace {

constexpr int kHealAmount = 5;

std::array<Enemy, 3> createEnemies() {
  return {Enemy("Goblin", 10, 3, 0, 10),
          Enemy("Skeleton", 16, 5, 1, 10),
          Enemy("Dragon", 24, 7, 2, 10)};
}

}  // namespace

Game::Game(std::istream& inputStream, std::ostream& outputStream)
    : input(inputStream), output(outputStream) {}

void Game::run() {
  output << "=== Text RPG ===\n";
  output << "Defeat the Goblin, Skeleton, and Dragon to win.\n";

  while (true) {
    const GameResult result = playGame();
    if (result == GameResult::InputEnded) {
      return;
    }

    if (result == GameResult::Victory) {
      output << "Victory! You defeated the Dragon.\n";
    } else if (result == GameResult::Defeat) {
      output << "Defeat! Your adventure has ended.\n";
    } else {
      output << "You quit the game.\n";
    }

    if (!askToReplay()) {
      return;
    }
  }
}

Game::GameResult Game::playGame() {
  Player player("Hero");

  for (Enemy enemy : createEnemies()) {
    const GameResult result = playEncounter(player, std::move(enemy));
    if (result != GameResult::Victory) {
      return result;
    }
  }

  return GameResult::Victory;
}

Game::GameResult Game::playEncounter(Player& player, Enemy enemy) {
  bool healAvailable = true;
  output << "\nA " << enemy.name << " appears!\n";

  while (true) {
    output << "Hero: " << player.health << '/' << player.maximumHealth
           << " HP | Level " << player.level << " | XP " << player.experience
           << "\n";
    output << enemy.name << ": " << enemy.health << " HP\n";
    output << "Choose an action: [1] Attack [2] Heal [3] Quit\n> ";

    std::string choice;
    if (!readLine(choice)) {
      return GameResult::InputEnded;
    }

    if (choice == "1") {
      const int damage = calculateDamage(player.attack, enemy.defense);
      applyDamage(enemy, damage);
      output << "You deal " << damage << " damage to the " << enemy.name
             << ".\n";
    } else if (choice == "2") {
      if (!healAvailable) {
        output << "You have already used Heal in this encounter.\n";
        continue;
      }

      const int healthBeforeHealing = player.health;
      player.restoreHealth(kHealAmount);
      output << "You restore " << player.health - healthBeforeHealing
             << " health.\n";
      healAvailable = false;
    } else if (choice == "3") {
      return GameResult::Quit;
    } else {
      output << "Invalid choice. Please enter 1, 2, or 3.\n";
      continue;
    }

    if (isDefeated(enemy)) {
      output << "You defeated the " << enemy.name << " and earned "
             << enemy.xpReward << " XP.\n";
      awardExperience(player, enemy.xpReward);
      return GameResult::Victory;
    }

    const int damage = calculateDamage(enemy.attack, player.defense);
    applyDamage(player, damage);
    output << "The " << enemy.name << " deals " << damage
           << " damage to you.\n";

    if (isDefeated(player)) {
      return GameResult::Defeat;
    }
  }
}

bool Game::askToReplay() {
  while (true) {
    output << "Play again? (y/n): ";

    std::string choice;
    if (!readLine(choice)) {
      return false;
    }

    if (choice == "y" || choice == "Y") {
      return true;
    }
    if (choice == "n" || choice == "N") {
      output << "Thanks for playing.\n";
      return false;
    }

    output << "Invalid choice. Please enter y or n.\n";
  }
}

bool Game::readLine(std::string& line) {
  if (std::getline(input, line)) {
    return true;
  }

  printInputEndedMessage();
  return false;
}

void Game::printInputEndedMessage() {
  if (!inputEndedMessagePrinted) {
    output << "\nInput ended. Goodbye.\n";
    inputEndedMessagePrinted = true;
  }
}
