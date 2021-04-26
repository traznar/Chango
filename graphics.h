//
// Created by Brandon on 23/4/2021.
//

#ifndef DONKEYC_GRAPHICS_H
#define DONKEYC_GRAPHICS_H
#include "SDL_ttf.h"
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
    int x,y;
    SDL_Texture *lagartoImagen;
} Lagarto;
typedef struct {
    int x,y;
    SDL_Texture *frutasImagen;
} Frutas;

typedef struct {
    //Jugadores
    DonkeyJr donkeyJr;
    Plataformas plataformas[7];
    Agua agua;
    Liana liana[15];
    Kong kong;
    SDL_Renderer *renderer;
    SDL_Texture *label;
    SDL_Texture *labelvidas;
    Lagarto lagarto[20];
    Frutas frutas[100];

    TTF_Font *font;
} GameState;
void destroyLabel(GameState *game);
void drawLabel(GameState *game);
void loadGame(GameState *game);
void doRender(SDL_Renderer *renderer, GameState *game);
void showScore(GameState *game);
//void crearPlataforma(int posX, int posY, GameState *game, int i);
void crearCocodrilosAzules(GameState *game,int i,int posX, int posY,int type);
void crearLianas(GameState *game,int posX, int posY);
void crearFrutas(GameState *game,int posX, int posY,int i);
void cargarPlataforma(GameState *game,int i,int posX, int posY);

#endif //DONKEYC_GRAPHICS_H
