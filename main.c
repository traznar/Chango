#include <stdio.h>
#include "Game.c"

//#define IP "192.168.0.6"
//#define IP "192.168.18.27"
static char UserIp[20]="192.168.18.27";


int main(int argc, char* args[]){

    //printf("Enter Ip: ");
    //scanf("%s", UserIp);
    bool connect= initClient();
   if(connect){
        pthread_t thread_Update;
        pthread_create(&thread_Update, NULL, update, NULL);
        pthread_join(thread_Update, NULL);
    }
    return 0;
}
