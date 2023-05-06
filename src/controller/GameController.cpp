#include "GameController.h"
#include "model/GameModel.h"
#include "view/GameView.h"
#include "model/Ghost.h"
#include "model/PacMan.h"
#include "model/Character.h"
#include "common/Direction.h"

#include <SDL.h>
#include <iostream>
#include <cmath>

GameController::GameController() : sdl_initialized(false), time_count(0.0f), fright_time_count(0.0f){}

GameController::~GameController() {
    if (sdl_initialized) {
        SDL_Quit();
    }
}

bool GameController::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError() << std::endl;
        return false;
    }
    sdl_initialized = true;
    return true;
}

void GameController::run() {
    if (!sdl_initialized) {
        return;
    }

    GameModel game_model;
    GameView gameView(game_model);

    // Main game loop
    
    //DEBUG
    //int it=0;

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			default: break;
			}
		}

        // Gestion du clavier
        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        Direction input_direction = Direction::NONE;
        if (keys[SDL_SCANCODE_LEFT])
            input_direction = Direction::LEFT;
        if (keys[SDL_SCANCODE_RIGHT])
            input_direction = Direction::RIGHT;
        if (keys[SDL_SCANCODE_UP])
            input_direction = Direction::UP;
        if (keys[SDL_SCANCODE_DOWN])
            input_direction = Direction::DOWN;

        //là dedans y'a move pour tous les persos
        game_model.update(input_direction, time_count, fright_time_count);

        // AFFICHAGE
		gameView.draw();

        //DEBUG
        //SDL_Delay(500);

        //Animation de la mort
        if (game_model.getPacMan().isDead()) {
            for (int death_sprite_num = 0; death_sprite_num < 11; death_sprite_num++) {
                SDL_Event event;
	        	while (!quit && SDL_PollEvent(&event))
	        	{
	        		switch (event.type)
	        		{
	        		case SDL_QUIT:
	        			quit = true;
	        			break;
	        		default: break;
	        		}
	        	}

                // AFFICHAGE
	        	gameView.drawDeathAnimation(death_sprite_num);
                SDL_Delay(100);

                // LIMITE A 60 FPS
                const Uint64 desiredFrameTime = 16; // 60 FPS = 1000 ms -> ~16 ms per frame
                Uint64 currentTime = SDL_GetTicks64();
                Uint64 frameStartTime = currentTime;
                Uint64 elapsedTime = currentTime - frameStartTime;
                if (elapsedTime < desiredFrameTime) {
                    SDL_Delay(static_cast<Uint32>(desiredFrameTime - elapsedTime));
                }
                frameStartTime = SDL_GetTicks64();
            }
            game_model.getPacMan().setIsDead(false);
        }

        // LIMITE A 60 FPS
        const Uint64 desiredFrameTime = 16; // 60 FPS = 1000 ms -> ~16 ms per frame
        Uint64 currentTime = SDL_GetTicks64();
        Uint64 frameStartTime = currentTime;
        Uint64 elapsedTime = currentTime - frameStartTime;
        if (elapsedTime < desiredFrameTime) {
            SDL_Delay(static_cast<Uint32>(desiredFrameTime - elapsedTime));
        }
        frameStartTime = SDL_GetTicks64();

        if(!game_model.getFrightenedBool())
            time_count += 1.0f/60.0f;
        else
            fright_time_count += 1.0f/60.0f;

        if(fright_time_count > 7.1f)
            fright_time_count = 0.0f;

        //DEBUG
        //std::cout << "time_count: " << time_count << std::endl;

        //DEBUG
        //it++;
        //if(it%60==0){
        //    std::cout << "Second fright: " << static_cast<int>(fright_time_count) << std::endl;
        //    it=0;
        //}


	}

}

int GameController::getTimeCount() const
{
    return time_count;
}