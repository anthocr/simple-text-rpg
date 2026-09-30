# Spec: Basic Command-Line RPG

## Status

**Draft — awaiting human review.** This document defines the proposed version-1
scope. Implementation must not begin until it is approved.

## Objective

Build a small, single-player, turn-based role-playing game that runs in a
terminal. A player starts a game, fights three increasingly difficult enemies,
earns experience, levels up when eligible, and reaches either a victory or
defeat screen.

The intended user is someone learning or practicing C++ through a complete,
playable command-line program. Success means a new player can complete a game
without external instructions and the program handles invalid input safely.

## Version-1 Scope

### Included

- One player-controlled hero.
- Three fixed encounters: Goblin, Skeleton, then Dragon.
- Turn-based combat with `Attack`, `Heal`, and `Quit` actions.
- Player health, attack, defense, experience, and level.
- Experience rewards and a simple level-up system.
- Input validation, including clean handling of end-of-file input.
- Replay option after victory, defeat, or quitting.

### Excluded

- Inventory, equipment, shops, maps, or branching stories.
- Saving and loading games.
- Multiplayer, networking, graphics, databases, or third-party game engines.

## Proposed Game Rules

The values in this section are assumptions to approve or revise before
implementation.

### Player

| Stat | Starting value |
|---|---:|
| Health / maximum health | 20 / 20 |
| Attack | 5 |
| Defense | 1 |
| Experience | 0 |
| Level | 1 |

### Combat

- The player selects an action first; a living enemy then attacks.
- `Attack` damage is `max(1, attacker.attack - defender.defense)`.
- `Heal` restores 5 health, never above maximum health, and can be used once
  in each encounter.
- `Quit` ends the current game without awarding experience.
- Invalid input does not consume a turn. End-of-file input prints a short
  message and exits with success.

### Enemies and progression

| Encounter | Health | Attack | Defense | XP reward |
|---|---:|---:|---:|---:|
| Goblin | 10 | 3 | 0 | 10 |
| Skeleton | 16 | 5 | 1 | 10 |
| Dragon | 24 | 7 | 2 | 10 |

- At 20 accumulated XP, the player advances to level 2.
- Leveling increases maximum health by 2, restores health to the new maximum,
  and increases attack by 1.
- Defeating the Dragon wins the game.

## Tech Stack

- C++17 or later.
- Standard library only; no runtime dependencies.
- CMake as the build system.
- A small assertion-based test executable built with CMake; no testing
  framework dependency is introduced.
- The repository's `cpp-container` Docker image provides a consistent build
  environment.

## Commands

Run these commands from the repository root in the provided container:

```sh
cmake -S . -B build
cmake --build build
./build/text_rpg
ctest --test-dir build --output-on-failure
```

Start an interactive container shell, when needed:

```sh
docker run -v "$(pwd)":/usr/src -it cpp-container sh
```

## Project Structure

```text
CMakeLists.txt             # Build targets and CTest registration
main.cpp                   # Program entry point only
src/player.hpp/.cpp        # Player state and level-up behavior
src/enemy.hpp/.cpp         # Enemy data and actions
src/combat.hpp/.cpp        # Combat turn and damage rules
src/game.hpp/.cpp          # Encounter/replay loop and input handling
tests/game_tests.cpp       # Assertion-based unit tests
specs/basic-rpg.md         # This specification
```

## Code Style

- Use C++17, standard-library types, and `#pragma once` header guards.
- Use PascalCase for classes and structs; camelCase for functions and fields.
- Keep game rules in named constants or clearly named functions rather than
  scattering literal values.
- Separate terminal input/output from combat calculations where practical so
  rules can be tested without interactive input.

```cpp
int calculateDamage(const Combatant& attacker, const Combatant& defender) {
  return std::max(1, attacker.attack - defender.defense);
}
```

## Testing Strategy

- Place automated tests in `tests/game_tests.cpp` and register them with CTest.
- Unit-test damage, health clamping, defeat detection, XP rewards, and the
  level-up threshold.
- Add non-interactive tests for invalid menu choices where input handling can
  be separated from terminal I/O.
- Manually verify a complete win, defeat, quit, replay, invalid input, and EOF
  path after every release candidate.

## Boundaries

### Always

- Build and run the full test suite before presenting an implementation.
- Validate all player input and preserve a playable state after invalid input.
- Keep the project dependency-free aside from the C++ standard library.
- Update this specification before changing an approved game rule or scope.

### Ask first

- Adding a dependency or test framework.
- Changing the specified game rules or version-1 scope.
- Adding persistence, networking, graphics, CI configuration, or new build
  tooling beyond CMake.

### Never

- Commit secrets or generated build artifacts.
- Remove tests to make a build pass.
- Add out-of-scope RPG systems to version 1 without approval.

## Success Criteria

- The project configures and builds with the documented CMake commands.
- The test command passes tests for damage, health clamping, defeat, XP, and
  leveling.
- A player can defeat the Goblin, Skeleton, and Dragon in sequence and see a
  victory screen.
- A player can lose a fight, quit a game, or replay after an ending.
- Invalid input never crashes the program or consumes a turn.
- End-of-file input exits cleanly.

## Open Questions

- Should the proposed player and enemy values be retained, or should combat be
  more forgiving or difficult?
- Should the player level only once in version 1, as specified, or be able to
  level repeatedly at later thresholds?
- Is CMake acceptable as the project build system?
