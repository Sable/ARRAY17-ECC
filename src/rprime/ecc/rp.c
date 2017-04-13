#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "aplc.h"
#include "eli3lib.h"
#include "elimacros.h"
#define HEAPSIZE 2097152000
#define BVBFLE32 102400000
#define IVBFLE 163840
#define EVBFLE 163840
#define CVBFLE 163840
#define minn -7.237005577332262e75
#define QDCT 1e-13
#define QDRL 16807
#define QDPP 7
   int c2[2];
   int c21[25] =
{2,3,5,7,11,13,
17,19,23,29,31,37,
41,43,47,53,59,61,
67,71,73,79,83,89,
97};
   int  lf1= 0x80000000;
   int  ivbf[IVBFLE];
   double evbf[EVBFLE];
   int  bvbf[BVBFLE32];
   char cvbf[CVBFLE];
   int  r0, r1, r2, r8, t, n, i, j, new_v, time1, time2, th;
   int  w0, w1, w2, w3, w4, w5, w6, u0, u1, u2, u3, u4, u5, u6;
   int  q0, q1, q2, q3, q4, q5, q6, v0, v1, v2, v3, c6;
   int  l0, l1, l2, l3, l4, l5, l6, m0, m1, m2, m3, m4, m5, m6;
   int  sw, si, s0, s1, s2, s3, s4, s5, s6, freti;
   double d, fretf, epsln;
   char fretc;
   int  r15= HEAPSIZE;
   int  rseed= QDRL, initf;
   unsigned int tl,ttl,wa,wb;
   unsigned int * twp;
   int * v4= bvbf;
   char * v7= cvbf;
   int * fretip, * v5= ivbf;
   double * fretfp, * v6= evbf;
   char * fretcp, * lop, * rop, * cad0, * heap;
   int lshp[8], rshp[8], cad[50], dl[7], tdl[7], vdl[7];
   int * p0, * p1, * lo0, * lo1, * ro0,* ro1,* t0,* t1,* p10,* p11,*p12;
   int * lo13, * lo10,* ro13, * ro10, * lo11, * ro11,* lo12,* ro12;
   int * id0, * id1, * id2, * id3, * id4, * id5, * id6;
   double * p2,* t2,* lo2,* ro2,* p20,* p21,* p22,* lo24,* ro24,* lo25;
  double * lo20,* ro20,* lo21,* ro21,* lo22,* ro22,* lo23,* ro23,* ro25;
   char *ro30, * p3, *t3, * lo3, * ro3, *pTarg, *pSrc, *pBuff0, *pBuff1;
   STOFM2 v27;
   STOFM3 v28;
   STOFM2 v29;
   STOFM3 v30;
   STOFM2 v31;
   STOFM3 v32;
   //int totalWrapMoveTime = 0;
main(int argc, char * argv[])
 {char * lparm, * rparm;
  char  ltype, rtype;
    int  g19;
  int lleng= 1;
  FILE *fpl, *fpr, *fopen();
  extern int apl_sec();
  initf= 1;
  heap=(char*)amalloc(HEAPSIZE);
  v5=(int*)amalloc(131072000); v6=(double*)amalloc(131072000);
 {while (--argc > 0)
  if (argc>0) {lparm = *argv; *argv = *argv + 1;}
  else rparm = *argv;}
  lleng = 1;
  if( argv[1] == NULL )
    fpr= a_fopen("rprime.RIG","r");
  else
   {sprintf(cvbf, "%s.RIG", argv[1]);
    fpr= a_fopen(cvbf, "r"); }
  fscanf(fpr,"%c %d",&rtype,&rshp[0]);
  if( rtype!= 'I')  {
 printf("The type of the right arguement is mismatched.\n"); exit(99);}
  if( rshp[0]!= 0)  {
 printf("The rank of the right arguement is mismatched.\n"); exit(99);}
  for( i = 1; i < 1 + rshp[0]; ++i)  {
  fscanf(fpr," %d",&rshp[i]); lleng *= rshp[i];}
  while (fgetc(fpr) != '\n');
  fscanf(fpr,"%d",&g19);
  time1 = apl_sec();
  rprime   (g19);
  time2 = apl_sec();
  //printf("\n execution time in ms %d\n",time2-time1);
  printf("\n The elapsed time in ms: %g\n",(time2-time1)/1000.0);
  //printf("Total wrapmove time in ms: %g\n", totalWrapMoveTime/1000.0);
/*   OUTPUT generates the following code */
/*  p1 = fretip;
if(cad[1]<21) for(v1=0;v1<cad[1];v1++){printf("%d ",*p1);++p1;}
  else for (v1=0;v1<cad[1];v1++)
    {printf("%d ",*p1); ++p1; if ((v1%20)==19) printf("\n");}
 putchar('\n');*/
   free(heap); free(v5); free(v6); /* system("pause"); */ exit(0);}
