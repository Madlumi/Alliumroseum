#include <SDL2/SDL.h>
#include "mutil.h"
#include "mutilSDL.h"
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef BUTTON
#define BUTTON
typedef struct {
   SDL_Rect r;

}btn;
typedef struct {
   I i;
   I size;
   btn * btns;


} btn_list;

btn *btn_New(SDL_Rect r){
   btn *b = malloc(sizeof(btn));
   b->r=r;
   return b;
}
void btns_Add(btn_list * b,btn *butt){
   b->btns[b->i]=*butt;
   b->i++;
}
void btns_Free(btn_list * b){
}
btn * btn_Within(btn_list * b,SDL_Point p){
   for(int i = 0; i < b->i; i++) {
      if(SDL_PointInRect(&p, &b->btns[i].r)){
        return &b->btns[i]; 
      }
   }
   return NULL;
}
btn_list * btns_Init(){
   btn_list * b= malloc(sizeof(btn_list));
   b->i=0;
   b->size=10;
   b->btns= malloc(sizeof(btn)*b->size);
   return b;
}
#endif
