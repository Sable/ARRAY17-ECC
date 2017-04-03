#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "aplc.h"
#include "eli3lib.h"
#include "elimacros.h"
#define HEAPSIZE 2097152000
//#define BVBFLE32 102400000
#define BVBFLE32 153600000
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
   STOFM2 v44;
   STOFM3 v45;
   STOFM2 v46;
   STOFM3 v47;
   STOFM2 v48;
   STOFM3 v49;
   STOFM3 v31;
main(int argc, char * argv[])
 {char * lparm, * rparm;
  char  ltype, rtype;
    int  g19;
  int lleng= 1;
  FILE *fpl, *fpr, *fopen();
  extern int apl_sec();
  initf= 1;
  heap=(char*)amalloc(HEAPSIZE);
  //v5=(int*)amalloc(131072000); v6=(double*)amalloc(131072000);
  v5=(int*)amalloc(196608000); v6=(double*)amalloc(196608000);
 {while (--argc > 0)
  if (argc>0) {lparm = *argv; *argv = *argv + 1;}
  else rparm = *argv;}
  if( argv[1] == NULL )
    fpl= a_fopen("morgan.LEF","r");
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
    fpr= a_fopen("morgan.RIG","r");
  else
   {sprintf(cvbf, "%s.RIG", argv[1]);
    fpr= a_fopen(cvbf, "r"); }
  fscanf(fpr,"%c %d",&rtype,&rshp[0]);
  if( rtype!= 'E')  {
 printf("The type of the right arguement is mismatched.\n"); exit(99);}
  if( rshp[0]!= 3)  {
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
  morgan   (g19,ro2);
  time2 = apl_sec();
  //printf("\n execution time in ms %d\n",time2-time1);
  printf("\n The elapsed time in ms: %g\n",(time2-time1)/1000.0);
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
   free(heap); free(v5); free(v6); exit(0);}
/*              CODE SEGMENT FOR FUNCTION morgan        */
morgan   (v19,p20)
    int  v19;
  double* p20;
  { char v8, v11;
   int oldr15, v9, v12, v13, v17;
   double v10, v14, v15, v16;
   STOFM3 v18;
   STOFM3 v21;
   STOFM3 v22;
   STOFM3 v23;
   STOFM3 v24;
   STOFM3 v25;
   STOFM3 v26;
   STOFM3 v27;
   STOFM3 v32;
   STOFM3 v33;
   STOFM3 v34;
   STOFM3 v35;
   STOFM3 v36;
   STOFM3 v37;
   STOFM3 v38;
   STOFM3 v39;
   STOFM3 v40;
   STOFM3 v41;
   STOFM3 v20;
   v18.maxl = -1;
   v44.maxl= -1; v45.maxl= -1; v46.maxl= -1;
   v47.maxl= -1; v48.maxl= -1; v49.maxl= -1;
   v31.maxl = -1;
   v21.maxl = -1;
   v22.maxl = -1;
   v23.maxl = -1;
   v24.maxl = -1;
   v25.maxl = -1;
   v26.maxl = -1;
   v27.maxl = -1;
   v32.maxl = -1;
   v33.maxl = -1;
   v34.maxl = -1;
   v35.maxl = -1;
   v36.maxl = -1;
   v37.maxl = -1;
   v38.maxl = -1;
   v39.maxl = -1;
   v40.maxl = -1;
   v41.maxl = -1;
r0= rshp[0];
  for (v1=0; v1<3; v1++)
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
/* INDEXV generates the following code */
lo2 = (double *) v20.valp;
   dl[2]= t = 1;
  for (u0=0; u0<2; u0++)
   t= dl[1-u0]= t*v20.dims[2-u0];
  cad[2]= v20.dims[1]     ;
  cad[3]= v20.dims[2]     ;
  n=0;
  n += dl[0]*(1-1)           ;
  tdl[0] =v20.dims[2]     ;
  r0= tdl[0]*v20.dims[1]     ;
INCHEAPPH(v21,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
if (r0==0) goto l2;
  for (u0=0; u0<v20.dims[1]     ; u0++)
 {w0 = dl[1]*u0;
  q0 = tdl[0]*u0;
  for (u1=0; u1<v20.dims[2]     ; u1++)
   p2[q0+u1] = lo2[n+w0+dl[2]*u1];}
l2:;
  for (v1=0; v1<2; v1++)
  v21.dims[v1+0]=  cad[v1+2];
  v21.valp = cad0;
  v21.reall= cad[1];
/******************   LINE 2   ******************/
/* INDEXV generates the following code */
lo2 = (double *) v20.valp;
   dl[2]= t = 1;
  for (u0=0; u0<2; u0++)
   t= dl[1-u0]= t*v20.dims[2-u0];
  cad[2]= v20.dims[1]     ;
  cad[3]= v20.dims[2]     ;
  n=0;
  n += dl[0]*(2-1)           ;
  tdl[0] =v20.dims[2]     ;
  r0= tdl[0]*v20.dims[1]     ;
INCHEAPPH(v22,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
if (r0==0) goto l3;
  for (u0=0; u0<v20.dims[1]     ; u0++)
 {w0 = dl[1]*u0;
  q0 = tdl[0]*u0;
  for (u1=0; u1<v20.dims[2]     ; u1++)
   p2[q0+u1] = lo2[n+w0+dl[2]*u1];}
l3:;
  for (v1=0; v1<2; v1++)
  v22.dims[v1+0]=  cad[v1+2];
  v22.valp = cad0;
  v22.reall= cad[1];
/******************   LINE 3   ******************/
  for (v1=0; v1<2; v1++)
rshp[1+v1]=  v21.dims[v1+0];
rshp[0]=v21.reall;
ro2 = (double *) v21.valp;
msum     (v19,ro2);
  for (v1=0; v1<2; v1++)
  v23.dims[v1+0]=  cad[v1+2];
   r0=cad[1];
INCHEAPP3(v23,inchp2); /* by INCHEAPP */
   memcpy(v23.valp, (char *) fretfp, cad[1]<<3);
/******************   LINE 4   ******************/
  for (v1=0; v1<2; v1++)
rshp[1+v1]=  v22.dims[v1+0];
rshp[0]=v22.reall;
ro2 = (double *) v22.valp;
msum     (v19,ro2);
  for (v1=0; v1<2; v1++)
  v25.dims[v1+0]=  cad[v1+2];
   r0=cad[1];
INCHEAPP3(v25,inchp2); /* by INCHEAPP */
   memcpy(v25.valp, (char *) fretfp, cad[1]<<3);
/******************   LINE 5   ******************/
  r0=v21.reall;
  for (v1=0; v1<2; v1++)
  v34.dims[v1+0]=  v21.dims[v1+0];
INCHEAPP3(v34,inchp2); /* by INCHEAPP */
p2 = (double *) v34.valp;
lo2 = (double *) v21.valp;
  for (v1 =0; v1<r0; v1++) /* code for *. */
     p2[v1] = lo2[v1]*lo2[v1];
  for (v1=0; v1<2; v1++)
rshp[1+v1]=  v34.dims[v1+0];
rshp[0]=v34.reall;
ro2 = (double *) v34.valp;
msum     (v19,ro2);
  for (v1=0; v1<2; v1++)
  v24.dims[v1+0]=  cad[v1+2];
   r0=cad[1];
INCHEAPP3(v24,inchp2); /* by INCHEAPP */
   memcpy(v24.valp, (char *) fretfp, cad[1]<<3);
/******************   LINE 6   ******************/
  r0=v22.reall;
  for (v1=0; v1<2; v1++)
  v35.dims[v1+0]=  v22.dims[v1+0];
INCHEAPP3(v35,inchp2); /* by INCHEAPP */
p2 = (double *) v35.valp;
lo2 = (double *) v22.valp;
  for (v1 =0; v1<r0; v1++) /* code for *. */
     p2[v1] = lo2[v1]*lo2[v1];
  for (v1=0; v1<2; v1++)
rshp[1+v1]=  v35.dims[v1+0];
rshp[0]=v35.reall;
ro2 = (double *) v35.valp;
msum     (v19,ro2);
  for (v1=0; v1<2; v1++)
  v26.dims[v1+0]=  cad[v1+2];
   r0=cad[1];
INCHEAPP3(v26,inchp2); /* by INCHEAPP */
   memcpy(v26.valp, (char *) fretfp, cad[1]<<3);
/******************   LINE 7   ******************/
r0= v21.reall;
  r0=v22.reall;
  v36.dims[0]=v21.dims[0];
if (v21.dims[0] != v22.dims[0])
  LEMSG(78,7);
  v36.dims[1]=v21.dims[1];
if (v21.dims[1] != v22.dims[1])
  LEMSG(78,7);
  for (v1=0; v1<2; v1++)
  v36.dims[v1+0]=  v21.dims[v1+0];
INCHEAPP3(v36,inchp2); /* by INCHEAPP */
p2 = (double *) v36.valp;
lo2 = (double *) v21.valp;
ro2 = (double *) v22.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*ro2[v1];
  for (v1=0; v1<2; v1++)
rshp[1+v1]=  v36.dims[v1+0];
rshp[0]=v36.reall;
ro2 = (double *) v36.valp;
msum     (v19,ro2);
  for (v1=0; v1<2; v1++)
  v27.dims[v1+0]=  cad[v1+2];
   r0=cad[1];
INCHEAPP3(v27,inchp2); /* by INCHEAPP */
   memcpy(v27.valp, (char *) fretfp, cad[1]<<3);
/******************   LINE 8   ******************/
  r0=v25.reall;
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v25.dims[v1+0];
lo2 = (double *) v25.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (lo2[v1]==0 && 0==(double)v19) v6[v1] =  1; else
   v6[v1] = lo2[v1]/(double)v19;
  for (v1=0; v1<2; v1++)
  v39.dims[v1+0]=  cad[32+v1];
  r0=cad[31];
  for (v1=0; v1<2; v1++)
  v39.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v39,inchp2); /* by INCHEAPP */
p2 = (double *) v39.valp;
  for (v1 =0; v1<r0; v1++) /* code for *. */
     p2[v1] = v6[v1]*v6[v1];
  r0=v26.reall;
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v26.dims[v1+0];
lo2 = (double *) v26.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (lo2[v1]==0 && 0==(double)v19) v6[v1] =  1; else
   v6[v1] = lo2[v1]/(double)v19;
r0= cad[31];
if (cad[32] != v39.dims[0])
  LEMSG(111,8);
if (cad[33] != v39.dims[1])
  LEMSG(111,8);
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  cad[32+v1];
ro2 = (double *) v39.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for - */
    v6[v1] = v6[v1]-ro2[v1];
  r0 =   cad[31];
  cad[31] =  r0;
  for (v1 =0; v1<cad[31]; v1++) /* code for | */
    v6[v1] =  fabs(v6[v1]);
  for (v1=0; v1<2; v1++)
  v37.dims[v1+0]=  cad[32+v1];
  r0=cad[31];
  for (v1=0; v1<2; v1++)
  v37.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v37,inchp2); /* by INCHEAPP */
p2 = (double *) v37.valp;
  for (v1 =0; v1<r0; v1++) /* code for *. */
     p2[v1] = pow(v6[v1],0.5);
  r0=v23.reall;
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v23.dims[v1+0];
lo2 = (double *) v23.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (lo2[v1]==0 && 0==(double)v19) v6[v1] =  1; else
   v6[v1] = lo2[v1]/(double)v19;
  for (v1=0; v1<2; v1++)
  v40.dims[v1+0]=  cad[32+v1];
  r0=cad[31];
  for (v1=0; v1<2; v1++)
  v40.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v40,inchp2); /* by INCHEAPP */
p2 = (double *) v40.valp;
  for (v1 =0; v1<r0; v1++) /* code for *. */
     p2[v1] = v6[v1]*v6[v1];
  r0=v24.reall;
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v24.dims[v1+0];
lo2 = (double *) v24.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (lo2[v1]==0 && 0==(double)v19) v6[v1] =  1; else
   v6[v1] = lo2[v1]/(double)v19;
r0= cad[31];
if (cad[32] != v40.dims[0])
  LEMSG(98,8);
if (cad[33] != v40.dims[1])
  LEMSG(98,8);
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  cad[32+v1];
ro2 = (double *) v40.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for + */
    v6[v1] = v6[v1]+ro2[v1];
  for (v1 =0; v1<cad[31]; v1++) /* code for *. */
    v6[v1] = pow(v6[v1],0.5);
  r0 =   cad[31];
  cad[31] =  r0;
  for (v1 =0; v1<cad[31]; v1++) /* code for | */
    v6[v1] =  fabs(v6[v1]);
r0= cad[31];
  r0=v37.reall;
  v38.dims[0]=cad[32];
if (cad[32] != v37.dims[0])
  LEMSG(106,8);
  v38.dims[1]=cad[33];
if (cad[33] != v37.dims[1])
  LEMSG(106,8);
  for (v1=0; v1<2; v1++)
  v38.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v38,inchp2); /* by INCHEAPP */
