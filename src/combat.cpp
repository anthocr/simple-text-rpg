#include "combat.hpp"

#include <algorithm>

int calculateDamage(int attackerAttack, int defenderDefense) {
  return std::max(1, attackerAttack - defenderDefense);
}

void applyDamage(Player& player, int damage) {
  player.takeDamage(damage);
}

void applyDamage(Enemy& enemy, int damage) {
  enemy.takeDamage(damage);
}

bool isDefeated(const Player& player) {
  return player.isDefeated();
}

bool isDefeated(const Enemy& enemy) {
  return enemy.isDefeated();
}

void awardExperience(Player& player, int experience) {
  player.addExperience(experience);
}
