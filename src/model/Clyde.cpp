#include "Clyde.h"

#include "common/Position.h"
#include "common/Direction.h"
#include "GameModel.h"
#include "Ghost.h"

const Position init_pos_Clyde = Position((WINDOW_WIDTH-1)/2+2*TILE_SIZE, 17*TILE_SIZE + (TILE_SIZE-1)/2);
const Tile scatter_target_tile_Clyde = {WINDOW_ROWS-1,0};

Clyde::Clyde(GameModel& gameModel)
:Ghost(gameModel, Ghost::Type::CLYDE, init_pos_Clyde, Direction::UP, scatter_target_tile_Clyde, false)
{}

Clyde::~Clyde() {
    // Clean up Clyde-specific data here
}

void Clyde::move(int count) {
    (void)count;

    if(position.isCenteredOnTile() || out_of_den==false){
        //DEBUG
        //printDirection(direction);
        
        updateDirection();
    }

    //printDirection(direction);
    updatePosition();
}

void Clyde::updateDirection()
{
    if(position==init_pos_Clyde)
    {
        direction=Direction::LEFT;
        return;
    }
    else if(position==center_den_position)
    {
        direction=Direction::UP;
    }
    else if(position==out_of_den_position)
    {
        direction=Direction::LEFT;
        out_of_den=true;
    }
    else{
        ;
    }
}
