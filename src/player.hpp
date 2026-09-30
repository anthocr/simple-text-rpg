#pragma once

#include <string>

struct Player {
  explicit Player(std::string playerName);

  std::string name;
  int health;
  int maximumHealth;
  int attack;
  int defense;
  int experience;
  int level;

  void restoreHealth(int amount);
  void takeDamage(int amount);
  void addExperience(int amount);
  bool isDefeated() const;
};