/*              CODE SEGMENT FOR FUNCTION rprime        */
rprime   (v19)
    int  v19;
  { char v8, v11;
   int oldr15, v9, v12, v13, v17;
   double v10, v14, v15, v16;
   STOFM2 v18;
    int  v20;
   STOFM2 v21;
    int  v22;
   STOFM2 v23;
   STOFM2 v24;
   STOFM2 v25;
   STOFM2 v26;
   v18.maxl = -1;
   v27.maxl= -1; v28.maxl= -1; v29.maxl= -1;
   v30.maxl= -1; v31.maxl= -1; v32.maxl= -1;
   v21.maxl = -1;
   v23.maxl = -1;
   v24.maxl = -1;
   v25.maxl = -1;
   v26.maxl = -1;
new_v=0;
lj1:
/******************   LINE 1   ******************/
   r0=25;
INCHEAPP3(v18,inchp1); /* by INCHEAPP */
   memcpy(v18.valp, (char *) c21, 25<<2);
/******************   LINE 2   ******************/
/*     PFCOMPB generates the folowing code    */
   v8 = v19<=100;
/*  PFLOGIC Generates the following code for ~*/
if (0==v8)
v9 =  1;
    else
v9 =  0;
   if (v9!=0)
   goto lj5;
lj3:
/******************   LINE 3   ******************/
  r0=v18.reall;
  cad[11]=r0;
/*     PFCOMPB generates the folowing code    */
ro1 = (  int  *) v18.valp;
/*   PFCOMPRE generates the following code */
ro10 = (  int  *) v18.valp;
r0=r0;
  if (r0!=v18.reall && r0!=1) if (0!=v18.reall && r0!=1)
  LEMSG(18,3);
INCHEAPPH(v18,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
/* TEMPCOPY Generates the following instructions:  */
if (new_v==0) {r8=v18.reall;
  r1=r8<<2;
  th= r15-r1;
  if (th<0) alloc(4);
  t1 = (  int  *) &heap[th];
  memcpy(&heap[th], v18.valp, r8<<2);
  ro1= (  int  *) &heap[th];}
i= 0;
  for (v1=0; v1<r0; v1++)
  if (v19>=ro1[v1]) { p1[i]= ro10[v1]; i++;}
cad[1]= i;
  v18.valp = cad0;
  v18.reall= cad[1];
/******************   LINE 4   ******************/
  goto lj13;
lj5:
/******************   LINE 5   ******************/
/******************   LINE 6   ******************/
 v10 = pow((double)v19,0.5); /* code for *. */
 v9 =  floor(QDCT+v10); /* code for _. */
  oldr15= r15;
rprime   (v9);
  r15= oldr15;
  v27.maxl= -1; v28.maxl= -1; v29.maxl= -1;
  v30.maxl= -1; v31.maxl= -1; v32.maxl= -1;
   r0=cad[1];
INCHEAPP3(v18,inchp1); /* by INCHEAPP */
   memcpy(v18.valp, (char *) fretip, cad[1]<<2);
/*   GENRHO generates the following code */
  v20= v18.reall;
/******************   LINE 7   ******************/
/*   RESHAPE generates the following code */
  r0=v19;
INCHEAPPH(v21,inchp0, p0 = (   int  *) cad0 ); /* by INCHEAPP */
  n=r0; r0 +=31; r0 >>= 5;
  for (v1=0; v1<r0; v1++)
 p0[v1] = 0;
  v21.valp = cad0;
  v21.reall= cad[1];
/******************   LINE 8   ******************/
  v22 = 1;
lj9:
/******************   LINE 9   ******************/
/******************   LINE 10   ******************/
/* INDEXV generates the following code */
lo1 = (  int  *) v18.valp;
if (v18.reall<=(v22-1)         )
  IDMSG(46,10);
v9 = lo1[(v22-1)         ];
 v12 =  -v9; /* code for - */
/*   PFTAKE generates the following code */
  r0=abs(v12);
INCHEAPPH(v23,inchp0, p0 = (   int  *) cad0 ); /* by INCHEAPP */
r1=(r0+31)>>5;
  for (v1=0; v1<r1; v1++)
 p0[v1] = 0;
if (v12<0)
if ((tl=r0&0x0000001f)==0)
 p0[r1-1]=1;
    else
 p0[r1-1]=1<<(32-tl);
    else
 p0[0]=1<<31;
  v23.valp = cad0;
  v23.reall= cad[1];
/*   RESHAPE generates the following code */
ro0 = (  int  *) v23.valp;
  r0=v19;
cad[1]=r0;
//int chf0 = clock();
  wrapmove(v4, ro0, r0, v23.reall);
//totalWrapMoveTime += clock()-chf0;
  cad[11] = cad[1];
r0= v21.reall;
  if (r0!=cad[11] && r0!=1)
  LEMSG(41,10);
/*  PFLOGIC Generates the following code for &*/
p0 = (  int  *) v21.valp;
lo0 = (  int  *) v21.valp;
  r1= (31+r0)>>5;
  for (v1=0; v1<r1; v1++)
     p0[v1] = lo0[v1]|v4[v1];
/******************   LINE 11   ******************/
 v22 = v22+1; /* code for + */
/*     PFCOMPB generates the folowing code    */
   v8 = v20>=v22;
   if (v8!=0)
   goto lj9;
lj12:
/******************   LINE 12   ******************/
/* PFIOTA Generates the following instructions: */
  r0 = v19;
INCHEAPPH(v24,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
  if  (r0 == 0) goto l2;
  for (v1=0; v1<r0; v1++)
 p1[v1] =  v1+1;
l2:;
  v24.valp = cad0;
  v24.reall= cad[1];
  r0 =   v21.reall;
  cad[11] =  r0;
/*  PFLOGIC Generates the following code for ~*/
ro0 = (  int  *) v21.valp;
  r1= (31+v21.reall)>>5;
  for (v1=0; v1<r1; v1++)
    v4[v1] =  ~ro0[v1];
  if (0 != (tl = v21.reall<<27))
    { tl>>=27;
  t =v4[r1-1]>>(32-tl);
  v4[r1-1] = t<<(32-tl);}
/*   PFCOMPRE generates the following code */
ro1 = (  int  *) v24.valp;
r0=cad[11];
  if (r0!=v24.reall && r0!=1) if (0!=v24.reall && r0!=1)
  LEMSG(65,12);
  if (r0==0) goto l3;
  n = no_of_ones(r0,v4);
  r0 = n;
INCHEAPPH(v25,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
  i= 0; r1= (31+cad[11])>>5;
  for (v2=0; v2<r1; v2++) {t= v4[v2];
    for (v1=0; v1<32; v1++) {
      if ( t == 0) break;
      else if ( t < 0) {
       p1[i]= ro1[32*v2+v1];
      i++;} t<<=1; } }
l3:;
  v25.valp = cad0;
  v25.reall= cad[1];
/*   PFDROP generates the following code */
ro1 = (  int  *) v25.valp;
 n= 1; r0=v25.reall-abs(n); if (r0<0) r0= 0;
INCHEAPPH(v26,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
if (r0 == 0)
  goto l4;
cad0 = v25.valp +sizeof(  int )*max(0,1);
l4:;
  v26.valp = cad0;
  v26.reall= cad[1];
/***** PFCATENA *****/
lo1 = (  int  *) v18.valp;
ro1 = (  int  *) v26.valp;
  r0 = cad[1]= v18.reall+v26.reall;
INCHEAPPH(v18,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
if (new_v==1)   for (v1=0; v1<v18.reall; v1++)
      p1[v1] = lo1[v1];
j= v18.reall;
  for (v1=0; v1<v26.reall; v1++)
      p1[v1+j]= ro1[v1];
  v18.valp = cad0;
  v18.reall= cad[1];
lj13:
/******************   LINE 13   ******************/
lj0:;
cad[1]= v18.reall;
fretip= (  int  *) v18.valp;
    }
