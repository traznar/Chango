#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "application.c"
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <pthread.h>
#include <unistd.h>

#define MAX_FPS 20
#define IP "192.168.18.27"

static int MAX_ATTEMPTS =5;

/**
 * @def makeRequest realiza una peticion al servidor, el cual le respondera con un Json
 * @param printState : este parametro indica si queremos que se impriman los estados
 * @return  bool : en caso que la peticion fracase, se retorna un false
 */
bool makeRequest(bool printState){
    int state;
    WSADATA wsa;
    SOCKET mySocket;
    bool connected=false;
    struct sockaddr_in server;
    char *message , server_reply[400];
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(IP);
        server.sin_port = htons( 8081 );


    // INICIO WINSOCK------------------------------------------------------------------------------------------>
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        return false;}
    if(printState)printf("@: Cliente iniciado.\n");


    // CREO EL SOCKET------------------------------------------------------------------------------------------>
    if((mySocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
        printf("!!: No se pudo crear el socket  : %d", WSAGetLastError());
        return false;
    }


    //INTENTO CONECTAR AL SERVER------------------------------------------------------------------------------->
    while(!connected){//mientras no me haya logrado conectar
        if(MAX_ATTEMPTS!=0) {//y mis intentos no se hayan acabado
            if (connect(mySocket, (struct sockaddr *) &server, sizeof(server)) < 0) {//intentare conectarme al servidor
                if(printState) puts("buscando...\n");
                MAX_ATTEMPTS--;
            }
            else  connected = true;
        }
        else {if(printState) puts("!!: No se logro realizar la conexion\n"); return false; }
    }if(printState) puts("@: Socket iniciado...");


    //ENVIO LA PETICION---------------------------------------------------------------------------------------->
    message = "request\n\r";   //INTENTO MANDAR UN MENNSAJE  SI SE ENVIA EXITOSAMENTE ESCRIBE DATA SEND, SI NO SEND FAILED Y CIERRA
    if(send(mySocket , message , strlen(message) , 0) < 0){
        puts("!!: envio fallido");
        return false;
    }if(printState)puts("@: Informacion enviada correctamente\n");


    //ANALIZO SI RECIBO UNA RESPUESTA DEL SERVIDOR, LUEGO CIERRO-------------------------------------------------->
    if((state=recv(mySocket , server_reply , 400 , 0)) == SOCKET_ERROR){
        printf("!!: No se recibio respuesta \n!!: Error %i",state);
        return false;
    }
    server_reply[state]='\0';
    if(printState)printf("@: Respuesta obtenida: %s \n", server_reply);
    closesocket(mySocket);
    return true;

}

bool initClient(){
    return makeRequest(true);
}


_Noreturn void* update(){
    while(true){
        makeRequest(false);
        sleep(1/MAX_FPS);
    }
}

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

int processEvents(SDL_Window *window, GameState *game)
{
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if (window){
                    SDL_DestroyWindow(window);
                    window=NULL;
                    done=1;
                }
            }
                break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        done=1;
                        break;
                }
            }
                break;
            case SDL_QUIT:
                done =1;
                break;
        }
    }
    const Uint8 *state =SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
    {
        game->donkeyJr.x -=10;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        game->donkeyJr.x +=10;
    }
    if (state[SDL_SCANCODE_UP])
    {
        game->donkeyJr.y -=10;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        game->donkeyJr.y +=10;

    }
    return done;
}

void doRender(SDL_Renderer *renderer, GameState *game)
{
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
void loadGame(GameState *game)
{
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

void initCanvas(){
    GameState gameState;
    SDL_Window  *window=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Init(SDL_INIT_VIDEO);
    window=SDL_CreateWindow("CHANGO Jr",
                            SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED
            ,620,620,0);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameState.renderer= renderer;
    loadGame(&gameState);
    int done=0;

    while(!done)
    {
        done=processEvents(window, &gameState);
        doRender(renderer,&gameState);
    }
    SDL_DestroyTexture(gameState.donkeyJr.donkeyImage);
    SDL_DestroyTexture(gameState.liana->lianaImagen);
    SDL_DestroyTexture(gameState.agua.aguaImagen);
    SDL_DestroyTexture(gameState.plataformas->plataformaImagen);
    SDL_DestroyTexture(gameState.kong.kongImagen);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main(int argc, char* args[]){
    //MENSAJE DE INICIO
    initCanvas();
   // bool connect= initClient();
    //CONEXION POSTERIOR
    /*if(connect){
        pthread_t thread_Update;
        pthread_create(&thread_Update, NULL, update, NULL);
        pthread_join(thread_Update, NULL);
    }*/
    return 0;
}
