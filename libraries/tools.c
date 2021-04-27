


static GameState gameState;
/**
 * @def get a string value from JSON
 * @param json
 * @param key
 * @return  string value
 */
char* getStringFromJson(char *json, char *key ){
    return (cJSON_GetObjectItemCaseSensitive(cJSON_Parse(json), key)->valuestring);
}
/**
 * @def get a int value from JSON
 * @param json
 * @param key
 * @return int value
 */
double getNumberFromJson(char *json, char *key ){
    return (cJSON_GetObjectItemCaseSensitive(cJSON_Parse(json), key)->valuedouble);
}

/**
 * @def update the player state
 * @param posX
 * @param posY
 * @param vidas
 * @param puntaje
 */
void donkeyKongJrUpdater(int posX, int posY,int vidas,int puntaje){
    SDL_Color white= {255,255,255,255};
    char* str1[10];
    char* str [10];
    sprintf(str1,"%d",vidas);
    SDL_Surface *tmp2 = TTF_RenderText_Blended(gameState.font, strcat(str1," <-Vidas") , white);
    gameState.donkeyJr.x=posX;
    gameState.donkeyJr.y=posY;
    gameState.labelvidas =SDL_CreateTextureFromSurface(gameState.renderer, tmp2);
    SDL_FreeSurface(tmp2);
    sprintf(str,"%d",puntaje);
    SDL_Surface *tmp = TTF_RenderText_Blended(gameState.font, strcat(str," <-Puntaje") , white);
    gameState.label = SDL_CreateTextureFromSurface(gameState.renderer, tmp);
    SDL_FreeSurface(tmp);
}

/**
 * @update the Cocodriles state
 * @param posX
 * @param posY
 */
void lagartosUpdater(int posX, int posY){
    printf(" Posicion en X de lagartos : ");
    printf("%i",posX );
    printf(" Posicion en Y de lagartos : ");
    printf("%i",posY );

}
/**
 * @def uptate fruits state
 * @param posX
 * @param posY
 */
void frutasUpdater(int posX, int posY){

}

/**
 * @def process a Json info and call all the renderes for refreshing the game
 * @param Json
 */
void processJson(char *Json){
    char *dataDelJugador=getStringFromJson(Json, "playerData");
    int valorQueQueremosSacar=getNumberFromJson(dataDelJugador, "size");

    char *donkeyData=getStringFromJson(Json, "playerData");
    int donkeyposX=getNumberFromJson(donkeyData, "posX");
    int donkeyposY=getNumberFromJson(donkeyData, "posY");
    int vidas=getNumberFromJson(donkeyData, "vidas");
    int puntaje=getNumberFromJson(donkeyData, "puntuacion");
    donkeyKongJrUpdater(donkeyposX,donkeyposY,vidas,puntaje);


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

    memset( gameState.frutas, NULL , sizeof( 10 ) );
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
}