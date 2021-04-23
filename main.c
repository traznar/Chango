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
    //Jugadores

    DonkeyJr donkeyJr;


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
    SDL_SetRenderDrawColor(renderer,0,0,255,255);
    //Pasa el fonde de pantalla a azul
    SDL_RenderClear(renderer);
    //MIN 0:48
    SDL_Rect donkeyRect = {game->donkeyJr.x,game->donkeyJr.y,80,80};
    SDL_RenderCopy(renderer,game->donkeyJr.donkeyImage,NULL,&donkeyRect);
    SDL_RenderPresent(renderer);

}

void initCanvas(){
    GameState gameState;
    SDL_Window  *window=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Surface *donkeyImageSurface=NULL; //source pixels of the image


    SDL_Init(SDL_INIT_VIDEO);
    gameState.donkeyJr.x=320-40;
    gameState.donkeyJr.y= 240-40;

    window=SDL_CreateWindow("CHANGO Jr",
                            SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED
            ,720,680,0);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    donkeyImageSurface= IMG_Load("Donkey.png");
    if(donkeyImageSurface ==NULL){
        printf("No se encontro la ruta de la imagen! \n\n");
        SDL_Quit();
        return ;
    }
    gameState.donkeyJr.donkeyImage = SDL_CreateTextureFromSurface(renderer,donkeyImageSurface);
    SDL_FreeSurface(donkeyImageSurface);
    int done=0;

    while(!done)
    {
        done=processEvents(window, &gameState);
        doRender(renderer,&gameState);
    }
    SDL_DestroyTexture(gameState.donkeyJr.donkeyImage);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main(int argc, char* args[]){
    //MENSAJE DE INICIO
    bool connect= initClient();
    //CONEXION POSTERIOR
    if(connect){
        pthread_t thread_Update;
        pthread_create(&thread_Update, NULL, update, NULL);
        pthread_join(thread_Update, NULL);
    }
    return 0;
}
