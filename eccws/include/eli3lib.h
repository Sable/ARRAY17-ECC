/*                                                                              
 * Pre-compiled functions for APLC compiler.                                    
 */                                                                             

#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <string.h>                                                             
#include <math.h>                                                               
#include <time.h>                                                               
#include "aplc.h" 
//#include "Aplc.h"
                                                               
#define qdrl0 16807//from apl3lib2.c
#define m16 65535                                                               
#define m15 32767                                                               

//#include "aplc0.h" from apl3lib3.c
                                                                                
                                                                                
#define NBLOCK  256                                                             
/* The following QDPP is a temporary fix.  Should merge with                    
 * that defined in the main program. 12/25/90.                                  
 */                                                                             
#define QDPP   7   /*  out on 2/24/2009  back 3/11*/                                                           
void * amalloc(int size);

void * acalloc(int size, int chuck);

void alloc(int typ);
                                                                                
/*                                                                              
 * Open file, give error message and terminate if the failed.                   
 */                                                                             
//FILE *a_fopen(char *szFN, char *szMode);
                                                                                
/* timer subroutine for linking by c language program */                        
                                                                                
                                                                                
/*                                                                              
 * a_fmtI                                                                       
 * Format an integer type array                                                 
 * A null terminated is appended at the end of the output.                      
 $$$$$$$$$$$Important message$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                    
 $ We allocate temporary space here. The caller must free  $                    
 $ the space after copying the data to the target.         $                    
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                    
 */                                                                             
char *a_fmtI(int *pData, int iQdpp, int npts); /* Data pointer  Precision  Number of objects  */
                                                                                
/*                                                                              
 * a_pack                                                                       
 * Remove trailing spaces and 0's, then append a space and '\0'                 
 * If E format, then we also remove the leading 0 in the exponent               
 * Shi.. 12/17/90                                                               
 */                                                                             
void a_pack(char *pBuff, int iQdpp);    // Precision
                                                                                
/*                                                                              
 * a_fmtD                                                                       
 * Format a double type array                                                   
 * A null terminated is appended at the end of the output.                      
 $$$$$$$$$$$Important message$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                    
 $ We allocate temporary space here. The caller must free  $                    
 $ the space after copying the data to the target.         $                    
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                    
 * This function can be written in a more efficient way.                        
 * Due to the current (12/17/90) "rush", I will leave the fun part              
 * to the lucky one.  Shi..                                                     
 *                                                                              
 * Shi.. 12/17/90 First cut.                                                    
 * Shi.. 12/25/90 Add %E format                                                 
 * If the value is less than DBLFMTBD then we use %E format                     
 * DBLFMTDB is a defined constants.                                             
 *                                                                              
 */                                                                             
char *a_fmtD(double *pData, int iQdpp, int npts); //data pointer, precision, #objects

void a_prtD0(double v);
                                                                                
/* This routine counts the no of ones in the boolean var pointed by p0.         
*/                                                                              
int no_of_ones(int r0, int * p0);
                                                                                
/*    Pass a boolean parameter to main function */                              
void passparmb (FILE * fpl, int lgth, int * p0);
                                                                                
/* print out boolean value */                                                   
void prntbool (int * p0, int cl);

                                                                                
/****** factorial fns ******/                                                   
//int fact[13]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880,3628800,            
//              39916800, 479001600};                                            
                                                                                
int ifac(int n);
                                                                                
double efac(int n);
                                                                                
double ebin(int n,int m);

/* random number generator for vs apl */
int randomn(int n);

void mat_inverse(double* a,double* y,int n);
                                                                                
void ludcmp(double *a,int n,int *indx,double *d);

void lubksb(double *a,int n,int *indx,double *b);

//apl3lib3.c/* Convert boolean op to int or double  */
void boolcvi (int* targ,int* ooc,int llgth,int lgth);
                                                                                
/* Convert boolean op to int or double  */                                      
void boolcvd (double* targ,int* ooc,int llgth,int lgth);
                                                                                
/* Convert segment of boolean op to int or double. Called by MDCATENA */        
void boolcv1i(int* targ,int* ooc,int n,int i,int sl);

void boolcv1d(double* targ,int* ooc,int n,int i,int sl);

//#include "aplc0.h"//apl3lib4.c
void bitsmove (int *targ,int* rrc,int r0,int n);

/* BITSMOVEC 1992 9 3 */                                                        
/* move the complem of a bit-string to a targ place starti at i-th bit */       
void bitsmovc (int* targ,int* rrc,int ll,int rrl,int i);

