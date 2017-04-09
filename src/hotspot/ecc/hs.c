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
   int c20[2] = {0,1};
   int c19[1]= {0x40000000};
   int c29[2] = {0,-1};
   int c30[1]= {0x80000000};
   int c31[2] = {-1,0};
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
   STOFM2 v62;
   STOFM3 v63;
   STOFM2 v64;
   STOFM3 v65;
   STOFM2 v66;
   STOFM3 v67;
main(int argc, char * argv[])
 {char * lparm, * rparm;
  char  ltype, rtype;
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
    fpl= a_fopen("hotspot.LEF","r");
  else
   {sprintf(cvbf, "%s.LEF", argv[1]);
    fpl= a_fopen(cvbf, "r"); }
  fscanf(fpl,"%c %d",&ltype,&lshp[0]);
  if( ltype!= 'E')  {
 printf("The type of the left arguement is mismatched.\n"); exit(99);}
  if( lshp[0]!= 2)  {
 printf("The rank of the left arguement is mismatched.\n"); exit(99);}
  for( i = 1; i < 1 + lshp[0]; ++i)  {
  fscanf(fpl," %d",&lshp[i]); lleng *= lshp[i];}
  while (fgetc(fpl) != '\n');
  lshp[0]= r0 = lleng;inchp2;
  lop= &heap[r15]; p2 = (double *) lop;
  for(i = 0; i < lleng; ++i)  {
    fscanf(fpl,"%lf",p2);
    ++p2;}
  lleng = 1;
  if( argv[1] == NULL )
    fpr= a_fopen("hotspot.RIG","r");
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
  hotspot  (lo2,ro2);
  time2 = apl_sec();
//  printf("\n execution time in ms %d\n",time2-time1);
  printf("\n The elapsed time in ms: %g\n",(time2-time1)/1000.0);
/*   OUTPUT generates the following code */
/*printf("Result:\n");
for(u0=0; u0<10; u0++){
    printf(" %g", fretfp[u0]);
}
printf("\n");*/
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
/*              CODE SEGMENT FOR FUNCTION hotspot       */
hotspot  (p19,p20)
  double* p19;
  double* p20;
  { char v8, v11;
   int oldr15, v9, v12, v13, v17;
   double v10, v14, v15, v16;
   STOFM3 v18;
  double v21;
  double v22;
  double v23;
  double v24;
    int  v26;
   STOFM3 v28;
   STOFM3 v29;
   STOFM3 v30;
   STOFM3 v31;
   STOFM3 v32;
   STOFM3 v33;
   STOFM3 v34;
   STOFM3 v35;
    int  v36;
    int  v37;
  double v38;
  double v39;
    int  v49[2];
    int  v50[2];
   STOFM3 v51;
   STOFM3 v52;
    int  v53[2];
   STOFM3 v54;
   STOFM3 v55;
   STOFM3 v56;
   STOFM3 v57;
   STOFM3 v58;
   STOFM3 v59;
   STOFM3 v60;
   STOFM3 v61;
   STOFM3 v19;
   STOFM3 v20;
   v18.maxl = -1;
   v62.maxl= -1; v63.maxl= -1; v64.maxl= -1;
   v65.maxl= -1; v66.maxl= -1; v67.maxl= -1;
   v28.maxl = -1;
   v29.maxl = -1;
   v30.maxl = -1;
   v31.maxl = -1;
   v32.maxl = -1;
   v33.maxl = -1;
   v34.maxl = -1;
   v35.maxl = -1;
   v51.maxl = -1;
   v52.maxl = -1;
   v54.maxl = -1;
   v55.maxl = -1;
   v56.maxl = -1;
   v57.maxl = -1;
   v58.maxl = -1;
   v59.maxl = -1;
   v60.maxl = -1;
   v61.maxl = -1;
r0= lshp[0];
  for (v1=0; v1<2; v1++)
  v19.dims[v1+0]=lshp[v1+1];
if (initf == 1)
  {v19.valp= lop;
  v19.reall= v19.maxl= r0;
  } else {
v19.reall= v19.maxl= r0;
 inchp2; v19.valp= &heap[r15]; /* by INCHEAP2V */
ro2= (double *) v19.valp;
  for (v1=0; v1<r0; v1++)
ro2[v1]= p19[v1];}
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
/******************   LINE 2   ******************/
/******************   LINE 3   ******************/
/******************   LINE 4   ******************/
/******************   LINE 5   ******************/
/******************   LINE 6   ******************/
/******************   LINE 7   ******************/
/******************   LINE 8   ******************/
/******************   LINE 9   ******************/
/******************   LINE 10   ******************/
/* TAKRHO generates the following instructions: */
ro2 = (double *) v19.valp;
  v9= v19.dims[0];
  v36 = v9;
 v39 = 0.016/(double)v9; /* code for % */
/* TAKRHO generates the following instructions: */
ro2 = (double *) v19.valp;
  v9= v19.dims[1];
  v37 = v9;
 v38 = 0.016/(double)v9; /* code for % */
 v10 = v38*v39; /* code for * */
 v14 = 0.0005*v10; /* code for * */
 v10 = 1750000*v14; /* code for * */
 v21 = 0.5*v10; /* code for * */
/******************   LINE 11   ******************/
 v10 = 0.0005*v39; /* code for * */
 v14 = 100*v10; /* code for * */
 v10 = 2*v14; /* code for * */
 v22 = v38/v10; /* code for % */
/******************   LINE 12   ******************/
 v10 = 0.0005*v38; /* code for * */
 v14 = 100*v10; /* code for * */
 v10 = 2*v14; /* code for * */
 v23 = v39/v10; /* code for % */
/******************   LINE 13   ******************/
 v10 = v39*v38; /* code for * */
 v14 = 100*v10; /* code for * */
 v24 = 0.0005/v14; /* code for % */
/******************   LINE 14   ******************/
/******************   LINE 15   ******************/
  v26 = 0;
/******************   LINE 16   ******************/
/***** PFCATENA *****/
  r0 = cad[1]= 1+1;
  v49[0] = v36;
  v49[1]= v37;
/*   RESHAPE generates the following code */
  r0=1;
  for (v1=0; v1<2; v1++)
  {cad[2+v1] =v49[v1];
   r0= r0*cad[2+v1];}
INCHEAPPH(v35,inchp1, p1 = (   int  *) cad0 ); /* by INCHEAPP */
  for (v1=0; v1<r0; v1++)
 p1[v1] = 2;
  for (v1=0; v1<2; v1++)
  v35.dims[v1+0]=  cad[v1+2];
  v35.valp = cad0;
  v35.reall= cad[1];
  for (v1=0; v1<2; v1++)
  v34.dims[v1+0]=  v35.dims[v1+0];
   r0=v35.reall;
INCHEAPP3(v34,inchp1); /* by INCHEAPP */
   memcpy(v34.valp, v35.valp, v35.reall<<2);
/******************   LINE 17   ******************/
 v9 = v37-1; /* code for - */
/***** PFCATENA *****/
  r0 = cad[1]= 1+1;
  v50[0] = 0;
  v50[1]= v9;
/* INDEXA generates the following code */
p1 = (  int  *) v34.valp;
lo1 = (  int  *) v34.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v34.dims[1-u0];
  cad[2]= v34.dims[0]     ;
  cad[3]= 2               ;
  tdl[0] =2               ;
  r0= tdl[0]*v34.dims[0]     ;
  for (u0=0; u0<v34.dims[0]     ; u0++)
  {w0 = dl[0]*u0;
  q0 = tdl[0]*u0;
  for (u1=0; u1<2               ; u1++)
   p1[w0+dl[1]*(v50[u1]         )] = 1;}
/******************   LINE 18   ******************/
 v9 = v36-1; /* code for - */
/***** PFCATENA *****/
  r0 = cad[1]= 1+1;
  v53[0] = 0;
  v53[1]= v9;
/* INDEXA generates the following code */
p1 = (  int  *) v35.valp;
lo1 = (  int  *) v35.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v35.dims[1-u0];
  cad[2]= 2               ;
  cad[3]= v35.dims[1]     ;
  tdl[0] =v35.dims[1]     ;
  r0= tdl[0]*2               ;
  for (u0=0; u0<2               ; u0++)
 {w0= dl[0]*(v53[u0]         );
  q0 = tdl[0]*u0;
  for (u1=0; u1<v35.dims[1]     ; u1++)
   p1[w0+dl[1]*u1] = 1;}
lj19:
/******************   LINE 19   ******************/
 v26 = v26+1; /* code for + */
/*     PFCOMPB generates the folowing code    */
   v8 = 20< v26;
   if (v8!=0)
   goto lj28;
lj20:
/******************   LINE 20   ******************/
/*   PFDROP generates the following code */
   r0=2;
INCHEAPP3(v62,inchp1); /* by INCHEAPP */
 p1 = (  int  *) v62.valp;
r1= 2>>5;
v1=0;
boolcvi( p1, c19, 0, 2);
lo0 = (  int  *) v62.valp;
ro2 = (double *) v19.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v19.dims[1-u0];
  r0=t=1;
cad[3]          = max(0, v19.dims[1]     -abs(lo0[1]));
  t=tdl[0] = t*cad[3]          ;
cad[2]          = max(0,v19.dims[0]     -abs(lo0[0]));
  r0=r0*cad[2]          ;
  r0=r0*cad[3]          ;
INCHEAPPH(v54,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  for (u0=0; u0<cad[2]          ; u0++)
 {if (0>lo0[0])
  w0 = dl[0]*u0;
   else
  w0 = dl[0]*(lo0[0]+u0);
  q0 = tdl[0]*u0;
  for (u1=0; u1<cad[3]          ; u1++)
  if (0>lo0[1])
   p2[q0+u1] = ro2[w0+u1];
   else
   p2[q0+u1]=ro2[w0+(u1+lo0[1])];}
  for (v1=0; v1<2; v1++)
  v54.dims[v1+0]=  cad[v1+2];
  v54.valp = cad0;
  v54.reall= cad[1];
/***** PFCATENA *****/
lo2 = (double *) v54.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v54.dims[1-u0];
cad[2]=v54.dims[0]     ;
cad[3]=v54.dims[1]     +1;
  tl=1;
  tl= tl*v54.dims[0]     ;
  r0= tl*cad[3];
INCHEAPPH(v28,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  j=n=i=0;
  for (v1=0; v1<tl; v1++)
  {
  for (u1=0; u1<v54.dims[1]     ; u1++)
 p2[j+u1]=lo2[n+u1];
  n+=v54.dims[1]     ;
  j+=v54.dims[1]     ;
 p2[j]=0;
  j++;}
  for (v1=0; v1<2; v1++)
  v28.dims[v1+0]=  cad[v1+2];
  v28.valp = cad0;
  v28.reall= cad[1];
/******************   LINE 21   ******************/
/*   PFDROP generates the following code */
ro2 = (double *) v19.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v19.dims[1-u0];
  r0=t=1;
cad[3]          = max(0, v19.dims[1]     -abs(c29[1]));
  t=tdl[0] = t*cad[3]          ;
cad[2]          = max(0,v19.dims[0]     -abs(c29[0]));
  r0=r0*cad[2]          ;
  r0=r0*cad[3]          ;
INCHEAPPH(v55,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  for (u0=0; u0<cad[2]          ; u0++)
 {if (0>c29[0])
  w0 = dl[0]*u0;
   else
  w0 = dl[0]*(c29[0]+u0);
  q0 = tdl[0]*u0;
  for (u1=0; u1<cad[3]          ; u1++)
  if (0>c29[1])
   p2[q0+u1] = ro2[w0+u1];
   else
   p2[q0+u1]=ro2[w0+(u1+c29[1])];}
  for (v1=0; v1<2; v1++)
  v55.dims[v1+0]=  cad[v1+2];
  v55.valp = cad0;
  v55.reall= cad[1];
/***** PFCATENA *****/
ro2 = (double *) v55.valp;
tdl[0]=dl[0];
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v55.dims[1-u0];
cad[2]=v55.dims[0]     ;
cad[3]=v55.dims[1]     +1;
  tl=1;
  tl= tl*v55.dims[0]     ;
  r0= tl*cad[3];
INCHEAPPH(v29,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  j=n=i=0;
  for (v1=0; v1<tl; v1++)
  {
 p2[j]=0;
  j++;
  for (u1=0; u1<v55.dims[1]     ; u1++)
 p2[j+u1]=ro2[i+u1];
  i+=v55.dims[1]     ; j+=v55.dims[1]     ;}
  for (v1=0; v1<2; v1++)
  v29.dims[v1+0]=  cad[v1+2];
  v29.valp = cad0;
  v29.reall= cad[1];
/******************   LINE 22   ******************/
r0= v34.reall;
  r0=v19.reall;
if (v34.dims[0] != v19.dims[0])
  LEMSG(169,22);
if (v34.dims[1] != v19.dims[1])
  LEMSG(169,22);
lo1 = (  int  *) v34.valp;
ro20 = (double *) v19.valp; // ro2 = (double *) v19.valp;
r0= v28.reall;
  r0=v29.reall;
if (v28.dims[0] != v29.dims[0])
  LEMSG(165,22);
if (v28.dims[1] != v29.dims[1])
  LEMSG(165,22);
lo2 = (double *) v28.valp;
ro2 = (double *) v29.valp;
r0= v29.reall;
  r0=v19.reall;
  v30.dims[0]=v29.dims[0];
if (v29.dims[0] != v19.dims[0])
  LEMSG(167,22);
  v30.dims[1]=v29.dims[1];
if (v29.dims[1] != v19.dims[1])
  LEMSG(167,22);
  for (v1=0; v1<2; v1++)
  v30.dims[v1+0]=  v29.dims[v1+0];
INCHEAPP3(v30,inchp2); /* by INCHEAPP */
p2 = (double *) v30.valp;
lo20 = (double *) v29.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
     p2[v1] = (lo2[v1]+ro2[v1])-lo1[v1]*ro20[v1];
     //p2[v1] = (lo2[v1]+ro2[v1])-lo1[v1]*ro2[v1];
/******************   LINE 23   ******************/
/*   PFDROP generates the following code */
   r0=2;
INCHEAPP3(v62,inchp1); /* by INCHEAPP */
 p1 = (  int  *) v62.valp;
r1= 2>>5;
v1=0;
boolcvi( p1, c30, 0, 2);
lo0 = (  int  *) v62.valp;
ro2 = (double *) v19.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v19.dims[1-u0];
  r0=t=1;
cad[3]          = max(0, v19.dims[1]     -abs(lo0[1]));
  t=tdl[0] = t*cad[3]          ;
cad[2]          = max(0,v19.dims[0]     -abs(lo0[0]));
  r0=r0*cad[2]          ;
  r0=r0*cad[3]          ;
INCHEAPPH(v56,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  for (u0=0; u0<cad[2]          ; u0++)
 {if (0>lo0[0])
  w0 = dl[0]*u0;
   else
  w0 = dl[0]*(lo0[0]+u0);
  q0 = tdl[0]*u0;
  for (u1=0; u1<cad[3]          ; u1++)
  if (0>lo0[1])
   p2[q0+u1] = ro2[w0+u1];
   else
   p2[q0+u1]=ro2[w0+(u1+lo0[1])];}
  for (v1=0; v1<2; v1++)
  v56.dims[v1+0]=  cad[v1+2];
  v56.valp = cad0;
  v56.reall= cad[1];
/***** PFCATENA *****/
lo2 = (double *) v56.valp;
cad[3]=v56.dims[1]     ;
cad[2]=v56.dims[0]     +1;
  r0= 1;
  r0= r0*cad[2];
  r0= r0*cad[3];
INCHEAPPH(v31,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  for (v1=0; v1<v56.reall; v1++)
      p2[v1] = lo2[v1];
j= v56.reall;
  for (v1=0; v1<cad[3]; v1++)
      p2[v1+j]= 0;
  for (v1=0; v1<2; v1++)
  v31.dims[v1+0]=  cad[v1+2];
  v31.valp = cad0;
  v31.reall= cad[1];
/******************   LINE 24   ******************/
/*   PFDROP generates the following code */
ro2 = (double *) v19.valp;
   dl[1]= t = 1;
  for (u0=0; u0<1; u0++)
   t= dl[0-u0]= t*v19.dims[1-u0];
  r0=t=1;
cad[3]          = max(0, v19.dims[1]     -abs(c31[1]));
  t=tdl[0] = t*cad[3]          ;
cad[2]          = max(0,v19.dims[0]     -abs(c31[0]));
  r0=r0*cad[2]          ;
  r0=r0*cad[3]          ;
INCHEAPPH(v57,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  for (u0=0; u0<cad[2]          ; u0++)
 {if (0>c31[0])
  w0 = dl[0]*u0;
   else
  w0 = dl[0]*(c31[0]+u0);
  q0 = tdl[0]*u0;
  for (u1=0; u1<cad[3]          ; u1++)
  if (0>c31[1])
   p2[q0+u1] = ro2[w0+u1];
   else
   p2[q0+u1]=ro2[w0+(u1+c31[1])];}
  for (v1=0; v1<2; v1++)
  v57.dims[v1+0]=  cad[v1+2];
  v57.valp = cad0;
  v57.reall= cad[1];
/***** PFCATENA *****/
ro2 = (double *) v57.valp;
tdl[0]=dl[0];
cad[3]=v57.dims[1]     ;
cad[2]=v57.dims[0]     +1;
  r0= 1;
  r0= r0*cad[2];
  r0= r0*cad[3];
INCHEAPPH(v32,inchp2, p2 = ( double *) cad0 ); /* by INCHEAPP */
  for (v1=0; v1<cad[3]; v1++)
      p2[v1] = 0;
j= cad[3];
  for (v1=0; v1<v57.reall; v1++)
      p2[v1+j]= ro2[v1];
  for (v1=0; v1<2; v1++)
  v32.dims[v1+0]=  cad[v1+2];
  v32.valp = cad0;
  v32.reall= cad[1];
/******************   LINE 25   ******************/
r0= v35.reall;
  r0=v19.reall;
if (v35.dims[0] != v19.dims[0])
  LEMSG(192,25);
if (v35.dims[1] != v19.dims[1])
  LEMSG(192,25);
lo1 = (  int  *) v35.valp;
ro20 = (double *) v19.valp; //ro2 = (double *) v19.valp;
r0= v31.reall;
  r0=v32.reall;
if (v31.dims[0] != v32.dims[0])
  LEMSG(188,25);
if (v31.dims[1] != v32.dims[1])
  LEMSG(188,25);
lo2 = (double *) v31.valp;
ro2 = (double *) v32.valp;
r0= v32.reall;
  r0=v19.reall;
  v33.dims[0]=v32.dims[0];
if (v32.dims[0] != v19.dims[0])
  LEMSG(190,25);
  v33.dims[1]=v32.dims[1];
if (v32.dims[1] != v19.dims[1])
  LEMSG(190,25);
  for (v1=0; v1<2; v1++)
  v33.dims[v1+0]=  v32.dims[v1+0];
INCHEAPP3(v33,inchp2); /* by INCHEAPP */
p2 = (double *) v33.valp;
lo20 = (double *) v32.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
     p2[v1] = (lo2[v1]+ro2[v1])-lo1[v1]*ro20[v1];
     //p2[v1] = (lo2[v1]+ro2[v1])-lo1[v1]*ro2[v1];
/*
m1: 28
m2: 29
x : 30
n1: 31
n2: 32
y : 33
c1: 34
*/
/*printf("c1\n");
for(u0=0; u0<10; u0++){
    printf(" %d", ((int*)v34.valp)[u0]);
}*/
/******************   LINE 26   ******************/
  r0=v19.reall;
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v19.dims[v1+0];
ro2 = (double *) v19.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
    v6[v1] = 80-ro2[v1];
  for (v1=0; v1<2; v1++)
  v60.dims[v1+0]=  cad[32+v1];
  r0=cad[31];
  for (v1=0; v1<2; v1++)
  v60.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v60,inchp2); /* by INCHEAPP */
p2 = (double *) v60.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (v6[v1]==0 && 0==v24)  p2[v1] =  1; else
    p2[v1] = v6[v1]/v24;
  r0=v33.reall;
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v33.dims[v1+0];
lo2 = (double *) v33.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (lo2[v1]==0 && 0==v23) v6[v1] =  1; else
   v6[v1] = lo2[v1]/v23;
r0= cad[31];
  r0=v60.reall;
  v61.dims[0]=cad[32];
if (cad[32] != v60.dims[0])
  LEMSG(211,26);
  v61.dims[1]=cad[33];
if (cad[33] != v60.dims[1])
  LEMSG(211,26);
  for (v1=0; v1<2; v1++)
  v61.dims[v1+0]=  cad[32+v1];
INCHEAPP3(v61,inchp2); /* by INCHEAPP */
p2 = (double *) v61.valp;
ro2 = (double *) v60.valp;
  for (v1 =0; v1<r0; v1++) /* code for + */
     p2[v1] = v6[v1]+ro2[v1];
  r0=v30.reall;
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v30.dims[v1+0];
lo2 = (double *) v30.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (lo2[v1]==0 && 0==v22) v6[v1] =  1; else
   v6[v1] = lo2[v1]/v22;
r0= cad[31];
if (cad[32] != v61.dims[0])
  LEMSG(207,26);
if (cad[33] != v61.dims[1])
  LEMSG(207,26);
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  cad[32+v1];
ro2 = (double *) v61.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for + */
    v6[v1] = v6[v1]+ro2[v1];
r0= v20.reall;
if (cad[32] != v20.dims[0])
  LEMSG(203,26);
if (cad[33] != v20.dims[1])
  LEMSG(203,26);
  cad[31]=r0;
  for (v1=0; v1<2; v1++)
  cad[32+v1]=  v20.dims[v1+0];
lo2 = (double *) v20.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for + */
    v6[v1] = lo2[v1]+v6[v1];
 v10 = (1.458333333e-7)/v21; /* code for % */
  for (v1 =0; v1<cad[31]; v1++) /* code for * */
    v6[v1] = v10*v6[v1];
r0= v19.reall;
if (v19.dims[0] != cad[32])
  LEMSG(197,26);
if (v19.dims[1] != cad[33])
  LEMSG(197,26);
p2 = (double *) v19.valp;
lo2 = (double *) v19.valp;
  for (v1 =0; v1<v19.reall; v1++) /* code for + */
     p2[v1] = lo2[v1]+v6[v1];
/*printf("temp:\n");
for(u0=0; u0<10; u0++){
    printf(" %g", ((double*)v19.valp)[u0]);
}
printf("\n");*/
/******************   LINE 27   ******************/
  goto lj19;
lj28:
/******************   LINE 28   ******************/
  for (v1=0; v1<2; v1++)
  v18.dims[v1+0]=  v19.dims[v1+0];
   r0=v19.reall;
INCHEAPP3(v18,inchp2); /* by INCHEAPP */
   memcpy(v18.valp, v19.valp, v19.reall<<3);
lj0:;
  for (v1=0; v1<2; v1++)
  cad[2+v1]=  v18.dims[v1+0];
cad[1]= v18.reall;
fretfp= (double *) v18.valp;
    }