p2 = (double *) v38.valp;
ro2 = (double *) v37.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = v6[v1]*ro2[v1];
 v9 = v19*v19; /* code for *. */
r0= v23.reall;
  r0=v25.reall;
  cad[32]=v23.dims[0];
if (v23.dims[0] != v25.dims[0])
  LEMSG(87,8);
  cad[33]=v23.dims[1];
if (v23.dims[1] != v25.dims[1])
  LEMSG(87,8);
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v23.dims[v1+0];
lo2 = (double *) v23.valp;
ro2 = (double *) v25.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
    v6[v1] = lo2[v1]*ro2[v1];
  for (v1=0; v1<2; v1++)
  v41.dims[v1+0]=  cad[32+v1];
  r0=cad[31];
  for (v1=0; v1<2; v1++)
  v41.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v41,inchp2); /* by INCHEAPP */
p2 = (double *) v41.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (v6[v1]==0 && 0==(double)v9)  p2[v1] =  1; else
    p2[v1] = v6[v1]/(double)v9;
  r0=v27.reall;
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v27.dims[v1+0];
lo2 = (double *) v27.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (lo2[v1]==0 && 0==(double)v19) v6[v1] =  1; else
   v6[v1] = lo2[v1]/(double)v19;
r0= cad[31];
if (cad[32] != v41.dims[0])
  LEMSG(85,8);
