#pragma once

#include <string>

struct Enemy {
  Enemy(std::string enemyName, int startingHealth, int enemyAttack,
        int enemyDefense, int experienceReward);

  std::string name;
  int health;
  int attack;
  int defense;
  int xpReward;

  void takeDamage(int amount);
  bool isDefeated() const;
};
