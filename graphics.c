//
// Created by Brandon on 23/4/2021.
//
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <unistd.h>
#include "graphics.h"

char str[100];
char str1[100];



void showScore(GameState *game) {
    SDL_Color white= {255,255,255,255};
    sprintf(str,"%d",game->donkeyJr.x);
    sprintf(str1,"%d",game->donkeyJr.y);

    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, strcat(str," <-Puntaje") , white);
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);

    //SDL_Surface *tmp2 = TTF_RenderText_Blended(game->font, strcat(str1," <-Vidas") , white);
    //game->labelvidas =SDL_CreateTextureFromSurface(game->renderer, tmp2);

    SDL_FreeSurface(tmp);
    //SDL_FreeSurface(tmp2);
}


void drawLabel(GameState *game) {
    SDL_Rect textRect = {500, 20 ,120,60};
    SDL_RenderCopy(game->renderer,game->label,NULL, &textRect);

    SDL_Rect vidaRect = {500, 50 ,120,60};
    SDL_RenderCopy(game->renderer,game->labelvidas,NULL, &vidaRect);
}


void destroyLabel(GameState *game) {
    SDL_DestroyTexture(game->label);
    game->label =NULL;
    SDL_DestroyTexture(game->labelvidas);
    game->labelvidas =NULL;
}

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

    SDL_Rect lagartoRect ={game->lagarto[0].x,game->lagarto[0].y,14,32};
    SDL_RenderCopy(renderer,game->lagarto[0].lagartoImagen,NULL,&lagartoRect);
    SDL_Rect lagartoRect1 ={game->lagarto[1].x,game->lagarto[1].y,14,32};
    SDL_RenderCopy(renderer,game->lagarto[1].lagartoImagen,NULL,&lagartoRect1);
    SDL_Rect lagartoRect2 ={game->lagarto[2].x,game->lagarto[2].y,14,32};
    SDL_RenderCopy(renderer,game->lagarto[2].lagartoImagen,NULL,&lagartoRect2);
    SDL_Rect lagartoRect3 ={game->lagarto[3].x,game->lagarto[3].y,14,32};
    SDL_RenderCopy(renderer,game->lagarto[3].lagartoImagen,NULL,&lagartoRect3);
    SDL_Rect lagartoRect4 ={game->lagarto[4].x,game->lagarto[4].y,14,32};
    SDL_RenderCopy(renderer,game->lagarto[4].lagartoImagen,NULL,&lagartoRect4);
    SDL_Rect lagartoRect5 ={game->lagarto[5].x,game->lagarto[5].y,14,32};
    SDL_RenderCopy(renderer,game->lagarto[5].lagartoImagen,NULL,&lagartoRect5);
    SDL_Rect lagartoRect6 ={game->lagarto[6].x,game->lagarto[6].y,14,32};
    SDL_RenderCopy(renderer,game->lagarto[6].lagartoImagen,NULL,&lagartoRect6);
    SDL_Rect lagartoRect7 ={game->lagarto[7].x,game->lagarto[7].y,14,32};
    SDL_RenderCopy(renderer,game->lagarto[7].lagartoImagen,NULL,&lagartoRect7);


    SDL_Rect frutasRect ={game->frutas[0].x,game->frutas[0].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[0].frutasImagen,NULL,&frutasRect);
    SDL_Rect frutasRect1 ={game->frutas[1].x,game->frutas[1].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[1].frutasImagen,NULL,&frutasRect1);
    SDL_Rect frutasRect2 ={game->frutas[2].x,game->frutas[2].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[2].frutasImagen,NULL,&frutasRect2);
    SDL_Rect frutasRect3 ={game->frutas[3].x,game->frutas[3].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[3].frutasImagen,NULL,&frutasRect3);
    SDL_Rect frutasRect4 ={game->frutas[4].x,game->frutas[4].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[4].frutasImagen,NULL,&frutasRect4);
    SDL_Rect frutasRect5 ={game->frutas[5].x,game->frutas[5].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[5].frutasImagen,NULL,&frutasRect5);
    SDL_Rect frutasRect6 ={game->frutas[6].x,game->frutas[6].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[6].frutasImagen,NULL,&frutasRect6);
    SDL_Rect frutasRect7 ={game->frutas[7].x,game->frutas[7].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[7].frutasImagen,NULL,&frutasRect7);
    SDL_Rect frutasRect8 ={game->frutas[8].x,game->frutas[8].y,16,16};
    SDL_RenderCopy(renderer,game->frutas[8].frutasImagen,NULL,&frutasRect8);


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

    showScore(game);
    drawLabel(game);

    SDL_RenderCopy(renderer,game->donkeyJr.donkeyImage,NULL,&donkeyRect);

    SDL_RenderPresent(renderer);

}



/*void crearPlataforma(int posX, int posY, GameState *game, int i) {
    SDL_Rect plataformaRect ={game->plataformas[i].x,game->plataformas[i].y,150,20};
    SDL_RenderCopy(game->renderer,game->plataformas[i].plataformaImagen,NULL,&plataformaRect);
}*/



