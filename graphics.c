//
// Created by Brandon on 23/4/2021.
//
#include <stdio.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <unistd.h>
#include "graphics.h"

char str[100];
char str1[100];


/**
 * @def showScore
 * @param game
 */
void showScore(GameState *game) {
    SDL_Color white= {255,255,255,255};
    sprintf(str,"%d",game->donkeyJr.x);
    sprintf(str1,"%d",game->donkeyJr.y);
/*
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, strcat(str," <-Puntaje") , white);
    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);

    //SDL_Surface *tmp2 = TTF_RenderText_Blended(game->font, strcat(str1," <-Vidas") , white);
    //game->labelvidas =SDL_CreateTextureFromSurface(game->renderer, tmp2);

    SDL_FreeSurface(tmp);*/
    //SDL_FreeSurface(tmp2);
}

/**
 * @def render a label in canvas
 * @param game
 */
void drawLabel(GameState *game) {
    SDL_Rect textRect = {500, 20 ,120,60};
    SDL_RenderCopy(game->renderer,game->label,NULL, &textRect);

    SDL_Rect vidaRect = {500, 50 ,120,60};
    SDL_RenderCopy(game->renderer,game->labelvidas,NULL, &vidaRect);
}

/**
 * @ destroy a Label in the gamestate
 * @param game
 */
void destroyLabel(GameState *game) {
    SDL_DestroyTexture(game->label);
    game->label =NULL;
    SDL_DestroyTexture(game->labelvidas);
    game->labelvidas =NULL;
}
/**
 * @def Renderes all elements in the game
 * @param renderer
 * @param game
 */
void doRender(SDL_Renderer *renderer, GameState *game) {
    //El fondo del window va a hacer azul, esta vara es como
    //agarrar un lapiz de un color para pintar pero aun no ha pintado
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    //Pasa el fonde de pantalla a azul
    SDL_RenderClear(renderer);
    //MIN 0:48
    SDL_Rect donkeyRect = {game->donkeyJr.x,game->donkeyJr.y,50,50};

    SDL_Rect kongRect ={game->kong.x,game->kong.y,72,47};
    //SDL_RenderCopy(renderer,game->kong.kongImagen,NULL,&kongRect);

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



    for(int i=0 ;i<9;i++){
        SDL_Rect lagartoRect ={game->lagarto[i].x,game->lagarto[i].y,14,32};
        SDL_RenderCopyEx(renderer,game->lagarto[i].lagartoImagen[game->lagarto->animFrame],
                         NULL,&lagartoRect,0,NULL,1);

        //SDL_RenderCopy(renderer,game->lagarto[i].lagartoImagen,NULL,&lagartoRect);
    }
    for(int i=0 ;i<9;i++){
        SDL_Rect frutasRect ={game->frutas[i].x,game->frutas[i].y,16,16};
        SDL_RenderCopy(renderer,game->frutas[i].frutasImagen,NULL,&frutasRect);
    }
    for(int i =0; i<7; i++) {
        SDL_Rect lianaRect = {game->lianas[i].x, game->lianas[i].y, 6, game->lianas[i].size};
        SDL_RenderCopy(renderer, game->lianas[i].lianaImagen, NULL, &lianaRect);
    }
    for(int i =7; i<15; i++) {
        SDL_Rect lianaRect2 = {game->lianas[i].x, game->lianas[i].y, 6, 250};
        SDL_RenderCopy(renderer, game->lianas[i].lianaImagen, NULL, &lianaRect2);

    }

    SDL_Rect aguaRect ={game->agua.x,game->agua.y,620,15};
    //SDL_RenderCopy(renderer,game->agua.aguaImagen,NULL,&aguaRect);
    SDL_RenderCopyEx(renderer,game->agua.aguaImagen[game->agua.animFrame],
                     NULL,&aguaRect,0,NULL,1);
    showScore(game);
    drawLabel(game);

    // SDL_RenderCopy(renderer,game->donkeyJr.donkeyImage,NULL,&donkeyRect);
    SDL_RenderCopyEx(renderer,game->donkeyJr.donkeyImage[game->donkeyJr.animFrame],
                     NULL,&donkeyRect,0,NULL,(game->donkeyJr.facingLeft==0));
    SDL_RenderCopyEx(renderer,game->kong.kongImagen[game->kong.animFrame],
                     NULL,&kongRect,0,NULL,(game->donkeyJr.facingLeft==0));

    SDL_RenderPresent(renderer);


}




void cargarPlataforma(GameState *game, int i, int posX, int posY) {
    SDL_Surface *plataformaImageSurface=NULL;
    plataformaImageSurface= IMG_Load("plataforma.jpg");
    game->plataformas[i].x= posX;
    game->plataformas[i].y= posY;
    game->plataformas[i].plataformaImagen=SDL_CreateTextureFromSurface(game->renderer,plataformaImageSurface);
    SDL_FreeSurface(plataformaImageSurface);
}



