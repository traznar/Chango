#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_image.h>
#include "application.c"
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library


#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "C:/Users/Brandon/Desktop/DonkeyC/images/Donkey.png"
#define IP "192.168.18.27"

static const int width = 800;
static const int height = 600;


int initServer(){
    WSADATA wsa;
    SOCKET mySocket;
    struct sockaddr_in server;
    char *message , server_reply[2000];
    int recv_size;

    //Se inicializa winsock
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Cliente iniciado.\n");

    //Se crea el socket esto es pura sintaxis
    if((mySocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        printf("No se pudo crear el socket  : %d" , WSAGetLastError());


    printf("Socket creado.\n");

    //DEFINO LAS VARIABLES DE LA ESTRTUCTURA
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons( 8081 );

    //INTENTO CONECTAR AL SERVER,  CONECTAR MYSOKET A SERVER
    if (connect(mySocket , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
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
    if((recv_size = recv(mySocket , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }

    puts("Reply received\n");
}


int main(int argc, char* args[])
    {

        initServer(); //INICIO EL CLIENTE AQUI ---------------->
        bool quit = false;
        SDL_Event event;

        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_JPG);

        SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
                                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Surface * image = IMG_Load("Donkey.png");
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

        while (!quit)
        {
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

        return 0;
}
