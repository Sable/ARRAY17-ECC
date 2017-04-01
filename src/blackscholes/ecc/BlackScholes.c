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
   int lshp[8], rshp[48], cad[50], dl[7], tdl[7], vdl[7];
   int * p0, * p1, * lo0, * lo1, * ro0,* ro1,* t0,* t1,* p10,* p11,*p12;
   int * lo13, * lo10,* ro13, * ro10, * lo11, * ro11,* lo12,* ro12;
   int * id0, * id1, * id2, * id3, * id4, * id5, * id6;
   double * p2,* t2,* lo2,* ro2,* p20,* p21,* p22,* lo24,* ro24,* lo25;
  double * lo20,* ro20,* lo21,* ro21,* lo22,* ro22,* lo23,* ro23,* ro25;
   char *ro30, * p3, *t3, * lo3, * ro3, *pTarg, *pSrc, *pBuff0, *pBuff1;
   STOFM2 v74;
   STOFM3 v75;
   STOFM2 v76;
   STOFM3 v77;
   STOFM2 v78;
   STOFM3 v79;
    int  v19;
   STOFM2 v21;
   STOFM2 v22;
   STOFM2 v23;
   STOFM2 v24;
   STOFM2 v25;
   STOFM2 v27;
main(int argc, char * argv[])
 {char * lparm, * rparm;
  char  ltype, rtype[6];
int rrnk[6]= {1,1,1,1,1,1};
    int  g19;
  int lleng= 1;
  FILE *fpl, *fpr[6], *fopen();
  extern int apl_sec();
  initf= 1;
  heap=(char*)amalloc(HEAPSIZE);
  v5=(int*)amalloc(131072000); v6=(double*)amalloc(131072000);
 {while (--argc > 0)
  if (argc>0) {lparm = *argv; *argv = *argv + 1;}
  else rparm = *argv;}
  if( argv[1] == NULL )
    fpl= a_fopen("BlkSchls.LEF","r");
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
  fscanf(fpl,"%d",&v19);
  lleng = 1;
  if( argv[1] == NULL )
  for (j= 0; j<6; j++)
     {sprintf(cvbf, "BlkSchls.RIG%d", j);
    fpr[j]= a_fopen(cvbf,"r");}
  else
  for (j= 0; j<6; j++)
   {sprintf(cvbf, "%s.RIG%1d", argv[1],j);
    fpr[j]= a_fopen(cvbf, "r"); }
  for (j= 0; j<6; j++) {lleng=1;
  fscanf(fpr[j],"%c %d",&rtype[j],&rshp[8*j]);
  if( rtype[j]!= "EEEEEC"[j])  {
 printf("The type of one right arguement is mismatched.\n"); exit(99);}
  if( rshp[8*j]!= rrnk[j])  {
 printf("The rank of one right arguement is mismatched.\n"); exit(99);}
  for( i = 1; i < 1 + rshp[8*j]; ++i)  {
  fscanf(fpr[j]," %d",&rshp[8*j+i]); lleng *= rshp[8*j+i];}
  rshp[8*j]= lleng;
  while (fgetc(fpr[j]) != '\n');}
  v21.maxl= v21.reall= r0 = lleng= rshp[0];inchp2;
  v21.valp= &heap[r15]; p2 = (double *) v21.valp;
  for(i = 0; i < lleng; ++i)  {
    fscanf(fpr[0],"%lf",p2);
    ++p2;}
  v22.maxl= v22.reall= r0 = lleng= rshp[8];inchp2;
  v22.valp= &heap[r15]; p2 = (double *) v22.valp;
  for(i = 0; i < lleng; ++i)  {
    fscanf(fpr[1],"%lf",p2);
    ++p2;}
  v23.maxl= v23.reall= r0 = lleng= rshp[16];inchp2;
  v23.valp= &heap[r15]; p2 = (double *) v23.valp;
  for(i = 0; i < lleng; ++i)  {
    fscanf(fpr[2],"%lf",p2);
    ++p2;}
  v24.maxl= v24.reall= r0 = lleng= rshp[24];inchp2;
  v24.valp= &heap[r15]; p2 = (double *) v24.valp;
  for(i = 0; i < lleng; ++i)  {
    fscanf(fpr[3],"%lf",p2);
    ++p2;}
  v25.maxl= v25.reall= r0 = lleng= rshp[32];inchp2;
  v25.valp= &heap[r15]; p2 = (double *) v25.valp;
  for(i = 0; i < lleng; ++i)  {
    fscanf(fpr[4],"%lf",p2);
    ++p2;}
  v27.maxl= v27.reall= r0 = lleng= rshp[40];inchp3;
  v27.valp= &heap[r15]; p3 = (char   *) v27.valp;
  for(i = 0; i < lleng; ++i)  {
    *p3 = (char) getc(fpr[5]);
    if ('\n'== *p3) *p3= getc(fpr[5]);
    ++p3;}
  time1 = apl_sec();
  BlkSchls ();
  time2 = apl_sec();
//  printf("\n execution time in ms %d\n",time2-time1);
  printf("\n The elapsed time in ms: %g\n",(time2-time1)/1000.0);
/*   OUTPUT generates the following code */
/*  p2 = fretfp;
if(cad[1]<11) for(v1=0;v1<cad[1];v1++){a_prtD0(*p2);++p2;}
  else for (v1=0;v1<cad[1];v1++)
    {a_prtD0(*p2); ++p2; if ((v1%10)==9) printf("\n");}
 putchar('\n');*/
   free(heap); free(v5); free(v6);                  exit(0);}
