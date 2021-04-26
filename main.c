#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <pthread.h>

#include "usleep.h"

#include "graphics.h"
#include "cJSON.h"
#include "cJSON.c"

#define MAX_FPS 20
#define IP "192.168.0.6"
//#define IP "192.168.18.27"
static int MAX_ATTEMPTS =5;
static GameState gameState;
static SDL_Window  *window=NULL;
static SDL_Renderer *renderer=NULL;
char* str1[100];





char* getStringFromJson(char *json, char *key ){
    return (cJSON_GetObjectItemCaseSensitive(cJSON_Parse(json), key)->valuestring);
}
double getNumberFromJson(char *json, char *key ){
    return (cJSON_GetObjectItemCaseSensitive(cJSON_Parse(json), key)->valuedouble);
}
void donkeyKongJrUpdater(int posX, int posY,int vidas){
    SDL_Color white= {255,255,255,255};
    printf(" Posicion en X de donkeyJR : ");
    printf("%i",posX);
    printf(" Posicion en Y de donkeyJR : ");
    printf("%i",posY);
    printf(" Vidas de donkeyJR : ");
    printf("%i",vidas);
    sprintf(str1,"%d",vidas);
    SDL_Surface *tmp2 = TTF_RenderText_Blended(gameState.font, strcat(str1," <-Vidas") , white);
    gameState.labelvidas =SDL_CreateTextureFromSurface(gameState.renderer, tmp2);
    SDL_FreeSurface(tmp2);

}
void lagartosUpdater(int posX, int posY){
    printf(" Posicion en X de lagartos : ");
    printf("%i",posX );
    printf(" Posicion en Y de lagartos : ");
    printf("%i",posY );


}
void frutasUpdater(int posX, int posY){

}

/**
 * @def makeRequest realiza una peticion al servidor, el cual le respondera con un Json
 * @param printState : este parametro indica si queremos que se impriman los estados
 * @return  bool : en caso que la peticion fracase, se retorna un false
 */
bool makeRequest(bool printState,char* message){
    int state;
    WSADATA wsa;
    SOCKET mySocket;
    bool connected=false;
    struct sockaddr_in server;
    char server_reply[6000];
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
    //message = "request";   //INTENTO MANDAR UN MENNSAJE  SI SE ENVIA EXITOSAMENTE ESCRIBE DATA SEND, SI NO SEND FAILED Y CIERRA
    if(send(mySocket , message , strlen(message) , 0) < 0){
        puts("!!: envio fallido");
        return false;
    }if(printState)puts("@: Informacion enviada correctamente\n");


    //ANALIZO SI RECIBO UNA RESPUESTA DEL SERVIDOR, LUEGO CIERRO-------------------------------------------------->
    if((state=recv(mySocket , server_reply , 6000 , 0)) == SOCKET_ERROR){//guarda la respuesta en server_reply[state]
        printf("!!: No se recibio respuesta \n!!: Error %i",state);
        return false;
    }
    server_reply[state]='\0';
    if(printState)printf("@: Respuesta obtenida: %s \n", server_reply);

    char *Json = cJSON_Print(cJSON_Parse(server_reply));
    char *dataDelJugador=getStringFromJson(Json, "playerData");
    int valorQueQueremosSacar=getNumberFromJson(dataDelJugador, "size");

    char *donkeyData=getStringFromJson(Json, "playerData");
    int donkeyposX=getNumberFromJson(donkeyData, "posX");
    int donkeyposY=getNumberFromJson(donkeyData, "posY");
    int vidas=getNumberFromJson(donkeyData, "vidas");

    //char *lagartosData=getStringFromJson(Json, "cocodrilos");
    //printf("\n");
    //printf("===========================================>");
   // printf("%s", lagartosData);
   // char* data2= getStringFromJson(lagartosData,"posX");
    //int lagartoX=getNumberFromJson(lagartosData, "posX");
    //int lagartoY=getNumberFromJson(lagartosData, "posY");

    //printf(data2);
    donkeyKongJrUpdater(donkeyposX,donkeyposY,vidas);
    //lagartosUpdater(lagartoX,lagartoY);
    /**
    printf(Json);
    printf("\n\n\n");
    printf(dataDelJugador);
    printf("\n\n\n");
    printf("%i",valorQueQueremosSacar );
    printf("\n\n\n");
    */
    //===============================Ejemplo de Arrays===========================>
    /*printf("\n\n\n");
    cJSON *array = cJSON_Parse(getStringFromJson(Json, "plataformas"));
    int n = cJSON_GetArraySize(array);
    for (int i = 0; i < n; i++) {
        cJSON *elem;
        elem = cJSON_GetArrayItem(array, i);
        char* text=cJSON_Print(elem);
        printf(text);
    }*/
    //===============================Ejemplo de Arrays===========================>
    //Llamando a creacion de plataformas
    printf("\n\n\n");
    cJSON *arrayPlat = cJSON_Parse(getStringFromJson(Json, "plataformas"));
    int num = cJSON_GetArraySize(arrayPlat);

    for (int i = 0; i < num; i++) {
        cJSON *elemt;
        elemt = cJSON_GetArrayItem(arrayPlat, i);
        char* text=cJSON_Print(elemt);
        printf(text);
        int posX=getNumberFromJson(text,"posX");
        int posY=getNumberFromJson(text,"posY");

        cargarPlataforma(&gameState,i,posX,posY);
       // crearPlataforma(posX,posY,&gameState,i);

    }
    closesocket(mySocket);
    return true;
}

