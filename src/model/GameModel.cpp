#include "GameModel.h"
#include "Character.h"

#include <iostream>

GameModel::GameModel() : count(0) {
    // Initialize other game objects here
}

GameModel::~GameModel() {
    // Clean up if necessary
}

void GameModel::update(CharacterDirection input_direction) {
    // Update Ghost position
    ghost.updatePosition(count);

    // Update PacMan position
    if (input_direction != CharacterDirection::NONE)
        pacman.setIntendedDirection(input_direction);
    pacman.updatePosition(count);

    // Update other game objects here
    count = (count + 1) % 512;
}

Ghost& GameModel::getGhost() {
    return ghost;
}

PacMan& GameModel::getPacMan() {
    return pacman;
}

int GameModel::getCount() const {
    return count;
}

void GameModel::setCount(int count) {
    this->count = count;
}