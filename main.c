#include <stdio.h>
#include "Game.c"

#define IP "192.168.0.6"
//#define IP "192.168.18.27"
//#define IP "192.168.0.15"

static char UserIp[20]=IP;
static char User[20];

int main(int argc, char* args[]){

    //printf("Enter Ip: ");
    //scanf("%s", UserIp);
    //printf("Introduzca el tipo de usuario (observador,jugador): ");
    //scanf("%s", User);
    bool connect= initClient();
    if(connect){
        pthread_t thread_Update;
        pthread_create(&thread_Update, NULL, update, NULL);
        pthread_join(thread_Update, NULL);
    }
    return 0;
}
