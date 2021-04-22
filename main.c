#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "application.c"
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <pthread.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_FPS 1
#define IMG_PATH "C:/Users/Brandon/Desktop/DonkeyC/images/Donkey.png"
#define IP "192.168.18.27"

static int MAX_ATTEMPTS =5;
static const int width = 800;
static const int height = 600;


bool initClient(){
    WSADATA wsa;
    SOCKET mySocket;
    struct sockaddr_in server;
    char *message , server_reply[2000];

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        return false;
    }
    printf("Cliente iniciado.\n");

    //Se crea el socket esto es pura sintaxis
    if((mySocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
        printf("No se pudo crear el socket  : %d", WSAGetLastError());
        return false;
    }

    //DEFINO LAS VARIABLES DE LA ESTRTUCTURA
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons( 8081 );

    //INTENTO CONECTAR AL SERVER,  CONECTAR MYSOKET A SERVER
    bool connected=false;
    while(!connected){
        if(MAX_ATTEMPTS!=0) {
            if (connect(mySocket, (struct sockaddr *) &server, sizeof(server)) < 0) {
                puts("buscando...\n");
                MAX_ATTEMPTS--;
            }

            else  connected = true;
        }
        else { printf("No se logro realizar la conexion\n"); return false; }
    }

    puts("Connected");

    //INTENTO MANDAR UN MENNSAJE  SI SE ENVIA EXITOSAMENTE ESCRIBE DATA SEND, SI NO SEND FAILED Y CIERRA
    message = "Holaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n\r";
    if(send(mySocket , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");

    //ANALIZO SI RECIBO UNA RESPUESTA DEL SERVIDOR
    if((recv(mySocket , server_reply , 2000 , 0)) == SOCKET_ERROR)
        puts("recv failed");
    else{
        puts("Reply received\n");
        return true;
    }
}




_Noreturn void* update(void *args){
    while(true){
        printf("NieRAutomata\n");
        sleep(1/MAX_FPS);
    }
}

void initCanvas(void *args){
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = IMG_Load("Donkey.png");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    while (!quit){
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }

        //SDL_Rect dstrect = { 5, 5, 320, 240 };
        //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]){
    //se inicia el servidor
    bool connect= initClient();
    //si logro conectarme inicio un hilo de repeticion a una frecuencia dada
    if(connect){
        pthread_t thread_Update;
        pthread_create(&thread_Update, NULL, update, NULL);
        pthread_join(thread_Update, NULL);
    }

    return 0;
}
/**
 * P1 se inicia el servidor
 * P2 si logro establecer una conexion inicio un hilo con 30 a 60 fps
 * P3 en cada frame actualizo mando un mensaje al servidor, luego actualizo el canvas
 * P4 de paso si tengo una tecla presionada la mando
 */