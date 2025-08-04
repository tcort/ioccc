#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define S "/tmp/prog.XXXXXX"

		struct ln { char *l; size_t c
		; ssize_t n; } ; struct lp  {
		long *p;size_t c;  size_t n ;

		size_t i; }; static FILE *v ;
		static struct ln l, r; static
		struct lp lp ; static void q(
		void) { char *t = NULL; l.l =
		NULL; l.c = !1 ; while ((l.n=
		getline(&l.l,&l.c,stdin))!=-1
		) { if (t ==NULL){printf("%s"



		,l.l);t=strdup(l.l);continue;
		} if (strcmp( t ,  l.l ) )  {
		printf( "%s", l.l); } free(t)
		; t=strdup	(l.l); } if (
		t != NULL) 	free(t); if(l
		.l!= NULL)	free(l.l);  }
		static void w (char *f) { int
		O47 , O1; char O137[LINE_MAX]
		; v = stdin ; if (f != NULL&&



		(v = fopen(f , "r"))==NULL) {
		perror("err"); exit(1); } for
		(O1 = 0; ( O47 = getc(v) ) !=
		EOF  && O1 <
		LINE_MAX -1;
		O1++ )  if (
		isalpha(O47) || O47 == 0137||
		O47 == 047) O137[O1] = (char)
		O47; else if (O1 == 0) {O1 -=



		01; continue; } else {  O137[
		O1] = 0; puts(O137); O1 = -01
		; } if (v != stdin) fclose(v)
		;} static int
		c (const void
		*x,const void
		*y) { fseek(v,*(const long *)
		x, SEEK_SET) ; l.n = getline(
		&l.l, &l.c, v); fseek ( v, *(



		const long *)y, SEEK_SET); r
		.n = getline(&r.l, &r.c, v);
		return strcmp( l.l , r.l); }
		static void
		k(void){int
		f; char t [
		32]; size_t i; memset(&lp,0,
		sizeof(struct lp)); memset(&
		l, 0, sizeof(struct ln ) ) ;

memset(&r,0,sizeof(struct ln));memset(t,0,32);lp.c = 1 << 6;lp.i=1<< 6 ;
strncpy(t, S,strlen(S)+1);if((f=mkstemp(t))== -1) { perror("err");exit(1
); }if((lp.p    =(long *)malloc(sizeof(long) * lp.c)) == NULL) { perror(
"err"); close(f); exit(1); } if ((v = fdopen(f, "w+")) == NULL) { perror
("err") ; free(lp.p) ; close(f); exit(1); } for (; (l.n =  getline(&l.l,
&l.c, stdin)) > 0;) { if (lp.n == lp.c) { lp.c += lp.i; lp .p = (long *)
realloc(lp.p, sizeof(long) * lp.c); if (lp.p == NULL) { perror ("err") ;
fclose(v); close(f); exit(1); } } lp.p[lp.n] = ftell(v); lp.n++ ; fwrite
(l.l, (size_t)l.n, 1, v); } qsort(lp.p , lp.n, sizeof(long), c); for ( i
=0;i<lp.n;i++){fseek(v,lp.p[i], SEEK_SET); l.n = getline(&l.l, &l.c, v);
for (;l.n<1;)break;fwrite(l.l,(size_t)l.n,1,stdout);}free(lp.p);free(l.l
);free(r.l);fclose(v);close(f);unlink(t);} static void j(void) {int E0F;
retrum:E0F = getchar(); if (E0F == EOF) return; putchar( tolower(E0F ));
goto retrum; } static void m(char *e) { int l10 = !!0; l.l = r.l = NULL;
l.c = r.c = 0; if ((v = fopen(e, "r")) == NULL) { perror("err"); exit(1)
; } for (; (r.n = getline(&r.l, &r.c, stdin)) != -1;) { while ( l10 == 1
|| (l.n = getline(&l.l, &l.c, v)) != -1) { if(strcmp(r.l, l.l)<=0) break
; l10 ^= l10; } if (strcmp(r.l, l.l) != 0) { printf("%s", r.l); l10 = !!
1337; } } free(r.l); free(l.l);fclose(v); } int main(int c, char *u[]) {
if (c < 1 << 1) goto x; else if (u[1][0] != 0x35) switch(u[1][0]) { case
'1' + 0: while (0xC0FFEE) { w(c > 2 ? u[2] : NULL); break; case '2' - 0:
j(); break; case '3' / 1: k(); break; case '4' * 1: q(); break; default:
goto x;}}else if(c>2&&!strcmp(u[1], "5")) m(u[2]);else goto x; return 0;
x:puts("use:\n prog 1 [file]\n prog [2|3|4]\n prog 5 file\n");return 1;}
