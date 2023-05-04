#pragma once

#include "Character.h"
#include "common/Position.h"
#include "common/Direction.h"
#include "common/Tile.h"

#include <iostream>
#include <SDL.h>
#include <vector>

class GameModel;

class Ghost : public Character {
public:
    enum class Type {
        BLINKY,
        PINKY,
        INKY,
        CLYDE
    };

    enum class Mode {
        SCATTER,
        CHASE,
        FRIGHTENED
    };

    //Ghost(GameModel& gameModel, Type ghost_type, Position initial_position, Direction direction, Direction sprite_orientation);
    Ghost(GameModel& gameModel, Type ghost_type, Position initial_position, Direction direction, Tile scatter_target_tile, bool out_of_den);
    virtual ~Ghost();

    Type getType() const;

    void setMode(Mode mode);
    Mode getMode() const;

    void setChaseTargetTile(Tile tile);
    Tile getScatterTargetTile() const;

    void setCurrentTargetTile(Tile tile);
    Tile getCurrentTargetTile() const;

    

protected:
    Type ghost_type;
    Mode ghost_mode=Mode::SCATTER;

    Tile scatter_target_tile;
    Tile chase_target_tile;

    Tile current_target_tile;

    std::vector<Tile> forbiden_tiles_UP={{13,12},{13,15}};
    std::vector<Tile> forbiden_tiles_DOWN={{25,12},{25,15}};

    Position out_of_den_position;
    Position center_den_position;

    bool out_of_den;
};
