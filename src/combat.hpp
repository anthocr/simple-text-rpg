#pragma once

#include "enemy.hpp"
#include "player.hpp"

int calculateDamage(int attackerAttack, int defenderDefense);
void applyDamage(Player& player, int damage);
void applyDamage(Enemy& enemy, int damage);
bool isDefeated(const Player& player);
bool isDefeated(const Enemy& enemy);
void awardExperience(Player& player, int experience);
