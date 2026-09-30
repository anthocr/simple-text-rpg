#include "combat.hpp"
#include "enemy.hpp"
#include "game.hpp"
#include "player.hpp"

#include <cassert>
#include <sstream>
#include <string>

int main() {
  Player player("Hero");

  assert(player.health == 20);
  assert(player.maximumHealth == 20);
  assert(player.attack == 5);
  assert(player.defense == 1);
  assert(player.experience == 0);
  assert(player.level == 1);

  assert(calculateDamage(5, 1) == 4);
  assert(calculateDamage(1, 5) == 1);

  applyDamage(player, 30);
  assert(player.health == 0);
  assert(isDefeated(player));

  player.restoreHealth(50);
  assert(player.health == player.maximumHealth);

  Enemy goblin("Goblin", 10, 3, 0, 10);
  applyDamage(goblin, 10);
  assert(goblin.health == 0);
  assert(isDefeated(goblin));

  awardExperience(player, 10);
  assert(player.experience == 10);
  assert(player.level == 1);

  applyDamage(player, 5);
  awardExperience(player, 10);
  assert(player.experience == 20);
  assert(player.level == 2);
  assert(player.maximumHealth == 22);
  assert(player.health == 22);
  assert(player.attack == 6);

  std::istringstream input("not an action\n3\nn\n");
  std::ostringstream output;
  Game game(input, output);
  game.run();

  const std::string transcript = output.str();
  assert(transcript.find("Invalid choice. Please enter 1, 2, or 3.") !=
         std::string::npos);
  assert(transcript.find("You quit the game.") != std::string::npos);
  assert(transcript.find("Play again? (y/n):") != std::string::npos);
  assert(transcript.find("deals") == std::string::npos);

  return 0;
}
