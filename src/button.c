#include <SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef BUTTON
#define BUTTON
typedef struct {
   SDL_Rect r;

}Button;
typedef struct {
   int i;
   int size;
   Button * buttons;
} Buttons;

Button *button_New(SDL_Rect r){
   Button *b = malloc(sizeof(Button));
   b->r=r;
   return b;
}
void buttons_Add(Buttons * b,Button *butt){
   b->buttons[b->i]=*butt;
   b->i++;
}
void buttons_Free(Buttons * b){
}
Button * button_Within(Buttons * b,SDL_Point p){
   for(int i = 0; i < b->i; i++) {
      if(SDL_PointInRect(&p, &b->buttons[i].r)){
        return &b->buttons[i]; 
      }
   }
   return NULL;
}
Buttons * buttons_Init(){
   Buttons * b= malloc(sizeof(Buttons));
   b->i=0;
   b->size=10;
   b->buttons= malloc(sizeof(Button)*b->size);
   return b;
}
#endif
