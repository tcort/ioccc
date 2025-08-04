#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
const char X[]=" \netianmsurwdkgohvfXlYpjbxcyzqAX54B3PTR2&W+CHAR16=/INT(X7INT\
8X90FLOAT DOUBLE? CHAR\"  .    @SQL'  -UNSIGNEDPTR) TEXT,BLOB: BITINT(32)   ";
typedef uint32_t uX;typedef uint16_t uY;typedef uint8_t uZ;typedef int16_t iY;
size_t Ll=1440,SXl=480,Sl=2400,xyl=480,SY=1440,Il=0,ts=0;iY sm[]={0,7455,13285
,037533,15618,11612,5074,-2568,-9652,-034450,-0x4026,-034450,-9652,-2568,5074,
11612,15618,037533,13285,7455,0,-7455,-13285,-037533,-15618,-11612,-5074,2568,
9652,034450,0x4026,034450,9652,2568,-5074,-11612,-15618,-037533,-13285,-7455};
double T(double x){int i;double s=1,t=1;for(i=1;i<10;i++) {t*=x/i;s+=t;}return
s;}double Q(double x){int i;double y=1;for(i=0;i<5;i++) y+=2*(x-T(y))/(x+T(y))
;return y;}double J(double x) {return Q(x)/Q(2); }void P(FILE*f,uY n){putc((n&
0xFF),f);putc((n&0xFF00)>>8,f);}void O(FILE*f,uX n){P(f,(uY)n);P(f,(uY)( n>>16
));}int E(char *f,iY*I, size_t Il,size_t ts){FILE *o;uX i,fl=44+Il; o=fopen(f,
"w");if(o==NULL)return 1;fputs("RIFF",o);O(o,fl-8);fputs("WAVE",o);fputs("fmt\
 ",o);O(o,16);P(o,1);P(o,1);O(o,8000);O(o,16000);P(o,2);P(o,16);fputs("data",o
); O(o,ts*2); for(i=0;i<ts;i++) P(o,I[i]); fclose(o); return 0;}int N(char c){
unsigned long i;for(i=0;i<strlen(X);i++) if(tolower(c) ==X[i]) return i;return
-1;} iY* xy,*dt,*I=NULL,*L,*SX,*S;int K(int p){return p<2?0:J(p);}void M(iY*s,
size_t ns){size_t i;for(i=0;i<ns;i++){s[i]=sm[i%40];if(i<40)s[i]=s[i]*(i*0.025
);else if(i>ns-40)s[i]=s[i]*((ns-i)*0.025);}}void B(iY*d,size_t l){iY*U;size_t
_l=0;_l= Il+l; U=(iY*)realloc(I,_l*2); if(U==NULL)exit(1);memcpy(U+Il,d,l*2);I
=U; Il+=l;ts=Il;}void R(char c){int p=N(c),i;if(p==-1) return;if(p<2){B(S,Sl);
return;}for(i=K(p)-1;i>=0;i--) {if(i!=K(p)-1) B(SX,SXl); if((1<<i)&p)B(dt,SY);
else B(xy,xyl);}}int main(int argc,char *argv[]){FILE*f;int rc,i,c; if(argc!=3
){puts("prog in.txt out.wav");return 1;}f=fopen( argv[1],"r");if( f==NULL)exit
(1);L=(iY*) malloc(Ll*2);if(L== NULL) return 1;memset(L,0,2*Ll);SX=(iY*)malloc
(SXl*2);if(SX==NULL)return 1;memset(SX,0,2*SXl);S=(iY*)malloc(Sl*2);if(S==NULL
)return 1;memset(S,0,2*Sl);xy=(iY*)malloc(xyl*2);if(xy==NULL)return 1;M(xy,xyl
);dt=(iY*)malloc (SY*2);if(dt==NULL)return 1; M(dt, SY);for(i=0;(c=getc(f)) !=
EOF;i++){if(i!=0)B(L,Ll);R(c);} free(xy);free(dt);free(L);free(SX);free(S);xy=
dt=L=SX=S=NULL;xyl=SY=Ll=SXl=Sl=0;fclose(f);rc=E(argv[2],I, Il,ts);free(I);Il=
ts=0;exit(rc);;;;;;}