bool initClient(){
    return makeRequest(true,"request\n\r");
}




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
    if (state[SDL_SCANCODE_A])
    {
        if(0<game->donkeyJr.x) {
            game->donkeyJr.x -= 10;
        }
        char* left;
        left="left\n\r";
        makeRequest(FALSE, left);
    }
    if (state[SDL_SCANCODE_D])
    {
        if(572>game->donkeyJr.x) {

            game->donkeyJr.x += 10;
        }
        char* right;
        right="rigth\n\r";
        makeRequest(FALSE, right);

    }
    if (state[SDL_SCANCODE_W])
    {
        if(5<game->donkeyJr.y){
            game->donkeyJr.y -= 10;
        }
        char* up;
        up="up\n\r";
        makeRequest(FALSE, up);
    }
    if (state[SDL_SCANCODE_S])
    {
        if(565>game->donkeyJr.y) {
            game->donkeyJr.y += 10;
        }
        char* down;
        down="down\n\r";
        makeRequest(FALSE, down);

    }
    return done;
}

void initCanvas(){


    SDL_Init(SDL_INIT_VIDEO);
    window=SDL_CreateWindow("CHANGO Jr",
                            SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED
            ,620,620,0);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameState.renderer= renderer;
    TTF_Init();
    loadGame(&gameState);


    /* while(!done)
     {
         done=processEvents(window, &gameState);
         doRender(renderer,&gameState);
     }*/

}
void* update(){
    initCanvas();
    int done=0;
    char* fpc;
    fpc= "se va a morir\n\r";
    while(!done){

        //makeRequest(true,fpc);

        done=processEvents(window, &gameState);
        doRender(renderer,&gameState);

        usleep(1000000/MAX_FPS);

    }
    SDL_DestroyTexture(gameState.donkeyJr.donkeyImage);
    SDL_DestroyTexture(gameState.liana->lianaImagen);
    SDL_DestroyTexture(gameState.agua.aguaImagen);
    SDL_DestroyTexture(gameState.plataformas->plataformaImagen);
    SDL_DestroyTexture(gameState.kong.kongImagen);
    SDL_DestroyTexture(gameState.frutas->frutasImagen);
    destroyLabel(&gameState);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}



int main(int argc, char* args[]){
    //MENSAJE DE INI

    bool connect= initClient();
    //CONEXION POSTERIOR

   if(connect){
        pthread_t thread_Update;
        pthread_create(&thread_Update, NULL, update, NULL);
        pthread_join(thread_Update, NULL);
    }
    return 0;
}
