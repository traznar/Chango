//
// Created by Brandon on 23/4/2021.
//

#ifndef DONKEYC_GRAPHICS_H
#define DONKEYC_GRAPHICS_H


typedef struct {
    int x,y;
    short life;
    char *name;
    SDL_Texture *donkeyImage;
} DonkeyJr;
typedef struct {
    int x,y;
    SDL_Texture *plataformaImagen;
} Plataformas;
typedef struct {
    int x,y;
    SDL_Texture *aguaImagen;
} Agua;

typedef struct {
    int x,y;
    SDL_Texture *lianaImagen;
} Liana;
typedef struct {
    int x,y;
    SDL_Texture *kongImagen;
} Kong;

typedef struct {
    //Jugadores
    DonkeyJr donkeyJr;
    Plataformas plataformas[7];
    Agua agua;
    Liana liana[15];
    Kong kong;
    SDL_Renderer *renderer;
} GameState;

void loadGame(GameState *game);
void doRender(SDL_Renderer *renderer, GameState *game);


#endif //DONKEYC_GRAPHICS_H
