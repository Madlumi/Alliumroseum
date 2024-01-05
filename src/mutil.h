#pragma once
#include <stdbool.h>

typedef int    I;
typedef bool B ;
typedef float  F;
typedef double D;
typedef void V ;
typedef char   C;
typedef char*  S;

#define SW switch
#define CA(x,y) case x: y; break;
#define BR break
#define PRIV static;
#define IN(x,l,h) ((l)<=(x)&&(x)<=(h))
#define eif else if
#define el else
#define W(x) while((x))
#define FOR(n,x) {for(int i=0;i<n;++i){x;}}