/*   move a bit-string to a targ place starting at i-th bit */                  
void bitsmov0 (int* targ,int* rrc,int ll,int rrl,int i);
                                                                                
void bitsmovs (int* targ,int rrc,int ll,int rrl,int i);

/*     move a bit-string starting at word sw bit position si to                 
       targ word qw bit position qi. */                                         
int qw, qi;                                                              
//extern int qw, qi;                                                              
                                                                                
/*int  bitsmov1 (targ, rrc, sw, si, lslg) */                                    
void  bitsmov1 (int* targ,int* rrc,int sw,int si,int lslg);

//#include "aplc0.h" apl3lib5.c
/*** called by genidxof boolean case ***/                                       
int  findfst0(int* llc,int lopl,int qdio);

int  findfst1(int* llc,int lopl,int qdio);
                                                                                
void boolidxof(int* ttc,int* llc,int* rrc,int lopl,int ropl,int qdio);
                                                                                
void bol1idxof(int* ttc,int llc,int* rrc,int ropl,int qdio);

/* code containing wrapmove in genreshp */                                      
void wrapmove(int* ttc,int* rrc,int r0,int ropl);

//apl3lib7.c
//#include "aplc0.h"

int count3b0(int tl,int j,int n);

/* extern int n; */
int count32b(int t,int n);

/*     +/BM    */
void breductv(int *ttc,int * rrc,int  r0,int lplg0);

/*     +/Bool vect */
int  breduct0(int *rrc, int ropl);

/*     +�Bool vect  */
void bscan0(int* ttc,int* rrc, int ropl);

/*     Kernel of Bool ػ   */
void bscan20(int* ttc,int* pt,unsigned int * pwa,int  v1,int  segl, int i, int j);

/* ػB                              */
void gscan20m(int* ttc,int* rrc,int r0,int n);

void gscan20v(int* ttc,int* rrc,int r0,int n);

//apl3lib8.c
//#include "aplc0.h"                                                              
                                                                                
/*    copy string of 1s to targ place word TW position i lgth RLTH */           
void copybits1(int* ttc,int i,int j,int rlth);
                                                                                
/* bits OR reduction subroutine for linking by c language program */            
/* void aplbit0(r0, size, ro0)                                  */              
/* pos: bool-element position, i:bit pos/rel.32. size:string length */          
/* ro0 is the ROP variable */                                                   
void aplbit0(int* p0,int u0,int r0,int size,int* ro0);

void  aplbit1(int r0,int v3,int* ttc,int* rrc);

void  aplbit2(int r0,int v3,int* ttc,int* rrc);
                                                                                
void  aplbit3(int r0,int v3,int* ttc,int* rrc);

void all1s(int* ttc,int r0);

//apl3lib9.c
void reversi(int* ttc,int* rrc,int v3,int n0,int r1,int seg,int tl);
                                                                                
void reversm(double* ttc,int* rrc,int v3,int n0,int r1,int seg,int tl);
                                                                                
void reversd(double* ttc,double* rrc,int v3,int n0,int r1,int seg,int tl);
                                                                                
void reversc(char* ttc,char* rrc,int v3,int n0,int r1,int seg,int tl);
                                                                                
void areversi(int* ttc,int* rrc,int q0,int r1,int r2,int seg);
                                                                                
void areversm(double* ttc,int* rrc,int q0,int r1,int r2,int seg);
                                                                                
void areversd(double* ttc,double* rrc,int q0,int r1,int r2,int seg);
                                                                                
void areversc(char* ttc,char* rrc,int q0,int r1,int r2,int seg);
                                                                                
void breversi(int* ttc,int* rrc,int r0);
                                                                                
void breversm(double* ttc,int* rrc,int r0);
                                                                                
void breversd(double* ttc,double* rrc,int r0);
                                                                                
void breversc(char* ttc,char* rrc,int r0);

//apl3liba.c
//#include "aplc0.h"                                                              
                                                                                
void rotatfxi(int* ttc,int* llc,int* rrc,int notb,int q1,int q2);
                                                                                
void rotatfxd(double* ttc,int* llc,double* rrc,int q1,int q2);
                                                                                
void rotatfxc(char* ttc,int* llc,char* rrc,int q1,int q2);
                                                                                
void rotatfxm(double* ttc, int* llc,int* rrc,int q1,int q2);

//apl3libb.c
//#include "aplc0.h"                                             

void takei(int* ttc,int* rrc,int r0,int rrl,int lopv);
                                                                                
void taked(double* ttc,double* rrc,int r0,int rrl,int lopv);
                                                                                
void takec(char* ttc,char* rrc,int r0,int rrl,int lopv);
                                                                                
