#include "player.hpp"

#include <algorithm>
#include <utility>

Player::Player(std::string playerName)
    : name(std::move(playerName)),
      health(20),
      maximumHealth(20),
      attack(5),
      defense(1),
      experience(0),
      level(1) {}

void Player::restoreHealth(int amount) {
  health = std::min(maximumHealth, health + amount);
}

void Player::takeDamage(int amount) {
  health = std::max(0, health - amount);
}

void Player::addExperience(int amount) {
  experience += amount;

  if (level == 1 && experience >= 20) {
    level = 2;
    maximumHealth += 2;
    health = maximumHealth;
    attack += 1;
  }
}

bool Player::isDefeated() const {
  return health == 0;
}