/*              CODE SEGMENT FOR FUNCTION BlkSchls      */
BlkSchls ()
  { char v8, v11;
   int oldr15, v9, v12, v13, v17;
   double v10, v14, v15, v16;
   STOFM2 v18;
   STOFM2 v26;
   STOFM2 v28;
   STOFM2 v29;
   STOFM2 v30;
   STOFM2 v31;
   STOFM2 v32;
   STOFM2 v33;
   STOFM2 v34;
   STOFM2 v35;
   STOFM2 v36;
   STOFM2 v37;
   STOFM2 v38;
   STOFM2 v39;
   STOFM2 v40;
   STOFM2 v68;
   STOFM2 v69;
   v18.maxl = -1;
   v74.maxl= -1; v75.maxl= -1; v76.maxl= -1;
   v77.maxl= -1; v78.maxl= -1; v79.maxl= -1;
   v26.maxl = -1;
   v28.maxl = -1;
   v29.maxl = -1;
   v30.maxl = -1;
   v31.maxl = -1;
   v32.maxl = -1;
   v33.maxl = -1;
   v34.maxl = -1;
   v35.maxl = -1;
   v36.maxl = -1;
   v37.maxl = -1;
   v38.maxl = -1;
   v39.maxl = -1;
   v40.maxl = -1;
   v68.maxl = -1;
   v69.maxl = -1;
new_v=0;
lj1:
/******************   LINE 1   ******************/
/******************   LINE 2   ******************/
  r0=v25.reall;
INCHEAPP3(v29,inchp2); /* by INCHEAPP */
p2 = (double *) v29.valp;
lo2 = (double *) v25.valp;
  for (v1 =0; v1<r0; v1++) /* code for *. */
     p2[v1] = sqrt((double)lo2[v1]);
/******************   LINE 3   ******************/
r0= v21.reall;
  if (r0!=v22.reall && r0!=1)
  LEMSG(24,3);
  cad[31]=r0;
lo2 = (double *) v21.valp;
ro2 = (double *) v22.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (lo2[v1]==0 && 0==ro2[v1]) v6[v1] =  1; else
   v6[v1] = lo2[v1]/ro2[v1];
  r0 =   cad[31];
INCHEAPP3(v30,inchp2); /* by INCHEAPP */
p2 = (double *) v30.valp;
  for (v1 =0; v1<r0; v1++) /* code for %. */
     p2[v1] =  log(v6[v1]);
   r0=v30.reall;
INCHEAPP3(v31,inchp2); /* by INCHEAPP */
   memcpy(v31.valp, v30.valp, v30.reall<<3);
/******************   LINE 4   ******************/
   r0=v23.reall;
INCHEAPP3(v28,inchp2); /* by INCHEAPP */
   memcpy(v28.valp, v23.valp, v23.reall<<3);
/******************   LINE 5   ******************/
  r0=v27.reall;
INCHEAPP3(v26,inchp0); /* by INCHEAPP */
/*     PFCOMPB generates the folowing code    */
p0 = (  int  *) v26.valp;
lo3 = (char   *) v27.valp;
v1 =0;
while (v1+31 < r0)
 {t=0;
  for (u0=0; u0<32; u0++)
   {if (lo3[v1]=='P')
       t|= lfb>>u0; v1++;}
   p0[v1-1>>5]= t;}
tl= r0&msk;
if ( tl!=0 )
 {t=0;
  u0= r0-tl;
  for (v1= u0; v1 < r0; v1++)
   {if (lo3[v1]=='P')
       t|= lfb>>v1-u0;}
   p0[v1>>5]= t;}
/******************   LINE 6   ******************/
r0= v24.reall;
  if (r0!=v29.reall && r0!=1)
  LEMSG(55,6);
INCHEAPP3(v35,inchp2); /* by INCHEAPP */
p2 = (double *) v35.valp;
lo2 = (double *) v24.valp;
ro2 = (double *) v29.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*ro2[v1];
  r0=v24.reall;
lo2 = (double *) v24.valp;
r0= v24.reall;
  if (r0!=v24.reall && r0!=1)
  LEMSG(47,6);
INCHEAPP3(v34,inchp2); /* by INCHEAPP */
 p20 = (double *) v34.valp;
lo20 = (double *) v24.valp;
r0= v28.reall;
  if (r0!=v34.reall && r0!=1)
  LEMSG(43,6);
lo21 = (double *) v28.valp;
r0= v25.reall;
  if (r0!=v24.reall && r0!=1)
  LEMSG(41,6);
lo22 = (double *) v25.valp;
r0= v31.reall;
  if (r0!=v24.reall && r0!=1)
  LEMSG(39,6);
  cad[31]=r0;
lo23 = (double *) v31.valp;
  for (v1 =0; v1<r0; v1++){ /* code for + */
      p20[v1] = lo20[v1]*lo2[v1]*0.5;
    v6[v1] = lo23[v1]+lo22[v1]*(lo21[v1]+p20[v1]);}
r0= cad[31];
  if (r0!=v35.reall && r0!=1)
  LEMSG(51,6);
INCHEAPP3(v32,inchp2); /* by INCHEAPP */
p2 = (double *) v32.valp;
ro2 = (double *) v35.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
 if (v6[v1]==0 && 0==ro2[v1])  p2[v1] =  1; else
    p2[v1] = v6[v1]/ro2[v1];
   r0=v32.reall;
INCHEAPP3(v36,inchp2); /* by INCHEAPP */
   memcpy(v36.valp, v32.valp, v32.reall<<3);
/******************   LINE 7   ******************/
r0= v32.reall;
  if (r0!=v35.reall && r0!=1)
  LEMSG(62,7);
INCHEAPP3(v33,inchp2); /* by INCHEAPP */
p2 = (double *) v33.valp;
lo2 = (double *) v32.valp;
ro2 = (double *) v35.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
     p2[v1] = lo2[v1]-ro2[v1];
   r0=v33.reall;
INCHEAPP3(v37,inchp2); /* by INCHEAPP */
   memcpy(v37.valp, v33.valp, v33.reall<<3);
/******************   LINE 8   ******************/
/******************   LINE 9   ******************/
rshp[0]=v36.reall;
ro2 = (double *) v36.valp;
  oldr15= r15;
CNDF     (ro2);
  r15= oldr15;
  v74.maxl= -1; v75.maxl= -1; v76.maxl= -1;
  v77.maxl= -1; v78.maxl= -1; v79.maxl= -1;
   r0=cad[1];
INCHEAPP3(v39,inchp2); /* by INCHEAPP */
   memcpy(v39.valp, (char *) fretfp, cad[1]<<3);
/******************   LINE 10   ******************/
rshp[0]=v37.reall;
ro2 = (double *) v37.valp;
  oldr15= r15;
CNDF     (ro2);
  r15= oldr15;
  v74.maxl= -1; v75.maxl= -1; v76.maxl= -1;
  v77.maxl= -1; v78.maxl= -1; v79.maxl= -1;
   r0=cad[1];
INCHEAPP3(v40,inchp2); /* by INCHEAPP */
   memcpy(v40.valp, (char *) fretfp, cad[1]<<3);
/******************   LINE 11   ******************/
r0= v23.reall;
  if (r0!=v25.reall && r0!=1)
  LEMSG(172,11);
lo2 = (double *) v23.valp;
ro2 = (double *) v25.valp;
  r0 =   v25.reall;
  cad[31] =  r0;
  r0 =   v25.reall;
  cad[31] =  r0;
r0= v22.reall;
  if (r0!=v25.reall && r0!=1)
  LEMSG(168,11);
INCHEAPP3(v38,inchp2); /* by INCHEAPP */
p2 = (double *) v38.valp;
lo20 = (double *) v22.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo20[v1]* exp(( -lo2[v1]*ro2[v1]));
/******************   LINE 12   ******************/
  r0=v39.reall;
  cad[31]=r0;
ro2 = (double *) v39.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
    v6[v1] = 1-ro2[v1];
r0= v21.reall;
  if (r0!=cad[31] && r0!=1)
  LEMSG(185,12);
INCHEAPP3(v68,inchp2); /* by INCHEAPP */
p2 = (double *) v68.valp;
lo2 = (double *) v21.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*v6[v1];
  r0=v40.reall;
  cad[31]=r0;
ro2 = (double *) v40.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
    v6[v1] = 1-ro2[v1];
r0= v38.reall;
  if (r0!=cad[31] && r0!=1)
  LEMSG(179,12);
  cad[31]=r0;
lo2 = (double *) v38.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for * */
    v6[v1] = lo2[v1]*v6[v1];
r0= cad[31];
  if (r0!=v68.reall && r0!=1)
  LEMSG(183,12);
  cad[31]=r0;
ro2 = (double *) v68.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for - */
    v6[v1] = v6[v1]-ro2[v1];
r0= v26.reall;
  if (r0!=cad[31] && r0!=1)
  LEMSG(177,12);
INCHEAPP3(v18,inchp2); /* by INCHEAPP */
p2 = (double *) v18.valp;
lo0 = (  int  *) v26.valp;
   v1 =0; /* code for * */
   for (u1 =0; u1<r0>>5; u1++)
  {t=lo0[u1];
    for (v2=0; v2<32; v2++) {
      if ( t < 0)
      p2[v1] = 1*v6[v1];
      else
      p2[v1] = 0*v6[v1];
      v1++;
      t<<=1;}}
  if ((r0&msk)!=0)
  {t=lo0[u1];
    for (v2=0; v2<(r0&msk); v2++) {
      if ( t < 0)
      p2[v1] = 1*v6[v1];
      else
      p2[v1] = 0*v6[v1];
      v1++;
      t<<=1;}}
/******************   LINE 13   ******************/
r0= v38.reall;
  if (r0!=v40.reall && r0!=1)
  LEMSG(201,13);
INCHEAPP3(v69,inchp2); /* by INCHEAPP */
p2 = (double *) v69.valp;
lo2 = (double *) v38.valp;
ro2 = (double *) v40.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*ro2[v1];
r0= v21.reall;
  if (r0!=v39.reall && r0!=1)
  LEMSG(197,13);
  cad[31]=r0;
lo2 = (double *) v21.valp;
ro2 = (double *) v39.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
    v6[v1] = lo2[v1]*ro2[v1];
r0= cad[31];
  if (r0!=v69.reall && r0!=1)
  LEMSG(199,13);
  cad[31]=r0;
ro2 = (double *) v69.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for - */
    v6[v1] = v6[v1]-ro2[v1];
  r0 =   v26.reall;
  cad[11] =  r0;
/*  PFLOGIC Generates the following code for ~*/
ro0 = (  int  *) v26.valp;
  r1= (31+v26.reall)>>5;
  for (v1=0; v1<r1; v1++)
    v4[v1] =  ~ro0[v1];
  if (0 != (tl = v26.reall<<27))
    { tl>>=27;
  t =v4[r1-1]>>(32-tl);
  v4[r1-1] = t<<(32-tl);}
r0= cad[11];
  if (r0!=cad[31] && r0!=1)
  LEMSG(195,13);
  cad[31]=r0;
   v1 =0; /* code for * */
   for (u1 =0; u1<cad[31]>>5; u1++)
  {t=v4[u1];
    for (v2=0; v2<32; v2++) {
      if ( t < 0)
     v6[v1] = 1*v6[v1];
      else
     v6[v1] = 0*v6[v1];
      v1++;
      t<<=1;}}
  if ((cad[31]&msk)!=0)
  {t=v4[u1];
    for (v2=0; v2<(cad[31]&msk); v2++) {
      if ( t < 0)
     v6[v1] = 1*v6[v1];
      else
     v6[v1] = 0*v6[v1];
      v1++;
      t<<=1;}}
r0= v18.reall;
  if (r0!=cad[31] && r0!=1)
  LEMSG(192,13);
p2 = (double *) v18.valp;
lo2 = (double *) v18.valp;
  for (v1 =0; v1<v18.reall; v1++) /* code for + */
     p2[v1] = lo2[v1]+v6[v1];
lj0:;
cad[1]= v18.reall;
fretfp= (double *) v18.valp;
    }
