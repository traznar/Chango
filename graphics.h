//
// Created by Brandon on 23/4/2021.
//

#ifndef DONKEYC_GRAPHICS_H
#define DONKEYC_GRAPHICS_H
#include "SDL2\SDL_ttf.h"
typedef struct {
    int x,y;
    int dx,dy;
    short life;
    char *name;
    int animFrame, facingLeft;
    int time;
    SDL_Texture *donkeyImage[4];

} DonkeyJr;
typedef struct {
    int x,y;
    SDL_Texture *plataformaImagen;
} Plataformas;
typedef struct {
    int x,y;
    int animFrame;
    SDL_Texture *aguaImagen[2];
} Agua;
typedef struct {
    int x,y,size;
    SDL_Texture *lianaImagen;
} Liana;
typedef struct {
    int x,y;
    int animFrame;
    int time;
    SDL_Texture *kongImagen[3];
} Kong;
typedef struct {
    int x,y;
    int animFrame;
    SDL_Texture *lagartoImagen[2];
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
    Liana lianas[15];
    Kong kong;
    SDL_Renderer *renderer;
    SDL_Texture *label;
    SDL_Texture *labelvidas;
    Lagarto lagarto[10];
    Frutas frutas[10];

    TTF_Font *font;
} GameState;
void destroyLabel(GameState *game);
void drawLabel(GameState *game);
void loadGame(GameState *game);
void doRender(SDL_Renderer *renderer, GameState *game);
void showScore(GameState *game);
//void crearPlataforma(int posX, int posY, GameState *game, int i);
void crearCocodrilosAzules(GameState *game,int i,int posX, int posY,int type);
void crearLianas(GameState *game,int i,int posX, int posY,int size);
void crearFrutas(GameState *game,int posX, int posY,int i);
void cargarPlataforma(GameState *game,int i,int posX, int posY);

#endif //DONKEYC_GRAPHICS_H