void takem(double* ttc,int* rrc,int r0,int rrl,int lopv);
                                                                                
/*extern int * cad, * tdl, * dl; */                                             
//void tak2d(double* p2,int* v19,double* ro2,int ropd0,int ropd1,int s0,int s1,int* cad,int* tdl,int* dl);

void tak2i(int* p2,int* v19,int* ro2,int ropd0,int ropd1,int s0,int s1,int* cad,int* tdl,int* dl);
                                                                                
void tak2m(double* p2,int* v19,int* ro2,int ropd0,int ropd1,int s0,int s1,int* cad,int* tdl,int* dl);
                                                                                
void tak2c(char* p2,int* v19,char* ro2,int ropd0,int ropd1,int s0,int s1,int* cad,int* tdl,int* dl);

//apl3libc.c
//#include "aplc0.h"                                                              
                                                                                
int membsp0b (int lop0,int* rrc,int ropl);
                                                                                
//void membspc(int* ttc,char* llc,int lopl,char* rrc,int ropl) 0/8
void membspc(long* ttc,char* llc,int lopl,char* rrc,int ropl);
                                                                                
void idxofc(int* ttc,char* llc,int lopl,char* rrc,int ropl,int qdio);

//apl3libd.c
/***** integer hashing for membership and index of *****/

//#include <stdlib.h>
//#include "aplc0.h"

// duplicated in eli3lib.cpp //2017.04.01
// int dvz[20]= {31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383,
//              32767, 65535, 131071, 262143, 524287, 1048575, 2097151,
//              4194303, 8388607, 16777215};

//#define Hngi    0x80000001

//void * acalloc(int size, int chuck);
/*{void * z;
   if (size<0)
     {printf ("* size negative in allocate. *\n"); exit(1);}
   z= calloc(size, chuck);
   if (z == NULL)
     {printf ("* insufficient memery to allocate. *\n"); exit(1);}
   return z;
} */

//void membspi(int* ttc,int* llc,int lopl,int* rrc,int ropl) 0/8
//void membspi(long* ttc,long* llc,int lopl,long* rrc,int ropl)
// { duplicated in eli3lib.cpp }
//void idxofi(int* ttc,int* llc,int lopl,int* rrc,int ropl,int qdio)
// { duplicated in eli3lib.cpp }
//apl3libe.c
/***** floating point hashing for membership and index of *****/

/*#include <stdlib.h>
#include "aplc0.h"*/

//int dvs[20]= {31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383,
//              32767, 65535, 131071, 262143, 524287, 1048575, 2097151,
//              4194303, 8388607, 16777215};

//int sfr[20]= {18, 17, 16, 15, 14, 13, 13, 12, 11, 10, 9, 8,
//              7, 6, 5, 4, 3, 2, 1, 0};

//double Hflt= 7.662478e+53;

void * amalloc(int size);
/*{void * z;
   if (size<0)
     {printf ("* size negative in allocate. *\n"); exit(1);}
   z= malloc(size);
   if (z == NULL)
     {printf ("* insufficient memery to allocate. *\n"); exit(1);}
   return z;
}*/
void * acalloc(int size, int chuck);
/*{void * z;
   if (size<0)
     {printf ("* size negative in allocate. *\n"); exit(1);}
   z= calloc(size, chuck);
   if (z == NULL)
     {printf ("* insufficient memery to allocate. *\n"); exit(1);}
   return z;
}*/

//void membspd(int* ttc,double* llc,int lopl,double* rrc,int ropl) 0/8
//void membspd(long* ttc,double* llc,int lopl,double* rrc,int ropl)
// { duplicated in eli3lib.cpp } 

//void membspm(int* ttc,double* llc,int lopl, int* rrc,int ropl) 0/8
//void membspm(long* ttc,double* llc,int lopl, long* rrc,int ropl)
// { duplicated in eli3lib.cpp } 

//void membspn(int* ttc,int* llc,int lopl,double* rrc,int ropl) 0/8
//void membspn(long* ttc,long* llc,int lopl,double* rrc,int ropl)
// { duplicated in eli3lib.cpp } 

// void idxofd(int* ttc,double* llc,int lopl,double* rrc,int ropl,int qdio)
// { duplicated in eli3lib.cpp } 

// void idxofm(int* ttc,double* llc,int lopl,int* rrc,int ropl,int qdio)
// { duplicated in eli3lib.cpp } 

// void idxofn(int* ttc,int* llc,int lopl,double* rrc,int ropl,int qdio)
// { duplicated in eli3lib.cpp } 