void cargarPlataforma(GameState *game, int i, int posX, int posY) {
    SDL_Surface *plataformaImageSurface=NULL;
    plataformaImageSurface= IMG_Load("plataforma.png");
    game->plataformas[i].x= posX;
    game->plataformas[i].y= posY;
    game->plataformas[i].plataformaImagen=SDL_CreateTextureFromSurface(game->renderer,plataformaImageSurface);
    SDL_FreeSurface(plataformaImageSurface);
}


void crearCocodrilosAzules(GameState  *game,int i ,int posX, int posY,int type) {
    SDL_Surface *lagartoImageSurface=NULL;
    if(type == 0){
        lagartoImageSurface =IMG_Load("lagarto.png");
    }else{
        lagartoImageSurface =IMG_Load("lagartoRojo.png");
    }
    game->lagarto[i].x=posX;
    game->lagarto[i].y=posY;
    game->lagarto[i].lagartoImagen = SDL_CreateTextureFromSurface(game->renderer,lagartoImageSurface);
    SDL_FreeSurface(lagartoImageSurface);
}
void crearLianas(GameState *game,int posX, int posY) {

}
void crearFrutas(GameState *game,int posX, int posY,int i) {
    SDL_Surface *frutasImageSurface=NULL;
    frutasImageSurface =IMG_Load("banana.png");
    game->frutas[i].x=posX;
    game->frutas[i].y=posY;
    game->frutas[i].frutasImagen= SDL_CreateTextureFromSurface(game->renderer,frutasImageSurface);
    SDL_FreeSurface(frutasImageSurface);
}

void loadGame(GameState *game) {
    SDL_Surface *donkeyImageSurface=NULL; //source pixels of the image
    //SDL_Surface *plataformaImageSurface=NULL;
    SDL_Surface *aguaImageSurface=NULL;
    SDL_Surface *lianaImageSurface=NULL;
    SDL_Surface *kongImageSurface=NULL;
  //  SDL_Surface *lagartoImageSurface=NULL;
  //  SDL_Surface *frutasImageSurface=NULL;



   // plataformaImageSurface= IMG_Load("plataforma.png");
    donkeyImageSurface= IMG_Load("Donkey.png");
    aguaImageSurface =IMG_Load("agua.png");
    lianaImageSurface =IMG_Load("liana.png");
    kongImageSurface =IMG_Load("kong.png");
   // lagartoImageSurface =IMG_Load("lagarto.png");
  //  frutasImageSurface = IMG_Load("banana.png");

    if(donkeyImageSurface ==NULL){
        printf("No se encontro la ruta de la imagen de Donkey.png! \n\n");
        SDL_Quit();
        return ;
    }
   /* if(plataformaImageSurface ==NULL){
        printf("No se encontro la ruta de la imagen plataforma.png! \n\n");
        SDL_Quit();
        return ;
    }*/
    game->font= TTF_OpenFont("FreeMonoOblique.ttf",48);
    if(!game->font)
    {
        printf("No se encontro el file del font\n\n");
        SDL_Quit();
        exit(1);
    }

    game->donkeyJr.x=12;
    game->donkeyJr.y= 555;
/*
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
*/

    game->agua.x=150;
    game->agua.y=605;
/*
    game->lagarto[0].x=150;
    game->lagarto[0].y=150;
*/
    game->kong.x=0;
    game->kong.y=55;
/*
    game->frutas[1].x=110;
    game->frutas[1].y=55;
*/
    game->donkeyJr.donkeyImage = SDL_CreateTextureFromSurface(game->renderer,donkeyImageSurface);
    game->kong.kongImagen =SDL_CreateTextureFromSurface(game->renderer,kongImageSurface);

   // game->frutas[1].frutasImagen = SDL_CreateTextureFromSurface(game->renderer,frutasImageSurface);

  //  game->lagarto[0].lagartoImagen = SDL_CreateTextureFromSurface(game->renderer,lagartoImageSurface);

    for(int i =0; i<7; i++){
        game->liana[i].x= game->plataformas[i].x+20;
        game->liana[i].y= game->plataformas[i].y+20;
    }
    for(int i =7; i<15; i++){
        game->liana[i].x= game->plataformas[i].x+70;
        game->liana[i].y= game->plataformas[i].y;
    }
  /*  for(int i =0; i<7; i++) {
        game->plataformas[i].plataformaImagen=SDL_CreateTextureFromSurface(game->renderer,plataformaImageSurface);
    }
    for(int i =7; i<15; i++) {
        game->plataformas[i].plataformaImagen=SDL_CreateTextureFromSurface(game->renderer,plataformaImageSurface);
    }*/
    game->agua.aguaImagen=SDL_CreateTextureFromSurface(game->renderer,aguaImageSurface);
    for(int i =0; i<7; i++) {
        game->liana[i].lianaImagen = SDL_CreateTextureFromSurface(game->renderer, lianaImageSurface);
    }
    for(int i =7; i<15; i++) {
        game->liana[i].lianaImagen = SDL_CreateTextureFromSurface(game->renderer, lianaImageSurface);
    }
    SDL_FreeSurface(donkeyImageSurface);
   // SDL_FreeSurface(plataformaImageSurface);
    SDL_FreeSurface(aguaImageSurface);
    SDL_FreeSurface(lianaImageSurface);
    SDL_FreeSurface(kongImageSurface);
   // SDL_FreeSurface(lagartoImageSurface);
   // SDL_FreeSurface(frutasImageSurface);

}
