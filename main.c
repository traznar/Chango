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
//#define IP "192.168.0.6"
#define IP "192.168.18.27"
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

    sprintf(str1,"%d",vidas);
    SDL_Surface *tmp2 = TTF_RenderText_Blended(gameState.font, strcat(str1," <-Vidas") , white);
    gameState.donkeyJr.x=posX;
    gameState.donkeyJr.y=posY;
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
    donkeyKongJrUpdater(donkeyposX,donkeyposY,vidas);


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
    printf("\n\n\n");
    cJSON *arrayPlat = cJSON_Parse(getStringFromJson(Json, "plataformas"));
    int num = cJSON_GetArraySize(arrayPlat);

    for (int i = 0; i < num; i++) {
        cJSON *elemt;
        elemt = cJSON_GetArrayItem(arrayPlat, i);
        char* text=cJSON_Print(elemt);
        int posX=getNumberFromJson(text,"posX");
        int posY=getNumberFromJson(text,"posY");

        cargarPlataforma(&gameState,i,posX,posY);


    }
    //Creacion de cocodrilos
    cJSON *arrayCoco = cJSON_Parse(getStringFromJson(Json, "cocodrilos"));
    int numero = cJSON_GetArraySize(arrayCoco);

    for (int i = 0; i < numero; i++) {
        cJSON *elemto;
        elemto = cJSON_GetArrayItem(arrayCoco, i);
        char* texto=cJSON_Print(elemto);
        int posX=getNumberFromJson(texto,"posX");
        int posY=getNumberFromJson(texto,"posY");
        int type =getNumberFromJson(texto,"type");
        crearCocodrilosAzules(&gameState,i,posX,posY,type);

    }
    cJSON *arrayLianas = cJSON_Parse(getStringFromJson(Json, "lianas"));
    int numLianas = cJSON_GetArraySize(arrayLianas);

    for (int i = 0; i < numLianas; i++) {
        cJSON *elemto;
        elemto = cJSON_GetArrayItem(arrayLianas, i);
        char* texto=cJSON_Print(elemto);
       // int posX=getNumberFromJson(texto,"posX");
       // int posY=getNumberFromJson(texto,"posY");
       // int type =getNumberFromJson(texto,"type");
    }
    cJSON *arrayFrutas = cJSON_Parse(getStringFromJson(Json, "frutas"));
    int numfrutas = cJSON_GetArraySize(arrayFrutas);

    for (int i = 0; i < numfrutas; i++) {
        cJSON *elemto;
        elemto = cJSON_GetArrayItem(arrayFrutas, i);
        char* texto=cJSON_Print(elemto);
        int posX=getNumberFromJson(texto,"posX");
        int posY=getNumberFromJson(texto,"posY");
        crearFrutas(&gameState,posX,posY,i);
        // int type =getNumberFromJson(texto,"type");


    }
    //Creacion de lianas

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

        char* left;
        left="left";
        makeRequest(FALSE, left);
    }
    if (state[SDL_SCANCODE_D])
    {

        char* right;
        right="rigth";
        makeRequest(FALSE, right);

    }
    if (state[SDL_SCANCODE_W])
    {

        char* up;
        up="up";
        makeRequest(FALSE, up);
    }
    if (state[SDL_SCANCODE_S])
    {

        char* down;
        down="down";
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
