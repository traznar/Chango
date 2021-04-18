#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "application.c"

#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "C:/Users/Brandon/Desktop/DonkeyC/images/Donkey.png"

static const int width = 800;
static const int height = 600;

int main(int argc, char* args[])
    {
        bool quit = false;
        SDL_Event event;

        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_JPG);

        SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
                                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Surface * image = IMG_Load("Donkey.png");
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

        while (!quit)
        {
            SDL_WaitEvent(&event);

            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }

            //SDL_Rect dstrect = { 5, 5, 320, 240 };
            //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(image);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();

        return 0;
}