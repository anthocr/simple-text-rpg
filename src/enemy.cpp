#include "enemy.hpp"

#include <algorithm>
#include <utility>

Enemy::Enemy(std::string enemyName, int startingHealth, int enemyAttack,
             int enemyDefense, int experienceReward)
    : name(std::move(enemyName)),
      health(startingHealth),
      attack(enemyAttack),
      defense(enemyDefense),
      xpReward(experienceReward) {}

void Enemy::takeDamage(int amount) {
  health = std::max(0, health - amount);
}

bool Enemy::isDefeated() const {
  return health == 0;
}
