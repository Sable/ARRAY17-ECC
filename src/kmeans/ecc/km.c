#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
   STOFM2 v45;
   STOFM3 v46;
   STOFM2 v47;
   STOFM3 v48;
   STOFM2 v49;
   STOFM3 v50;
   int totalTime = 0;
   int chf0;
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
  if( argv[1] == NULL )
    fpl= a_fopen("kmeans.LEF","r");
  else
   {sprintf(cvbf, "%s.LEF", argv[1]);
    fpl= a_fopen(cvbf, "r"); }
  fscanf(fpl,"%c %d",&ltype,&lshp[0]);
  if( ltype!= 'I')  {
 printf("The type of the left arguement is mismatched.\n"); exit(99);}
  if( lshp[0]!= 0)  {
 printf("The rank of the left arguement is mismatched.\n"); exit(99);}
  for( i = 1; i < 1 + lshp[0]; ++i)  {
  fscanf(fpl," %d",&lshp[i]); lleng *= lshp[i];}
  while (fgetc(fpl) != '\n');
  fscanf(fpl,"%d",&g19);
  lleng = 1;
  if( argv[1] == NULL )
    fpr= a_fopen("kmeans.RIG","r");
  else
   {sprintf(cvbf, "%s.RIG", argv[1]);
    fpr= a_fopen(cvbf, "r"); }
  fscanf(fpr,"%c %d",&rtype,&rshp[0]);
  if( rtype!= 'E')  {
 printf("The type of the right arguement is mismatched.\n"); exit(99);}
  if( rshp[0]!= 2)  {
 printf("The rank of the right arguement is mismatched.\n"); exit(99);}
  for( i = 1; i < 1 + rshp[0]; ++i)  {
  fscanf(fpr," %d",&rshp[i]); lleng *= rshp[i];}
  while (fgetc(fpr) != '\n');
  rshp[0]= r0 = lleng;inchp2;
  rop= &heap[r15]; p2 = (double *) rop;
  for(i = 0; i < lleng; ++i)  {
    fscanf(fpr,"%lf",p2);
    ++p2;}
  time1 = apl_sec();
  kmeans   (g19,ro2);
  time2 = apl_sec();
  //printf("\n execution time in ms %d\n",time2-time1);
  printf("\n The elapsed time in ms: %g\n",(time2-time1)/1000.0);
  printf("Indexa time in ms: %g\n", totalTime/1000.0);
/*   OUTPUT generates the following code */
/*  p2 = fretfp;
  w0 = cad[3];
w1= cad[1]/w0;
for (u0=0; u0<w1; u0++)  {
if(w0<11) for(v1=0;v1<w0;v1++){a_prtD0(*p2);++p2;}
  else for (v1=0;v1<w0;v1++)
    {a_prtD0(*p2); ++p2; if ((v1%10)==9) printf("\n");}
  putchar('\n');}
 putchar('\n');*/
   free(heap); free(v5); free(v6);                  exit(0);}