void crearCocodrilosAzules(GameState  *game,int i ,int posX, int posY,int type) {
    SDL_Surface *lagartoImageSurface=NULL;
    if(type == 0){
        lagartoImageSurface =IMG_Load("lagarto1.jpg");
    }else{
        lagartoImageSurface =IMG_Load("lagartoRojo.jpg");
    }
    game->lagarto[i].x=posX;
    game->lagarto[i].y=posY;
    game->lagarto[i].lagartoImagen[0] = SDL_CreateTextureFromSurface(game->renderer,lagartoImageSurface);
    SDL_FreeSurface(lagartoImageSurface);

    if(type == 0){
        lagartoImageSurface =IMG_Load("lagarto2.jpg");
    }else{
        lagartoImageSurface =IMG_Load("lagartoRojo2.jpg");
    }
    game->lagarto[i].x=posX;
    game->lagarto[i].y=posY;
    game->lagarto[i].lagartoImagen[1] = SDL_CreateTextureFromSurface(game->renderer,lagartoImageSurface);
    SDL_FreeSurface(lagartoImageSurface);
}
void crearLianas(GameState *game,int i,int posX, int posY, int size) {
    SDL_Surface *plataformaImageSurface=NULL;
    plataformaImageSurface= IMG_Load("liana.jpg");
    game->lianas[i].x= posX;
    game->lianas[i].y= posY;
    game->lianas[i].size= size;
    game->lianas[i].lianaImagen=SDL_CreateTextureFromSurface(game->renderer,plataformaImageSurface);
    SDL_FreeSurface(plataformaImageSurface);
}
void crearFrutas(GameState *game,int posX, int posY,int i) {
    SDL_Surface *frutasImageSurface=NULL;
    frutasImageSurface =IMG_Load("banana.jpg");
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



    donkeyImageSurface= IMG_Load("1.jpg");
    game->donkeyJr.donkeyImage[0]=SDL_CreateTextureFromSurface(game->renderer,donkeyImageSurface);
    SDL_FreeSurface(donkeyImageSurface);

    donkeyImageSurface= IMG_Load("2.jpg");
    game->donkeyJr.donkeyImage[1]=SDL_CreateTextureFromSurface(game->renderer,donkeyImageSurface);
    SDL_FreeSurface(donkeyImageSurface);

    donkeyImageSurface= IMG_Load("3.jpg");
    game->donkeyJr.donkeyImage[2]=SDL_CreateTextureFromSurface(game->renderer,donkeyImageSurface);
    SDL_FreeSurface(donkeyImageSurface);

    //aguaImageSurface =IMG_Load("agua.jpg");
    lianaImageSurface =IMG_Load("lianas.jpg");
    //kongImageSurface =IMG_Load("kong.jpg");

    donkeyImageSurface= IMG_Load("4.jpg");
    game->donkeyJr.donkeyImage[3]=SDL_CreateTextureFromSurface(game->renderer,donkeyImageSurface);
    SDL_FreeSurface(donkeyImageSurface);

    //aguaImageSurface =IMG_Load("agua.jpg");
    lianaImageSurface =IMG_Load("liana.jpg");

    aguaImageSurface =IMG_Load("agua.jpg");
    game->agua.aguaImagen[0]=SDL_CreateTextureFromSurface(game->renderer,aguaImageSurface);
    SDL_FreeSurface(aguaImageSurface);
    aguaImageSurface =IMG_Load("agua2.jpg");
    game->agua.aguaImagen[1]=SDL_CreateTextureFromSurface(game->renderer,aguaImageSurface);
    SDL_FreeSurface(aguaImageSurface);

    kongImageSurface =IMG_Load("kong1.jpg");
    game->kong.kongImagen[0]=SDL_CreateTextureFromSurface(game->renderer,kongImageSurface);
    SDL_FreeSurface(kongImageSurface);
    kongImageSurface =IMG_Load("kong2.jpg");
    game->kong.kongImagen[1]=SDL_CreateTextureFromSurface(game->renderer,kongImageSurface);
    SDL_FreeSurface(kongImageSurface);
    kongImageSurface =IMG_Load("kong3.jpg");
    game->kong.kongImagen[2]=SDL_CreateTextureFromSurface(game->renderer,kongImageSurface);
    SDL_FreeSurface(kongImageSurface);

    if(donkeyImageSurface ==NULL){
        printf("No se encontro la ruta de la imagen de Donkey.png! \n\n");
        SDL_Quit();
        return ;
    }

    game->font= TTF_OpenFont("FreeMonoOblique.ttf",48);
    if(!game->font)
    {
        printf("No se encontro el file del font\n\n");
        SDL_Quit();
        exit(1);
    }

    game->agua.x=0;
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
   // game->donkeyJr.donkeyImage = SDL_CreateTextureFromSurface(game->renderer,donkeyImageSurface);
   // game->kong.kongImagen =SDL_CreateTextureFromSurface(game->renderer,kongImageSurface);

   // game->frutas[1].frutasImagen = SDL_CreateTextureFromSurface(game->renderer,frutasImageSurface);

  //  game->lagarto[0].lagartoImagen = SDL_CreateTextureFromSurface(game->renderer,lagartoImageSurface);



    //game->agua.aguaImagen=SDL_CreateTextureFromSurface(game->renderer,aguaImageSurface);


    //SDL_FreeSurface(donkeyImageSurface);
   // SDL_FreeSurface(plataformaImageSurface);
    //SDL_FreeSurface(aguaImageSurface);
    SDL_FreeSurface(lianaImageSurface);
    //SDL_FreeSurface(kongImageSurface);
   // SDL_FreeSurface(lagartoImageSurface);
   // SDL_FreeSurface(frutasImageSurface);

}
