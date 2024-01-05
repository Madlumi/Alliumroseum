#include <SDL2/SDL.h>
#include "mutil.h"
#include "mutilSDL.h"
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef _BUTTON
#define _BUTTON
typedef struct {
   SDL_Rect r;
   TEXTURE * tx_norm;
   TEXTURE * tx_click;
   TEXTURE * tx_high;
   TEXTURE * tx_dis;
}btn;
typedef struct _BTN_LIST {
   I i;
   I size;
   btn * btns;
   V (*add)(struct _BTN_LIST *self, btn * b);
   btn * (*in)(struct _BTN_LIST *self, POINT p);
   V (*rm)(struct _BTN_LIST *self, I i);
   V (*free)(struct _BTN_LIST *self);
   V (*draw)(struct _BTN_LIST *self, SDL_Renderer *ren);
} btn_list;

btn *btn_new(SDL_Rect r, TEXTURE * tx_norm, TEXTURE * tx_click,TEXTURE * tx_high,TEXTURE * tx_dis){
   btn *b = malloc(sizeof(btn));
   b->tx_norm=tx_norm;b->tx_click=tx_click;b->tx_high=tx_high;b->tx_dis=tx_dis;
   b->r=r;
   return b;
}
static void _add( struct _BTN_LIST * b,btn *butt){if(b->i<b->size){b->btns[b->i]=*butt;b->i++;};}
static void _rm( struct _BTN_LIST * b, I i){printf("rm not implemented\n"); }
static void _free(btn_list * b){ }
static btn * _in(btn_list * b,POINT p){FOR(b->i, {if(SDL_PointInRect(&p, &b->btns[i].r)){return &b->btns[i]; } }); return NULL;}
static void _draw(btn_list * b, SDL_Renderer *ren){FOR(b->i,{SDL_RenderCopy(ren, b->btns[i].tx_norm, NULL, &b->btns[i].r); })}
btn_list * btn_list_new(){
   btn_list * b= malloc(sizeof(btn_list));
   b->add=_add;b->rm=_rm;b->free=_free;b->in=_in;b->draw=_draw;
   b->i=0;b->size=10;
   b->btns= malloc(sizeof(btn)*b->size);
   return b;
}
#endif
