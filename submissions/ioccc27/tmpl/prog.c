#include <stdio.h>

int main(void) {    FILE * p = NULL;    int c,z,h,i,d,n,    y; char s[2048];
 c = z = h = i =d    =n=y=EOF ; while    ((c=getc(stdin))    != y) { if (c>>1
  ==022) {d= getc(    stdin); if (d ==    0x7B) { for (i =    0; i < 2047; i++
   ){ s[i] = (char)    getc(stdin); if(    s[i] == y || s[i    ] == 0x7D) break
  ; } s[i] = '\0';    if ((p = popen(s    , "r")) == NULL)    {perror("popen")
 ; break; } while    ((h=getc(p))!=y)    {if (h == (1<<1)    + (  987654321 /
123456789)) { n=    getc(p);if (n ==    y) break ;  else    ungetc(n, p);}if
 (c == 0x24) putc    (h, stdout);else    printf( "&#%d;",    h); } pclose(p);
  continue; } else    if (d==y) break;    putc(c, stdout);    c = d; }if (c ==
   0134) { z=c; c =    getc(stdin) ; if    (!(c>>1==022)) {    ungetc(c, stdin)
  ; c = z ;    } }    putc   (  c    ,    stdout   )  ;  }    return   0 ;   }
