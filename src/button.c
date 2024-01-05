#include <SDL2/SDL.h>
#include "mutil.h"
#include "mutilSDL.h"
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef _BUTTON
#define _BUTTON
enum BTN_STATUS{NORM, HOVER, DISABLED, CLICK};
typedef struct _BTN{
   SDL_Rect r;
   enum BTN_STATUS st;
   TEXTURE * tx_norm;TEXTURE * tx_click;TEXTURE * tx_high;TEXTURE * tx_dis;
   V (* onclick)();
   V (* enable)(struct _BTN * b, B en);
}btn;
typedef struct _BTN_LIST {
   I i;   I size;   btn * btns;
   V (*add)(struct _BTN_LIST *self, btn * b);btn * (*in)(struct _BTN_LIST *self, POINT p);
   V (*rm)(struct _BTN_LIST *self, I i); V (*free)(struct _BTN_LIST *self);
   V (*draw)(struct _BTN_LIST *self, SDL_Renderer *ren);V (*tick)(struct _BTN_LIST *self, POINT mp, I down);
} btn_list;
static V _enable(btn * b,B en){b->st= en ? NORM : DISABLED; }
static V _add( struct _BTN_LIST * b,btn *butt){if(b->i<b->size){b->btns[b->i]=*butt;b->i++;};}
static V _rm( struct _BTN_LIST * b, I i){printf("rm not implemented\n"); }
static V _free(btn_list * b){ }
static btn * _in(btn_list * b,POINT p){FOR(b->i, {if(SDL_PointInRect(&p, &b->btns[i].r)){return &b->btns[i]; } }); return NULL;}
static V _draw(btn_list * b, SDL_Renderer *ren){FOR(b->i,{
   TEXTURE * t; 
   SW(b->btns[i].st){CA(NORM,t=b->btns[i].tx_norm);CA(HOVER,t=b->btns[i].tx_high);CA(CLICK,t=b->btns[i].tx_click);CA(DISABLED,t=b->btns[i].tx_dis);}
   SDL_RenderCopy(ren, t, NULL, &b->btns[i].r);})}
static void _tick(btn_list * b, POINT mp, I down){FOR(b->i,{ if(b->btns[i].st==DISABLED){continue;}
   if(!SDL_PointInRect(&mp, &b->btns[i].r)){b->btns[i].st=NORM;continue;}
   if (down==2){b->btns[i].st=CLICK;}
   eif (down==0){ if(b->btns[i].st==CLICK){b->btns[i].onclick();} b->btns[i].st=HOVER;}})}
btn *btn_new(SDL_Rect r, TEXTURE * tx_norm,TEXTURE * tx_high, TEXTURE * tx_click,TEXTURE * tx_dis, V (* _onclick)()){
   btn *b = malloc(sizeof(btn));
   b->enable=_enable;
   b->tx_norm=tx_norm;b->tx_click=tx_click;b->tx_high=tx_high;b->tx_dis=tx_dis;b->r=r;b->st=NORM;b->onclick=_onclick;
   return b;}
btn_list * btn_list_new(){
   btn_list * b= malloc(sizeof(btn_list));
   b->add=_add;b->rm=_rm;b->free=_free;b->in=_in;b->draw=_draw;b->tick=_tick;
   b->i=0;b->size=10;
   b->btns= malloc(sizeof(btn)*b->size);
   return b;
}
#endif