/*              CODE SEGMENT FOR FUNCTION kmeans        */
kmeans   (v19,p20)
    int  v19;
  double* p20;
  { char v8, v11;
   int oldr15, v9, v12, v13, v17;
   double v10, v14, v15, v16;
   STOFM3 v18;
    int  v21;
    int  v22[2];
    int  v23;
   STOFM2 v24;
   STOFM2 v25;
   STOFM2 v26;
   STOFM2 v27;
   STOFM2 v28;
   STOFM2 v29;
   STOFM3 v30;
   STOFM2 v31;
    int  v32;
    int  v33;
    int  v34;
   STOFM3 v35;
   STOFM2 v36;
   STOFM2 v37;
   STOFM2 v38;
   STOFM3 v39;
    int  v40[2];
   STOFM2 v41;
   STOFM2 v42;
   STOFM3 v43;
   STOFM3 v44;
   STOFM3 v20;
   v18.maxl = -1;
   v45.maxl= -1; v46.maxl= -1; v47.maxl= -1;
   v48.maxl= -1; v49.maxl= -1; v50.maxl= -1;
   v24.maxl = -1;
   v25.maxl = -1;
   v26.maxl = -1;
   v27.maxl = -1;
   v28.maxl = -1;
   v29.maxl = -1;
   v30.maxl = -1;
   v31.maxl = -1;
   v35.maxl = -1;
   v36.maxl = -1;
   v37.maxl = -1;
   v38.maxl = -1;
   v39.maxl = -1;
   v41.maxl = -1;
   v42.maxl = -1;
   v43.maxl = -1;
   v44.maxl = -1;
r0= rshp[0];
  for (v1=0; v1<2; v1++)
  v20.dims[v1+0]=rshp[v1+1];
if (initf == 1)
  {v20.valp= rop;
  v20.reall= v20.maxl= r0;
  initf= 0;
  } else {
v20.reall= v20.maxl= r0;
 inchp2; v20.valp= &heap[r15]; /* by INCHEAP2V */
ro2= (double *) v20.valp;
  for (v1=0; v1<r0; v1++)
ro2[v1]= p20[v1];}
new_v=0;
lj1:
/******************   LINE 1   ******************/
  v33 = (-1);
/*   GENRHO generates the following code */
p1 = (  int  *) v26.valp;
  v26.reall=2;
  r0 = 2;
INCHEAPP3(v26,inchp1); /* by INCHEAPP */
  p1 = (  int  *) v26.valp; /* hf-up-3 */
  for (v1=0; v1<2; v1++)
 p1[v1] = v20.dims[v1];
/*   PFTAKE generates the following code */
ro1 = (  int  *) v26.valp;
if (0==v26.reall) v21 =  0 ; else
v21 = ro1[0];
/*   RESHAPE generates the following code */
  r0=v21;
INCHEAPPH(v28,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
  for (v1=0; v1<r0; v1++)
 p1[v1] = (-1);
  v28.valp = cad0;
  v28.reall= cad[1];
   r0=v28.reall;
INCHEAPP3(v29,inchp1); /* by INCHEAPP */
   memcpy(v29.valp, v28.valp, v28.reall<<2);
/******************   LINE 2   ******************/
/* INDEXV generates the following code */
lo1 = (  int  *) v26.valp;
if (v26.reall<=(2-1)           )
  IDMSG(30,2);
v9 = lo1[(2-1)           ];
/***** PFCATENA *****/
  r0 = cad[1]= 1+1;
  v22[0] = v19;
  v22[1]= v9;
/*   PFTAKE generates the following code */
ro2 = (double *) v20.valp;
  r0=1;
  for (v1=0; v1<2; v1++)
  {cad[2+v1] = abs(v22[v1]);
   r0= r0*cad[2+v1];}
INCHEAPPH(v18,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v20.dims[1-u0];
  tdl[1] = t = 1;
 t= tdl[0] = t*cad[3];
 s0= v20.dims[0]     -cad[2];
 s1= v20.dims[1]     -cad[3];
tak2d( p2,v22,ro2,v20.dims[0],v20.dims[1],s0,s1,cad,tdl,dl);
  for (v1=0; v1<2; v1++)
  v18.dims[v1+0]=  cad[v1+2];
  v18.valp = cad0;
  v18.reall= cad[1];
lj3:
/******************   LINE 3   ******************/
  v32 = 0;
/*   RESHAPE generates the following code */
  r0=1;
  for (v1=0; v1<2; v1++)
  {cad[2+v1] =v22[v1];
   r0= r0*cad[2+v1];}
INCHEAPPH(v30,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  for (v1=0; v1<r0; v1++)
 p2[v1] = 0;
  for (v1=0; v1<2; v1++)
  v30.dims[v1+0]=  cad[v1+2];
  v30.valp = cad0;
  v30.reall= cad[1];
/******************   LINE 4   ******************/
/*   RESHAPE generates the following code */
  r0=v19;
INCHEAPPH(v31,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
  for (v1=0; v1<r0; v1++)
 p1[v1] = 0;
  v31.valp = cad0;
  v31.reall= cad[1];
lj5:
/******************   LINE 5   ******************/
 v32 = v32+1; /* code for + */
/*     PFCOMPB generates the folowing code    */
   v8 = v21< v32;
   if (v8!=0)
   goto lj10;
lj6:
/******************   LINE 6   ******************/
/* INDEXV generates the following code */
lo2 = (double *) v20.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v20.dims[1-u0];
  cad[2]= v20.dims[1]     ;
  n=0;
  n += dl[0]*(v32-1)         ;
  r0=v20.dims[1]     ;
INCHEAPPH(v36,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
if (r0==0) goto l2;
  for (u0=0; u0<v20.dims[1]     ; u0++)
   p2[u0] = lo2[n+dl[1]*u0];
l2:;
  v36.valp = cad0;
  v36.reall= cad[1];
/*   RESHAPE generates the following code */
ro2 = (double *) v36.valp;
  r0=1;
  for (v1=0; v1<2; v1++)
  {cad[2+v1] =v22[v1];
   r0= r0*cad[2+v1];}
cad[1]=r0;
if  (r0<=v36.reall)
  for (v1=0; v1<r0; v1++)
v6[v1] = ro2[v1];
 else
 {r1=0;
  while  (r0>v36.reall) {
  for (v1=0; v1<v36.reall; v1++)
  v6[r1+v1]=ro2[v1];
  r0=r0-v36.reall;
  r1=r1+v36.reall;}
  if (r0 != 0)
  for (v1=0; v1<r0; v1++)
  v6[r1+v1]=ro2[v1];}
  cad[31] = cad[1];
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  cad[v1+2];
r0= cad[31];
if (cad[32] != v18.dims[0])
  LEMSG(72,6);
if (cad[33] != v18.dims[1])
  LEMSG(72,6);
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  cad[32+v1];
ro2 = (double *) v18.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for - */
    v6[v1] = v6[v1]-ro2[v1];
  for (v1=0; v1<2; v1++)
  v35.dims[v1+0]=  cad[32+v1];
  r0=cad[31];
  for (v1=0; v1<2; v1++)
  v35.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v35,inchp2); /* by INCHEAPP */
p2 = (double *) v35.valp;
  for (v1 =0; v1<r0; v1++) /* code for *. */
     p2[v1] = v6[v1]*v6[v1];
/*   REDUCT generates the following code */
ro2 = (double *) v35.valp;
  v3 =v35.dims[1];
  for (v1=0; v1<2; v1++)
  cad[2+v1]=  v35.dims[v1+0];
  r0 =1;
  for (u0=0; u0<1; u0++)
  r0=r0*cad[2+u0];
INCHEAPPH(v27,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
if (v35.dims[1]==0) goto l3;
  for (u0=0; u0<r0; u0++)
  {q1=u0*v3;
 d= ro2[q1+v3-1];
  for (u2=v3-2; u2>=0; u2--)
  d = ro2[q1+u2]+d;
   p2[u0] = d;}
  goto l4;
l3:;
  for (v1=0; v1<r0; v1++)
    p2[v1] = 0;
l4:;
  v27.valp = cad0;
  v27.reall= cad[1];
/*   REDUCT generates the following code */
ro2 = (double *) v27.valp;
  if (v27.reall== 0)
   d= 0;
  else {d= ro2[v27.reall-1];
  for (v1=v27.reall-2; v1>=0; v1--)
  d=min(ro2[v1],d);}
  v10=d;
/*   INDEXOF generates the following code */
lo2 = (double *) v27.valp;
t=1;
  for (v1=0; v1<v27.reall; v1++)
  {if (v10==lo2[v1])
   break;
t++;}
   v23 =  t;
/* INDEXA generates the following code */
p1 = (  int  *) v28.valp;
lo1 = (  int  *) v28.valp;
 p1[(v32-1)         ]=v23;
/******************   LINE 7   ******************/
/* INDEXV generates the following code */
lo2 = (double *) v20.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v20.dims[1-u0];
  cad[2]= v20.dims[1]     ;
  n=0;
  n += dl[0]*(v32-1)         ;
  r0=v20.dims[1]     ;
INCHEAPPH(v41,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
if (r0==0) goto l5;
  for (u0=0; u0<v20.dims[1]     ; u0++)
   p2[u0] = lo2[n+dl[1]*u0];
l5:;
  v41.valp = cad0;
  v41.reall= cad[1];
/* INDEXV generates the following code */
lo2 = (double *) v30.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v30.dims[1-u0];
  cad[2]= v30.dims[1]     ;
  n=0;
  n += dl[0]*(v23-1)         ;
  r0=v30.dims[1]     ;
cad[1]=r0;
if (r0==0) goto l6;
  for (u0=0; u0<v30.dims[1]     ; u0++)
  v6[u0] = lo2[n+dl[1]*u0];
l6:;
  cad[31] = cad[1];
r0= cad[31];
  if (r0!=v41.reall && r0!=1)
  LEMSG(87,7);
INCHEAPP3(v42,inchp2); /* by INCHEAPP */
p2 = (double *) v42.valp;
ro2 = (double *) v41.valp;
  for (v1 =0; v1<r0; v1++) /* code for + */
     p2[v1] = v6[v1]+ro2[v1];
/* INDEXA generates the following code */
chf0 = clock();
p2 = (double *) v30.valp;
lo2 = (double *) v30.valp;
ro2 = (double *) v42.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v30.dims[1-u0];
  cad[2]= v30.dims[1]     ;
  n=0;
  n += dl[0]*(v23-1)         ;
  r0=v30.dims[1]     ;
  for (u0=0; u0<v30.dims[1]     ; u0++)
   p2[n+dl[1]*u0] = ro2[u0];
totalTime += clock() - chf0;
/******************   LINE 8   ******************/
/* INDEXV generates the following code */
lo1 = (  int  *) v31.valp;
if (v31.reall<=(v23-1)         )
  IDMSG(98,8);
v9 = lo1[(v23-1)         ];
 v12 = v9+1; /* code for + */
/* INDEXA generates the following code */
p1 = (  int  *) v31.valp;
lo1 = (  int  *) v31.valp;
 p1[(v23-1)         ]=v12;
/******************   LINE 9   ******************/
  goto lj5;
lj10:
/******************   LINE 10   ******************/
r0= v29.reall;
  if (r0!=v28.reall && r0!=1)
  LEMSG(106,10);
  cad[11]=r0;
/*     PFCOMPB generates the folowing code    */
lo1 = (  int  *) v29.valp;
ro1 = (  int  *) v28.valp;
v1 =0;
while (v1+31 < r0)
 {t=0;
  for (u0=0; u0<32; u0++)
   {if (lo1[v1]!=ro1[v1])
       t|= lfb>>u0; v1++;}
  v4[v1-1>>5]= t;}
tl= r0&msk;
if ( tl!=0 )
 {t=0;
  u0= r0-tl;
  for (v1= u0; v1 < r0; v1++)
   {if (lo1[v1]!=ro1[v1])
       t|= lfb>>v1-u0;}
  v4[v1>>5]= t;}
/*   REDUCT generates the following code */
  v34 =  breduct0(v4, cad[11]);
/******************   LINE 11   ******************/
  r0=v31.reall;
INCHEAPP3(v24,inchp0); /* by INCHEAPP */
/*     PFCOMPB generates the folowing code    */
p0 = (  int  *) v24.valp;
lo1 = (  int  *) v31.valp;
v1 =0;
while (v1+31 < r0)
 {t=0;
  for (u0=0; u0<32; u0++)
   {if (lo1[v1]!=0)
       t|= lfb>>u0; v1++;}
   p0[v1-1>>5]= t;}
tl= r0&msk;
if ( tl!=0 )
 {t=0;
  u0= r0-tl;
  for (v1= u0; v1 < r0; v1++)
   {if (lo1[v1]!=0)
       t|= lfb>>v1-u0;}
   p0[v1>>5]= t;}
/*   GENRHO generates the following code */
  v9= v24.reall;
/* PFIOTA Generates the following instructions: */
  r0 = v9;
INCHEAPPH(v37,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
  if  (r0 == 0) goto l7;
  for (v1=0; v1<r0; v1++)
 p1[v1] =  v1+1;
l7:;
  v37.valp = cad0;
  v37.reall= cad[1];
/*   PFCOMPRE generates the following code */
lo0 = (  int  *) v24.valp;
ro1 = (  int  *) v37.valp;
r0=v24.reall;
  if (r0!=v37.reall && r0!=1) if (0!=v37.reall && r0!=1)
  LEMSG(133,11);
  if (r0==0) goto l8;
  n = no_of_ones(r0,lo0);
  r0 = n;
INCHEAPPH(v25,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
  i= 0; r1= (31+v24.reall)>>5;
  for (v2=0; v2<r1; v2++) {t= lo0[v2];
    for (v1=0; v1<32; v1++) {
      if ( t == 0) break;
      else if ( t < 0) {
       p1[i]= ro1[32*v2+v1];
      i++;} t<<=1; } }
l8:;
  v25.valp = cad0;
  v25.reall= cad[1];
/* INDEXV generates the following code */
lo1 = (  int  *) v31.valp;
id0 = (int *) v25.valp;
  cad[2]= v25.reall       ;
  r0=v25.reall       ;
INCHEAPPH(v38,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
if (r0==0) goto l9;
  for (u0=0; u0<v25.reall       ; u0++)
 p1[u0]=lo1[id0[u0]-1       ];
l9:;
  v38.valp = cad0;
  v38.reall= cad[1];
/*   GENRHO generates the following code */
  v9= v25.reall;
/* INDEXV generates the following code */
lo1 = (  int  *) v26.valp;
if (v26.reall<=(2-1)           )
  IDMSG(122,11);
v12 = lo1[(2-1)           ];
/***** PFCATENA *****/
  r0 = cad[1]= 1+1;
  v40[0] = v12;
  v40[1]= v9;
/*   RESHAPE generates the following code */
ro1 = (  int  *) v38.valp;
  r0=1;
  for (v1=0; v1<2; v1++)
  {cad[2+v1] =v40[v1];
   r0= r0*cad[2+v1];}
INCHEAPPH(v39,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
if  (r0<=v38.reall)
  for (v1=0; v1<r0; v1++)
 p1[v1] = ro1[v1];
 else
 {r1=0;
  while  (r0>v38.reall) {
  for (v1=0; v1<v38.reall; v1++)
   p1[r1+v1]=ro1[v1];
  r0=r0-v38.reall;
  r1=r1+v38.reall;}
  if (r0 != 0)
  for (v1=0; v1<r0; v1++)
   p1[r1+v1]=ro1[v1];}
  for (v1=0; v1<2; v1++)
  v39.dims[v1+0]=  cad[v1+2];
  v39.valp = cad0;
  v39.reall= cad[1];
/*   MONADIC TRANSPOSE generates the following code */
ro1 = (  int  *) v39.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v39.dims[1-u0];
cad[2]= v39.dims[1];
cad[3]= v39.dims[0];
  tdl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= tdl[0-u0]= t*cad[2+1-u0];
r0= v39.reall;
INCHEAPPH(v43,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
  for (u0=0; u0<cad[2]; u0++)
{w0= u0*tdl[0];
 q0= u0*dl[1];
  for (u1=0; u1<cad[3]; u1++)
    p1[w0+u1]= ro1[q0+u1*dl[0]];}
  for (v1=0; v1<2; v1++)
  v43.dims[v1+0]=  cad[v1+2];
  v43.valp = cad0;
  v43.reall= cad[1];
/* INDEXV generates the following code */
lo2 = (double *) v30.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v30.dims[1-u0];
id0 = (int *) v25.valp;
  cad[2]= v25.reall       ;
  cad[3]= v30.dims[1]     ;
  tdl[0] =v30.dims[1]     ;
  r0= tdl[0]*v25.reall       ;
cad[1]=r0;
if (r0==0) goto l10;
  for (u0=0; u0<v25.reall       ; u0++)
 {w0= dl[0]*(id0[u0]-1       );
  q0 = tdl[0]*u0;
  for (u1=0; u1<v30.dims[1]     ; u1++)
  v6[q0+u1] = lo2[w0+dl[1]*u1];}
l10:;
  cad[31] = cad[1];
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  cad[v1+2];
r0= cad[31];
  r0=v43.reall;
  v44.dims[0]=cad[32];
if (cad[32] != v43.dims[0])
  LEMSG(119,11);
  v44.dims[1]=cad[33];
if (cad[33] != v43.dims[1])
  LEMSG(119,11);
  for (v1=0; v1<2; v1++)
  v44.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v44,inchp2); /* by INCHEAPP */
p2 = (double *) v44.valp;
ro1 = (  int  *) v43.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (v6[v1]==0 && 0==(double)ro1[v1])  p2[v1] =  1; else
    p2[v1] = v6[v1]/(double)ro1[v1];
/* INDEXA generates the following code */
p2 = (double *) v18.valp;
lo2 = (double *) v18.valp;
ro2 = (double *) v44.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v18.dims[1-u0];
id0 = (int *) v25.valp;
  cad[2]= v25.reall       ;
  cad[3]= v18.dims[1]     ;
  tdl[0] =v18.dims[1]     ;
  r0= tdl[0]*v25.reall       ;
  for (u0=0; u0<v25.reall       ; u0++)
 {w0= dl[0]*(id0[u0]-1       );
  q0 = tdl[0]*u0;
  for (u1=0; u1<v18.dims[1]     ; u1++)
   p2[w0+dl[1]*u1] = ro2[q0+u1];}
/******************   LINE 12   ******************/
   r0=v28.reall;
INCHEAPP3(v29,inchp1); /* by INCHEAPP */
   memcpy(v29.valp, v28.valp, v28.reall<<2);
/******************   LINE 13   ******************/
 v33 = v33+1; /* code for + */
/*     PFCOMPB generates the folowing code    */
   v8 = 500> v33;
/*     PFCOMPB generates the folowing code    */
   v9 = v34> 0.001;
/*  PFLOGIC Generates the following code for ^*/
v12 = v9&v8;
   if (v12!=0)
   goto lj3;
   goto lj0;
lj0:;
  for (v1=0; v1<2; v1++)
  cad[2+v1]=  v18.dims[v1+0];
cad[1]= v18.reall;
fretfp= (double *) v18.valp;
    }
