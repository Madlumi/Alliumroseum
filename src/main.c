#include "mutil.h"
#include "mutilSDL.h"

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

SDL_Window *window;SDL_Renderer *renderer;SDL_Surface *surface;

TTF_Font* baseFont; TEXTURE* cube ;
btn_list *buttons;
I w= 512; I h= 512;
//Input
#define keyn 512 
#define mkeyn 24
B KEYS[keyn];
B MKEYS[mkeyn];
POINT mpos = {0,0};

I running=1;I t = 0;

I cookies=0;
C msg[256];

COL White = {255, 255, 255};
RECT texture_rect = {0,0,200,200};

V quit(){SDL_Quit(); running=0;}
V updateCookieCounter(){sprintf(msg,"%d Cookies", cookies);}
TEXTURE* btn_n;TEXTURE* btn_h;TEXTURE* btn_c;TEXTURE* btn_d;
V TMP_Bclick(){cookies++;updateCookieCounter();}
I init (){
   //base sdl--------------
   SDL_Init(SDL_INIT_VIDEO);
   TTF_Init();
   SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer);
   //sdl things------------
   surface = SDL_CreateRGBSurface(0, w , h, 32, 0, 0, 0, 0);
   baseFont = TTF_OpenFont("res/font/PrintedCircuitBoard.ttf", 48);
   cube = IMG_LoadTexture(renderer, "res/cube0001.png");
   btn_n = IMG_LoadTexture(renderer, "res/btn_norm.png");
   btn_h = IMG_LoadTexture(renderer, "res/btn_high.png");
   btn_c = IMG_LoadTexture(renderer, "res/btn_click.png");
   btn_d = IMG_LoadTexture(renderer, "res/btn_dis.png");
   //misc------------------
   updateCookieCounter();
   
   FOR(keyn,{KEYS[i] = false;});
   FOR(mkeyn,{MKEYS[i] = false;});
   buttons = btn_list_new();
   RECT c = {1,1,300,100};
    buttons->add(buttons,btn_new(c,btn_n,btn_h,btn_c,btn_d, TMP_Bclick));
   return 1;
}
V tick(){
   buttons->tick(buttons, mpos, MKEYS[0]);
   if(KEYS[SDLK_q]){quit();}
}
V events(){
   SDL_GetMouseState(&mpos.x, &mpos.y);
   SDL_Event e;
   W(SDL_PollEvent(&e)) {
      if (e.type==SDL_KEYDOWN){if(!IN(e.key.keysym.sym,0,keyn-1)){printf("key: %d\n",e.key.keysym.sym);return;}KEYS[e.key.keysym.sym] = 1;}
      eif (e.type == SDL_KEYUP){if(!IN(e.key.keysym.sym,0,keyn-1)){return;}KEYS[e.key.keysym.sym] = 0;}
      eif (e.type == SDL_MOUSEBUTTONDOWN){MKEYS[0]=1;}
      eif (e.type == SDL_MOUSEBUTTONUP){MKEYS[0]=0;}
      eif (e.type == SDL_QUIT){quit();}
   }
}


SDL_Texture *screenTexture;
SDL_Surface* surfaceMessage;
SDL_Texture* Message;
V render(){
   //arbitrary draw example
   if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
   Uint8 * pixels = surface->pixels;
   for (int i=0; i < w*h*4; i++) {pixels[i] = (i+t) % 255 *(i % 4);}
   if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
   //---
   screenTexture = SDL_CreateTextureFromSurface(renderer, surface);
   surfaceMessage = TTF_RenderText_Blended(baseFont,msg , White);
   Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
   RECT Message_rect; //create a rect
   Message_rect.x = 100;  //controls the rect's x coordinate 
   Message_rect.y = 100; // controls the rect's y coordinte
   Message_rect.w = 300; // controls the width of the rect
   Message_rect.h = 100; // controls the height of the rect
   TTF_SizeText(baseFont,msg, &Message_rect.w, &Message_rect.h);
   //-
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
   SDL_RenderCopy(renderer, cube, NULL, &texture_rect); 
   buttons->draw(buttons, renderer);
   SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
   SDL_RenderPresent(renderer);

   SDL_DestroyTexture(screenTexture);
   SDL_DestroyTexture(Message);
}

V loop(){ events(); tick(); render(); t++; }


I main(int argc, char* argv[]) {
   if(!init()){printf("INIT ERROR\n");return 0;}
#ifdef __EMSCRIPTEN__
   emscripten_set_main_loop(loop, 0, 1);
#else
   W(running){loop(); SDL_Delay(16);}
#endif 
}
