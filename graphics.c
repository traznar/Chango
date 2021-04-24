//
// Created by Brandon on 23/4/2021.
//
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <SDL_image.h>
#include <unistd.h>
#include "graphics.h"

void doRender(SDL_Renderer *renderer, GameState *game) {
    //El fondo del window va a hacer azul, esta vara es como
    //agarrar un lapiz de un color para pintar pero aun no ha pintado
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    //Pasa el fonde de pantalla a azul
    SDL_RenderClear(renderer);
    //MIN 0:48
    SDL_Rect donkeyRect = {game->donkeyJr.x,game->donkeyJr.y,50,50};

    SDL_Rect kongRect ={game->kong.x,game->kong.y,72,47};
    SDL_RenderCopy(renderer,game->kong.kongImagen,NULL,&kongRect);

    //Aca se crean y se manda a renderizar las plataformas
    //Se copian y pegan tres porque si se hace con un for, no se posicionan como se quiere
    SDL_Rect plataformaRect ={game->plataformas[0].x,game->plataformas[0].y,150,20};
    SDL_RenderCopy(renderer,game->plataformas[0].plataformaImagen,NULL,&plataformaRect);
    SDL_Rect plataformaRect2 ={game->plataformas[1].x,game->plataformas[1].y,140,20};
    SDL_RenderCopy(renderer,game->plataformas[1].plataformaImagen,NULL,&plataformaRect2);
    SDL_Rect plataformaRect3 ={game->plataformas[2].x,game->plataformas[2].y,140,20};
    SDL_RenderCopy(renderer,game->plataformas[2].plataformaImagen,NULL,&plataformaRect3);
    SDL_Rect plataformaRect4 ={game->plataformas[3].x,game->plataformas[3].y,140,20};
    SDL_RenderCopy(renderer,game->plataformas[3].plataformaImagen,NULL,&plataformaRect4);

    SDL_Rect plataformaRect5 ={game->plataformas[4].x,game->plataformas[4].y,320,20};
    SDL_RenderCopy(renderer,game->plataformas[4].plataformaImagen,NULL,&plataformaRect5);
    SDL_Rect plataformaRect6 ={game->plataformas[5].x,game->plataformas[5].y,240,20};
    SDL_RenderCopy(renderer,game->plataformas[5].plataformaImagen,NULL,&plataformaRect6);
    SDL_Rect plataformaRect7 ={game->plataformas[6].x,game->plataformas[6].y,240,20};
    SDL_RenderCopy(renderer,game->plataformas[6].plataformaImagen,NULL,&plataformaRect7);

    for(int i =0; i<7; i++) {
        SDL_Rect lianaRect = {game->liana[i].x, game->liana[i].y, 6, 120};
        SDL_RenderCopy(renderer, game->liana[i].lianaImagen, NULL, &lianaRect);
    }
    for(int i =7; i<15; i++) {
        SDL_Rect lianaRect2 = {game->liana[i].x, game->liana[i].y, 6, 250};
        SDL_RenderCopy(renderer, game->liana[i].lianaImagen, NULL, &lianaRect2);
    }

    SDL_Rect aguaRect ={game->agua.x,game->agua.y,470,15};
    SDL_RenderCopy(renderer,game->agua.aguaImagen,NULL,&aguaRect);


    SDL_RenderCopy(renderer,game->donkeyJr.donkeyImage,NULL,&donkeyRect);

    SDL_RenderPresent(renderer);

}


void loadGame(GameState *game) {
    SDL_Surface *donkeyImageSurface=NULL; //source pixels of the image
    SDL_Surface *plataformaImageSurface=NULL;
    SDL_Surface *aguaImageSurface=NULL;
    SDL_Surface *lianaImageSurface=NULL;
    SDL_Surface *kongImageSurface=NULL;


    plataformaImageSurface= IMG_Load("plataforma.png");
    donkeyImageSurface= IMG_Load("Donkey.png");
    aguaImageSurface =IMG_Load("agua.png");
    lianaImageSurface =IMG_Load("liana.png");
    kongImageSurface =IMG_Load("kong.png");

    if(donkeyImageSurface ==NULL){
        printf("No se encontro la ruta de la imagen de Donkey.png! \n\n");
        SDL_Quit();
        return ;
    }
    if(plataformaImageSurface ==NULL){
        printf("No se encontro la ruta de la imagen plataforma.png! \n\n");
        SDL_Quit();
        return ;
    }

    game->donkeyJr.x=12;
    game->donkeyJr.y= 555;

    game->plataformas[0].x= 0;
    game->plataformas[0].y=605;

    game->plataformas[1].x= 500;
    game->plataformas[1].y=500;

    game->plataformas[2].x= 40;
    game->plataformas[2].y= 400;

    game->plataformas[3].x= 300;
    game->plataformas[3].y= 300;

    game->plataformas[4].x= 0;
    game->plataformas[4].y= 100;

    game->plataformas[5].x= 420;
    game->plataformas[5].y= 190;

    game->plataformas[6].x= 320;
    game->plataformas[6].y= 0;


    game->agua.x=150;
    game->agua.y=605;

    game->kong.x=0;
    game->kong.y=55;

    game->donkeyJr.donkeyImage = SDL_CreateTextureFromSurface(game->renderer,donkeyImageSurface);
    game->kong.kongImagen =SDL_CreateTextureFromSurface(game->renderer,kongImageSurface);

    for(int i =0; i<7; i++){
        game->liana[i].x= game->plataformas[i].x+20;
        game->liana[i].y= game->plataformas[i].y+20;
    }
    for(int i =7; i<15; i++){
        game->liana[i].x= game->plataformas[i].x+70;
        game->liana[i].y= game->plataformas[i].y;
    }
    for(int i =0; i<7; i++) {
        game->plataformas[i].plataformaImagen=SDL_CreateTextureFromSurface(game->renderer,plataformaImageSurface);
    }
    for(int i =7; i<15; i++) {
        game->plataformas[i].plataformaImagen=SDL_CreateTextureFromSurface(game->renderer,plataformaImageSurface);
    }
    game->agua.aguaImagen=SDL_CreateTextureFromSurface(game->renderer,aguaImageSurface);
    for(int i =0; i<7; i++) {
        game->liana[i].lianaImagen = SDL_CreateTextureFromSurface(game->renderer, lianaImageSurface);
    }
    for(int i =7; i<15; i++) {
        game->liana[i].lianaImagen = SDL_CreateTextureFromSurface(game->renderer, lianaImageSurface);
    }
    SDL_FreeSurface(donkeyImageSurface);
    SDL_FreeSurface(plataformaImageSurface);
    SDL_FreeSurface(aguaImageSurface);
    SDL_FreeSurface(lianaImageSurface);
    SDL_FreeSurface(kongImageSurface);

}