//apl3libf.c
/*#include <stdio.h>                                                              
#include <stdlib.h>
#include <string.h>
#include "aplc.h"*/
/* Data types 
#define BOOLTYPE   0                                                            
#define INTTYPE    1                                                            
#define DOUBLETYPE 2                                                            
#define CHARTYPE   3 */                                                         
                                                                                
/*                                                                              
 * compare values, return 1 if equal, 0 otherwise.. for integer type            
 * N. Shi.. 12/16/90.                                                           
 */                                                                             
int compeqI(int* v,int* Indx,int qdio,int i,int j);
/*                                                                              
 * compare values, return 1 if equal, 0 otherwise; for double type              
 * N. Shi.. 12/16/90.                                                           
 */                                                                             
int compeqD(double* v,int* Indx,int qdio,int i,int j);                          
                                                                                
/*                                                                              
 * compare indices for qsort of the standard library                            
 * N. Shi.. 12/15/90.                                                           
                                                                              
int qcompIndx(int* i,int* j)                                                             
{                                                                               
   if ((*i) < (*j)) return -1;                                                  
      else                                                                      
      if ((*i) == (*j)) return 0; else return 1;                                
}                                                                               
*/                                                                              
                                                           
//Paul 10/99                                                                             
int qcompIndx(const void *i,const void *j);
/*                                                                              
 * compare for grade up, for integer array v                                    
 * N. Shi.. 12/15/90.                                                           
 */                                                                             
int compupI(int* v, int i,int j,int size);                                      
                                                                                
/*                                                                              
 * compare for grade up, for double array v                                     
 * N. Shi.. 12/15/90.                                                           
 */                                                                             
int compupD(double* v,int i,int j,int size);
                                                                                
/*                                                                              
 * compare for grade up, for char array v                                       
 * N. Shi.. 12/15/90.                                                           
 */                                                                             
int compupC(char* v,int i,int j,int size);                                      
                                                                                
/*                                                                              
 * compare for grade down, for integer array v                                  
 * N. Shi.. 12/16/90.                                                           
 */                                                                             
int compdnI(int* v,int i,int j,int size);                                       
                                                                                
/*                                                                              
 * compare for grade down, for double array v                                   
 */                                                                             
int compdnD(double* v,int i,int j,int size);                                    
                                                                                
/*                                                                              
 * compare for grade down, for char array v                                     
 * N. Shi.. 12/16/90.                                                           
 */                                                                             
int compdnC(char* v,int i,int j,int size);                                      
                                                                                
                                                                                
                                                                                
/*                                                                              
 * compare and swap if needed, for integer array v                              
 * For grade up for integer.                                                    
 * N. Shi.. 12/15/90.                                                           
 */                                                                             
void swap(void* v,int* Indx,int i,int j,int size);                              
                                                                                
/*                                                                              
 * order, arrange either in up or down order depending on comp.                 
 * For simulating APL grade-up and grade-down functions                         
 * N. Shi.. 12/15/90                                                            
 */                                                                             
/*void order(int* v,int* Indx,int left,int right,int size, int (*comp)())//**********problems with last param
{                                                                               
   int i, last; 																
																				
   if (left >= right) return;													
																				
   swap(v, Indx, left, (left+right)/2, size);									
   last = left; 																
																				
   for (i=left+1; i<= right; i++)												
	  if ((*comp)(v, i, left, size))											
		 swap(v, Indx, ++last, i, size);										
   swap(v, Indx, left, last, size); 											
   order(v, Indx, left, last-1, size, comp);									
   order(v, Indx, last+1, right, size, comp);									
}*/ //Problems with pointer to function, doesn't seem to be called by anything else															
                                                                                
/*                                                                              
 * TotalBytes, get the array length based on data type.                         
 * N. Shi.. 12/15/90                                                            
 */                                                                             
int TotalBytes(int iType,int n);
                                                                                
/* sort array v in ascending order by N. Shi 91/1/3 */                          
/* itemp is the indices, will be rearranged accoding to v */                    
void sortI(int n,int* v,int* itemp);
                                                                                
/* sort array v in decending order by N. Shi 91/1/3 */                          
/* itemp is the indices, will be rearranged accoding to v */                    
void sortD(int n,double* v,int* itemp);
                                                                                
/*                                                                              
 * grade                                                                        
 * N. Shi. 12/15/90                                                             
 * v = data array, iType = data type                                            
 * Indx = output indices for grade up or grade down.                            
 * qdio = quad-IO,  n = the number of data points.                              
 * option = GRADEUP or GRADEDOWN             /* Target array must have been allocated */                                   

//Paul 10/99
void a_grade(void* v,int iType,int* Indx,int qdio,int n,int option);