/*              CODE SEGMENT FOR FUNCTION CNDF          */
CNDF     (p47)
  double* p47;
  { char v8, v11;
   int oldr15, v9, v12, v13, v17;
   double v10, v14, v15, v16;
   STOFM2 v46;
   STOFM2 v48;
   STOFM2 v49;
   STOFM2 v50;
   STOFM2 v51;
   STOFM2 v52;
   STOFM2 v53;
   STOFM2 v54;
   STOFM2 v55;
   STOFM2 v56;
   STOFM2 v57;
   STOFM2 v58;
   STOFM2 v59;
   STOFM2 v70;
   STOFM2 v71;
   STOFM2 v72;
   STOFM2 v73;
   STOFM2 v47;
   v46.maxl = -1;
   v48.maxl = -1;
   v49.maxl = -1;
   v50.maxl = -1;
   v51.maxl = -1;
   v52.maxl = -1;
   v53.maxl = -1;
   v54.maxl = -1;
   v55.maxl = -1;
   v56.maxl = -1;
   v57.maxl = -1;
   v58.maxl = -1;
   v59.maxl = -1;
   v70.maxl = -1;
   v71.maxl = -1;
   v72.maxl = -1;
   v73.maxl = -1;
r0= rshp[0];
v47.reall= v47.maxl= r0;
 inchp2; v47.valp= &heap[r15]; /* by INCHEAP2V */
ro2= (double *) v47.valp;
  for (v1=0; v1<r0; v1++)
ro2[v1]= p47[v1];
new_v=0;
lj1:
/******************   LINE 1   ******************/
  r0=v47.reall;
INCHEAPP3(v48,inchp0); /* by INCHEAPP */
/*     PFCOMPB generates the folowing code    */
p0 = (  int  *) v48.valp;
lo2 = (double *) v47.valp;
v1 =0;
while (v1+31 < r0)
 {t=0;
  for (u0=0; u0<32; u0++)
   {if (lo2[v1]< 0)
       t|= lfb>>u0; v1++;}
   p0[v1-1>>5]= t;}
tl= r0&msk;
if ( tl!=0 )
 {t=0;
  u0= r0-tl;
  for (v1= u0; v1 < r0; v1++)
   {if (lo2[v1]< 0)
       t|= lfb>>v1-u0;}
   p0[v1>>5]= t;}
/******************   LINE 2   ******************/
  r0 =   v47.reall;
INCHEAPP3(v49,inchp2); /* by INCHEAPP */
p2 = (double *) v49.valp;
ro2 = (double *) v47.valp;
  for (v1 =0; v1<r0; v1++) /* code for | */
     p2[v1] =  fabs(ro2[v1]);
/******************   LINE 3   ******************/
r0= v47.reall;
  if (r0!=v47.reall && r0!=1)
  LEMSG(90,3);
lo2 = (double *) v47.valp;
ro2 = (double *) v47.valp;
  r0 =   v47.reall;
INCHEAPP3(v51,inchp2); /* by INCHEAPP */
 p20 = (double *) v51.valp;
  r0=v51.reall;
INCHEAPP3(v50,inchp2); /* by INCHEAPP */
p2 = (double *) v50.valp;
  for (v1 =0; v1<r0; v1++){ /* code for * */
      p20[v1] =  exp((-0.5)*lo2[v1]*ro2[v1]);
     p2[v1] = 0.39894228*p20[v1];}
/******************   LINE 4   ******************/
ro2 = (double *) v49.valp;
  r0=v49.reall;
  cad[31]=r0;
  for (v1 =0; v1<r0; v1++) /* code for + */
    v6[v1] = 1+0.2316419*ro2[v1];
  r0=cad[31];
INCHEAPP3(v52,inchp2); /* by INCHEAPP */
p2 = (double *) v52.valp;
  for (v1 =0; v1<r0; v1++) /* code for % */
    p2[v1] = (double)1/v6[v1];
r0= v52.reall;
  if (r0!=v52.reall && r0!=1)
  LEMSG(107,4);
INCHEAPP3(v53,inchp2); /* by INCHEAPP */
p2 = (double *) v53.valp;
lo2 = (double *) v52.valp;
ro2 = (double *) v52.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*ro2[v1];
r0= v52.reall;
  if (r0!=v53.reall && r0!=1)
  LEMSG(103,4);
INCHEAPP3(v54,inchp2); /* by INCHEAPP */
p2 = (double *) v54.valp;
lo2 = (double *) v52.valp;
ro2 = (double *) v53.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*ro2[v1];
r0= v52.reall;
  if (r0!=v54.reall && r0!=1)
  LEMSG(99,4);
INCHEAPP3(v55,inchp2); /* by INCHEAPP */
p2 = (double *) v55.valp;
lo2 = (double *) v52.valp;
ro2 = (double *) v54.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*ro2[v1];
r0= v52.reall;
  if (r0!=v55.reall && r0!=1)
  LEMSG(95,4);
INCHEAPP3(v56,inchp2); /* by INCHEAPP */
p2 = (double *) v56.valp;
lo2 = (double *) v52.valp;
ro2 = (double *) v55.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*ro2[v1];
/******************   LINE 5   ******************/
  r0=v52.reall;
INCHEAPP3(v58,inchp2); /* by INCHEAPP */
p2 = (double *) v58.valp;
lo2 = (double *) v52.valp;
  for (v1 =0; v1<r0; v1++) /* code for * */
     p2[v1] = lo2[v1]*0.31938153;
/******************   LINE 6   ******************/
  r0=v56.reall;
lo2 = (double *) v56.valp;
lo2 = (double *) v55.valp;
r0= v55.reall;
  if (r0!=v56.reall && r0!=1)
  LEMSG(135,6);
lo20 = (double *) v55.valp;
lo2 = (double *) v54.valp;
r0= v54.reall;
  if (r0!=v56.reall && r0!=1)
  LEMSG(131,6);
lo20 = (double *) v54.valp;
lo2 = (double *) v53.valp;
r0= v53.reall;
  if (r0!=v56.reall && r0!=1)
  LEMSG(127,6);
INCHEAPP3(v59,inchp2); /* by INCHEAPP */
p2 = (double *) v59.valp;
lo20 = (double *) v53.valp;
  for (v1 =0; v1<r0; v1++) /* code for + */
     p2[v1] = lo2[v1]*(-0.35656378)+(lo2[v1]*1.78147793+(lo2[v1]*(
-1.82125597)+lo2[v1]*1.33027442));
/******************   LINE 7   ******************/
r0= v59.reall;
  if (r0!=v58.reall && r0!=1)
  LEMSG(157,7);
  cad[31]=r0;
lo2 = (double *) v59.valp;
ro2 = (double *) v58.valp;
  for (v1 =0; v1<r0; v1++) /* code for + */
    v6[v1] = lo2[v1]+ro2[v1];
r0= v50.reall;
  if (r0!=cad[31] && r0!=1)
  LEMSG(155,7);
  cad[31]=r0;
lo2 = (double *) v50.valp;
  for (v1 =0; v1<cad[31]; v1++) /* code for * */
    v6[v1] = lo2[v1]*v6[v1];
  r0=cad[31];
INCHEAPP3(v57,inchp2); /* by INCHEAPP */
p2 = (double *) v57.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
     p2[v1] = 1-v6[v1];
  r0 =   v48.reall;
  cad[11] =  r0;
/*  PFLOGIC Generates the following code for ~*/
ro0 = (  int  *) v48.valp;
  r1= (31+v48.reall)>>5;
  for (v1=0; v1<r1; v1++)
    v4[v1] =  ~ro0[v1];
  if (0 != (tl = v48.reall<<27))
    { tl>>=27;
  t =v4[r1-1]>>(32-tl);
  v4[r1-1] = t<<(32-tl);}
r0= cad[11];
  if (r0!=v57.reall && r0!=1)
  LEMSG(149,7);
INCHEAPP3(v73,inchp2); /* by INCHEAPP */
p2 = (double *) v73.valp;
ro2 = (double *) v57.valp;
   v1 =0; /* code for * */
   for (u1 =0; u1<r0>>5; u1++)
  {t=v4[u1];
    for (v2=0; v2<32; v2++) {
      if ( t < 0)
      p2[v1] = 1*ro2[v1];
      else
      p2[v1] = 0*ro2[v1];
      v1++;
      t<<=1;}}
  if ((r0&msk)!=0)
  {t=v4[u1];
    for (v2=0; v2<(r0&msk); v2++) {
      if ( t < 0)
      p2[v1] = 1*ro2[v1];
      else
      p2[v1] = 0*ro2[v1];
      v1++;
      t<<=1;}}
  r0=v57.reall;
  cad[31]=r0;
ro2 = (double *) v57.valp;
  for (v1 =0; v1<r0; v1++) /* code for - */
    v6[v1] = 1-ro2[v1];
r0= v48.reall;
  if (r0!=cad[31] && r0!=1)
  LEMSG(142,7);
  cad[31]=r0;
lo0 = (  int  *) v48.valp;
   v1 =0; /* code for * */
   for (u1 =0; u1<cad[31]>>5; u1++)
  {t=lo0[u1];
    for (v2=0; v2<32; v2++) {
      if ( t < 0)
     v6[v1] = 1*v6[v1];
      else
     v6[v1] = 0*v6[v1];
      v1++;
      t<<=1;}}
  if ((cad[31]&msk)!=0)
  {t=lo0[u1];
    for (v2=0; v2<(cad[31]&msk); v2++) {
      if ( t < 0)
     v6[v1] = 1*v6[v1];
      else
     v6[v1] = 0*v6[v1];
      v1++;
      t<<=1;}}
r0= cad[31];
  if (r0!=v73.reall && r0!=1)
  LEMSG(146,7);
INCHEAPP3(v46,inchp2); /* by INCHEAPP */
p2 = (double *) v46.valp;
ro2 = (double *) v73.valp;
  for (v1 =0; v1<r0; v1++) /* code for + */
     p2[v1] = v6[v1]+ro2[v1];
lj0:;
cad[1]= v46.reall;
fretfp= v6;
ro2= (double *) v46.valp;
  for (u1=0; u1<v46.reall; u1++)
    v6[u1]= ro2[u1];
    }
