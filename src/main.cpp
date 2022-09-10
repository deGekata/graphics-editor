#include "..\SDL2\include\SDL2\SDL.h"
#include <iostream> 
#include "vectord_2d.hpp"

int main(int argv, char** args) {

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");
    SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    bool isRunning = true;
    bool invert_coord = true;

    SDL_Event event; 

    CoordSys ss(0, 0, 800, 600);
    CoordSys ss1(0, 0, 800, 600);
    CoordSys ss2(400, 0, 800, 300);
    SDL_Log("s x %d \n", ss.size_.getY());
    SDL_Log("s y %d \n", ss.size_.getY());
    SDL_Log("b x %d \n", ss.base_point_.getY());
    SDL_Log("b y %d \n", ss.base_point_.getY());
    // return 0;
    Vec2D line(400, 300);
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            // printf("lo1");
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                    break;
                }

                if (event.key.keysym.sym == SDLK_CAPSLOCK) {
                    invert_coord = !invert_coord;
                }
                
            default:
                break;
            }
        }


        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
        SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
        SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
        if (invert_coord) {
            ss.drawVec(renderer, ss2, line); 
        } else {
            ss.drawVec(renderer, ss1, line);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

