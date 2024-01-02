#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <stdbool.h>
#include <stdlib.h>
#include "button.c"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
TTF_Font* baseFont; 

SDL_Texture* cube ;

Buttons *buttons;

int w= 512;
int h= 512;

//
SDL_Point mpos = {0,0};
int mx=-1, my=-1;
int running=1;
int t = 0;

int cookies=0;

SDL_Color White = {255, 255, 255};
SDL_Rect texture_rect = {0,0,200,200};
bool KEYS[322];
void quit(){
   SDL_Quit();
   running=0;
}
char msg[256];
void updateCookieCounter(){
   sprintf(msg,"%d Cookies", cookies);
}
void events(){
   SDL_GetMouseState(&mpos.x, &mpos.y);
   SDL_Event e;
   while (SDL_PollEvent(&e)) {
      if (e.type==SDL_KEYDOWN){
         if (e.key.keysym.sym>322){continue;}
         KEYS[e.key.keysym.sym] = true;
      }else if (e.type == SDL_KEYUP){
         if (e.key.keysym.sym>322){continue;}
         KEYS[e.key.keysym.sym] = false;
      }else if (e.type == SDL_MOUSEBUTTONDOWN){
            Button * b = button_Within(buttons, mpos);
            if(b!=NULL){
               cookies++;
               updateCookieCounter();
            }
      }else if (e.type == SDL_QUIT){
         quit();
      }
   }
   if(KEYS[SDLK_q]) {
      quit();  
   }
}

void tick(){
}

SDL_Texture *screenTexture;
SDL_Surface* surfaceMessage;
SDL_Texture* Message;
void render(){
   //arbitrary draw example
   if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
   Uint8 * pixels = surface->pixels;
   for (int i=0; i < w*h*4; i++) {pixels[i] = (i+t) % 255 *(i % 4);}
   if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
   //---
   screenTexture = SDL_CreateTextureFromSurface(renderer, surface);
   surfaceMessage = TTF_RenderText_Blended(baseFont,msg , White);
   Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
   SDL_Rect Message_rect; //create a rect
   Message_rect.x = 100;  //controls the rect's x coordinate 
   Message_rect.y = 100; // controls the rect's y coordinte
   Message_rect.w = 300; // controls the width of the rect
   Message_rect.h = 100; // controls the height of the rect
   TTF_SizeText(baseFont,msg, &Message_rect.w, &Message_rect.h);
   //-
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
   SDL_RenderCopy(renderer, cube, NULL, &texture_rect); 
   SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
   SDL_RenderPresent(renderer);

   SDL_DestroyTexture(screenTexture);
   SDL_DestroyTexture(Message);
}

void mainLoop(){
   events();
   tick();
   render();
   t++;
}

int init (){
   //base sdl--------------
   SDL_Init(SDL_INIT_VIDEO);
   TTF_Init();
   SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer);
   //sdl things------------
   surface = SDL_CreateRGBSurface(0, w , h, 32, 0, 0, 0, 0);
   baseFont = TTF_OpenFont("res/font/PrintedCircuitBoard.ttf", 48);
   cube = IMG_LoadTexture(renderer, "res/cube0001.png");
   //misc------------------
   updateCookieCounter();
   
   for(int i = 0; i < 322; i++){KEYS[i] = false;}
   buttons = buttons_Init();
   SDL_Rect c = {1,1,100,100};
    buttons_Add(buttons,button_New(c));
   return 1;
}

int main(int argc, char* argv[]) {
   if(!init()){
      printf("INIT ERROR\n");
      return 0;
   }
#ifdef __EMSCRIPTEN__
   emscripten_set_main_loop(mainLoop, 0, 1);
#else
   while(running) {        
      mainLoop();
      SDL_Delay(16);
   }
#endif 
}
