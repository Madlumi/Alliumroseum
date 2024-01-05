#pragma once

typedef int    I;
typedef float  F;
typedef double D;
typedef void V ;
typedef char   C;
typedef char*  S;

#define PRIV static;
#define IN(x,l,h) ((l)<=(x)&&(x)<=(h))
#define eif else if
#define W(x) while((x))
#define FOR(n,x) {for(int i=0;i<n;++i){x;}}
