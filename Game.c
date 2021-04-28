
#include "Sockets.c"
#define MAX_FPS 20
static SDL_Window  *window=NULL;
static SDL_Renderer *renderer=NULL;
bool initClient(){
    return makeRequest(true,"request\n\r");
}
/**
 * @def process inputs events like the buttom input
 * @param window
 * @param window: the window is rendered, game: the gamestate
 * @return int event caching
 */
int processEvents(SDL_Window *window, GameState *game){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_WINDOWEVENT_CLOSE:{
                if (window){
                    SDL_DestroyWindow(window);
                    window=NULL;
                    done=1;
                }
            }
                break;
            case SDL_KEYDOWN:{
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
    if (state[SDL_SCANCODE_A]){
        char* left;
        left="left";
        makeRequest(FALSE, left);
    }
    if (state[SDL_SCANCODE_D]){
        char* right;
        right="rigth";
        makeRequest(FALSE, right);
    }
    if (state[SDL_SCANCODE_W]){
        char* up;
        up="up";
        makeRequest(FALSE, up);
    }
    if (state[SDL_SCANCODE_S]){
        char* down;
        down="down";
        makeRequest(FALSE, down);
    }
    return done;
}
/**
 * @def initCanvas intializes the canvas when the game is open
 * @return
 */
void initCanvas(){
    SDL_Init(SDL_INIT_VIDEO);
    window=SDL_CreateWindow("CHANGO Jr",
                            SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED
            ,620,620,0);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameState.renderer= renderer;
    TTF_Init();
    loadGame(&gameState);


}
/**
 * @def Update is executed every frame infinitely  until the game is closed
 * it make server request, process inputs events and refresh the canvas when the Json arrives
 * @return
 */
void* update(){
    initCanvas();
    int done=0;
    char* fpc;
    fpc= "request\n\r";
    while(!done){

        makeRequest(false,fpc);
        done=processEvents(window, &gameState);
        doRender(renderer,&gameState);

        usleep(1000000/MAX_FPS);

    }
    SDL_DestroyTexture(gameState.donkeyJr.donkeyImage);
    SDL_DestroyTexture(gameState.lianas->lianaImagen);
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