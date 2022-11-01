#include <SDL.h>
#include <iostream>
#include <stdio.h>

class Screen {

public:

   const static int SCREEN_WIDTH = 600;
   const static int SCREEN_HEIGHT = 600;

   const static int Width = SCREEN_WIDTH /2;
   const static int Height = SCREEN_HEIGHT /2;

public:

       SDL_Window *window;
       SDL_Renderer *renderer;
       SDL_Texture *texture;
       Uint32 *buffer;
       Uint32 *buffer1;

public:

     Screen();
     bool init();
     void screenUpdate();
     bool processEvents();
     void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
     void close();
     void clear();
     void boxBlur();


};

Screen::Screen() {

    window= NULL;
    renderer = NULL;
    texture = NULL;
    buffer=NULL;

}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){


    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {return;} 

      Uint32 color = 0;

      color += red;
      color <<= 8;
      color += green;
      color <<= 8;
      color += blue;
      color <<=8;
      
      
      buffer [(y*SCREEN_WIDTH)+x] = color;
}


void Screen::screenUpdate() {
     
    SDL_UpdateTexture (texture, NULL, buffer, SCREEN_WIDTH*sizeof(Uint32));
    SDL_RenderClear(renderer); 
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

}

void Screen::boxBlur()
{
    Uint32 *temp = buffer;
    buffer = buffer1;
    buffer1 = temp;

    for (int y = 0; y < SCREEN_HEIGHT; y++){
        
        
        for (int x = 0; x < SCREEN_WIDTH; x++){

                    int totalRed = 0;
                    int totalGreen = 0;
                    int totalBlue = 0;
                    
                    
                    for (int row =-1; row <= 1; row++){
                        for (int col = -1; col <= 1; col++){
                           
                           int currentX = x + col;
                           int currentY = y + row;
                           if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT){
                                
                                Uint32 color = buffer1[currentY * currentX];

                                Uint8 red = color >> 24;
                                Uint8 green = color >> 16;
                                Uint8 blue = color >> 8;
                                totalRed += red;
                                totalBlue += blue;
                                totalGreen += green;
                           
                           }
                        }
                    }
                Uint8 red = totalRed;
                Uint8 green = totalGreen;
                Uint8 blue = totalBlue;

                setPixel(x,y,red,green,blue);


        }
    }
}

bool Screen::init(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }
    SDL_Window *window = SDL_CreateWindow("particle fire explosion", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);


    if (window == NULL){
        SDL_Quit();
        return false;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *texture = SDL_CreateTexture (renderer,SDL_PIXELFORMAT_RGB888,SDL_TEXTUREACCESS_STATIC,SCREEN_WIDTH,SCREEN_HEIGHT);
    if (renderer == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (texture == NULL){
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    Uint32 *buffer = new Uint32[SCREEN_HEIGHT*SCREEN_WIDTH];

    SDL_memset(buffer, 0,SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));

    for (int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++ )
    {
       buffer[i] = 0xFFFF00;
    }



    return true;

}
void Screen::clear(){
    SDL_memset(buffer, 0,SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));
}
bool Screen::processEvents()

{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
            if(event.type == SDL_QUIT){
                return false;
            }
            
    }
    return true;


}

void Screen::close() {
    delete [] buffer;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}