if (cad[33] != v41.dims[1])
  LEMSG(85,8);
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  cad[32+v1];
ro2 = (double *) v41.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for - */
    v6[v1] = v6[v1]-ro2[v1];
r0= cad[31];
  r0=v38.reall;
  v18.dims[0]=cad[32];
if (cad[32] != v38.dims[0])
  LEMSG(93,8);
  v18.dims[1]=cad[33];
if (cad[33] != v38.dims[1])
  LEMSG(93,8);
  for (v1=0; v1<2; v1++)
  v18.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v18,inchp2); /* by INCHEAPP */
p2 = (double *) v18.valp;
ro2 = (double *) v38.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (v6[v1]==0 && 0==ro2[v1])  p2[v1] =  1; else
    p2[v1] = v6[v1]/ro2[v1];
lj0:;
  for (v1=0; v1<2; v1++)
  cad[2+v1]=  v18.dims[v1+0];
cad[1]= v18.reall;
fretfp= (double *) v18.valp;
    }
/*              CODE SEGMENT FOR FUNCTION msum          */
msum     (v29,p30)
    int  v29;
  double* p30;
  { char v8, v11;
   int oldr15, v9, v12, v13, v17;
   double v10, v14, v15, v16;
   STOFM3 v28;
   STOFM3 v42;
   STOFM3 v43;
   STOFM3 v30;
   v28.maxl = -1;
   v42.maxl = -1;
   v43.maxl = -1;
r0= rshp[0];
  for (v1=0; v1<2; v1++)
  v30.dims[v1+0]=rshp[v1+1];
v30.reall= v30.maxl= r0;
 inchp2; v30.valp= &heap[r15]; /* by INCHEAP2V */
ro2= (double *) v30.valp;
  for (v1=0; v1<r0; v1++)
ro2[v1]= p30[v1];
new_v=0;
lj1:
/******************   LINE 1   ******************/
/*   GENSCAN generates the following code */
p2 = (double *) v31.valp;
ro2 = (double *) v30.valp;
  for (v1=0; v1<2; v1++)
  v31.dims[v1+0]=  v30.dims[v1+0];
  r0 =   v30.reall;
INCHEAPP3(v31,inchp2); /* by INCHEAPP */
p2 = (double *) v31.valp;
if (r0==0) goto l4;
r0=v30.dims[1]     ;
r1=v30.dims[0]     ;
  for (u0=0; u0<r1; u0++)
  {v1= r0*u0;
  p2[v1] = d= ro2[v1];
  for (u1=1; u1<r0; u1++)
   p2[v1+u1]=d=d+ro2[v1+u1];}
l4:;
 v9 =  -v29; /* code for - */
/***** PFCATENA *****/
  r0 = cad[1]= 1+1;
  cad[1] =r0 =2;
  v5[0] = 0;
  v5[1]= v9;
/*   PFDROP generates the following code */
ro2 = (double *) v31.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v31.dims[1-u0];
  r0=t=1;
cad[3]          = max(0, v31.dims[1]     -abs(v5[1]));
  t=tdl[0] = t*cad[3]          ;
cad[2]          = max(0,v31.dims[0]     -abs(v5[0]));
  r0=r0*cad[2]          ;
  r0=r0*cad[3]          ;
INCHEAPPH(v42,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  for (u0=0; u0<cad[2]          ; u0++)
 {if (0>v5[0])
  w0 = dl[0]*u0;
   else
  w0 = dl[0]*(v5[0]+u0);
  q0 = tdl[0]*u0;
  for (u1=0; u1<cad[3]          ; u1++)
  if (0>v5[1])
   p2[q0+u1] = ro2[w0+u1];
   else
   p2[q0+u1]=ro2[w0+(u1+v5[1])];}
  for (v1=0; v1<2; v1++)
  v42.dims[v1+0]=  cad[v1+2];
  v42.valp = cad0;
  v42.reall= cad[1];
/***** PFCATENA *****/
ro2 = (double *) v42.valp;
tdl[0]=dl[0];
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v42.dims[1-u0];
cad[2]=v42.dims[0]     ;
cad[3]=v42.dims[1]     +1;
  tl=1;
  tl= tl*v42.dims[0]     ;
  r0= tl*cad[3];
INCHEAPPH(v43,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  j=n=i=0;
  for (v1=0; v1<tl; v1++)
  {
 p2[j]=0;
  j++;
  for (u1=0; u1<v42.dims[1]     ; u1++)
 p2[j+u1]=ro2[i+u1];
  i+=v42.dims[1]     ; j+=v42.dims[1]     ;}
  for (v1=0; v1<2; v1++)
  v43.dims[v1+0]=  cad[v1+2];
  v43.valp = cad0;
  v43.reall= cad[1];
 v9 = v29-1; /* code for - */
/***** PFCATENA *****/
  r0 = cad[1]= 1+1;
  cad[1] =r0 =2;
  v5[0] = 0;
  v5[1]= v9;
/*   PFDROP generates the following code */
ro2 = (double *) v31.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v31.dims[1-u0];
  r0=t=1;
cad[3]          = max(0, v31.dims[1]     -abs(v5[1]));
  t=tdl[0] = t*cad[3]          ;
cad[2]          = max(0,v31.dims[0]     -abs(v5[0]));
  r0=r0*cad[2]          ;
  r0=r0*cad[3]          ;
cad[1]=r0;
  for (u0=0; u0<cad[2]          ; u0++)
 {if (0>v5[0])
  w0 = dl[0]*u0;
   else
  w0 = dl[0]*(v5[0]+u0);
  q0 = tdl[0]*u0;
  for (u1=0; u1<cad[3]          ; u1++)
  if (0>v5[1])
  v6[q0+u1] = ro2[w0+u1];
   else
  v6[q0+u1]=ro2[w0+(u1+v5[1])];}
  cad[31] = cad[1];
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  cad[v1+2];
r0= cad[31];
  r0=v43.reall;
  v28.dims[0]=cad[32];
if (cad[32] != v43.dims[0])
  LEMSG(40,1);
  v28.dims[1]=cad[33];
//printf("%d %d\n",cad[33],v43.dims[1]);
/*if (cad[33] != v43.dims[1])
  LEMSG(40,1);*/
  for (v1=0; v1<2; v1++)
  v28.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v28,inchp2); /* by INCHEAPP */
p2 = (double *) v28.valp;
ro2 = (double *) v43.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
     p2[v1] = v6[v1]-ro2[v1];
lj0:;
  for (v1=0; v1<2; v1++)
  cad[2+v1]=  v28.dims[v1+0];
cad[1]= v28.reall;
fretfp= (double *) v28.valp;
    }
