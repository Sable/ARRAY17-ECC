/*                                                                              
 * apl_lib.c                                                                    
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
#define QDPP   7                                                                
void * amalloc(int size)                                                        
{void * z;                                                                      
   if (size<0)                                                                  
     {printf ("* size negative in allocate. *\n"); exit(1);}                    
   z= malloc(size);                                                             
   if (z == NULL)                                                               
     {printf ("* insufficient memery to allocate. *\n"); exit(1);}              
   return z;                                                                    
}                                                                               
void * acalloc(int size, int chuck)                                             
{void * z;                                                                      
   if (size<0)                                                                  
     {printf ("* size negative in allocate. *\n"); exit(1);}                    
   z= calloc(size, chuck);                                                      
   if (z == NULL)                                                               
     {printf ("* insufficient memery to allocate. *\n"); exit(1);}              
   return z;                                                                    
}                                                                               
void alloc(int typ)                                                                 
{  extern char * heap;                                                          
//   extern int r0, r1, th, r15;                                                  
   int r0, r1, th, r15;//removed externs********************************8
   int typsz[4]= {1,4,8,1};                                                     
   r15= max(typsz[typ],100000);                                                 
   heap= (char*)amalloc(r15); /* 93/6/1 *///**********added char*                            
   printf ("*** Heap space increased. ***\n");                                  
   if (typ == 0) r15 -=(r0+31)>>5<<2;                                           
   else if (typ == 1) r15 -= r0<<2;                                             
   else if (typ == 2) {r15 -= r0<<3; r15>>=3; r15<<=3;}                         
   else if (typ == 3) r15 -= (r0+3)>>2<<2;                                      
   else th = r15 - r1;}                                                         
                                                                                
/*                                                                              
 * Open file, give error message and terminate if the failed.                   
 */                                                                             
FILE *a_fopen(char *szFN, char *szMode)                                                     
{                                                                               
   FILE *fp;                                                                    
   if ( (fp = fopen(szFN, szMode)) == NULL) {                                   
      printf("Could not open file %s\n", szFN);                                 
      exit(1);                                                                  
   }                                                                            
   return (fp);                                                                 
}                                                                               
                                                                                
/* timer subroutine for linking by c language program */                        
                                                                                
int apl_sec()                                                                   
{                                                                               
    clock_t tmb;                                                                
    tmb = clock();                                                              
    return(tmb);                                                            
}                                                                               
                                                                                
/*                                                                              
 * a_fmtI                                                                       
 * Format an integer type array                                                 
 * A null terminated is appended at the end of the output.                      
 $$$$$$$$$$$Important message$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                    
 $ We allocate temporary space here. The caller must free  $                    
 $ the space after copying the data to the target.         $                    
 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                    
 */                                                                             
char *a_fmtI(int *pData, int iQdpp, int npts)/* Data pointer  Precision  Number of objects  */                                              
{                                                                               
   char temp[80];                                                               
   /* Assume that no one dare to use 80 char precision */                       
   char *pBuff=NULL;                                                            
   int  i, ntotal, nAlloc;                                                      
   int  width, nprecis, ndecade;                                                
   nAlloc = NBLOCK;                                                             
   if (!(pBuff= (char *) malloc(nAlloc)) ) {                                    
      printf("malloc failed in a_fmtD\n");                                      
      exit(1);                                                                  
   }                                                                            
   pBuff[0] = '\0';                                                             
                                                                                
   ntotal = 0;                                                                  
   for (i=0; i<npts; i++) {                                                     
      sprintf(temp, "%d ", pData[i]);                                           
      ntotal += strlen(temp);                                                   
      if (ntotal > (nAlloc+1)) {                                                
         nAlloc += NBLOCK;                                                      
         if (!(pBuff = (char *) realloc((char *) pBuff, nAlloc)) ) {            
            printf("realloc failed in a_fmtD, n = %d\n", nAlloc);               
            exit(1);                                                            
         }                                                                      
      }                                                                         
      strcat(pBuff, temp);                                                      
   }                                                                            
                                                                                
   pBuff[ntotal -1 ] = '\0';                                                    
   return(pBuff);                                                               
}                                                                               
                                                                                
/*                                                                              
 * a_pack                                                                       
 * Remove trailing spaces and 0's, then append a space and '\0'                 
 * If E format, then we also remove the leading 0 in the exponent               
 * Shi.. 12/17/90                                                               
 */                                                                             
void a_pack(char *pBuff, int iQdpp)    // Precision                                                  
{                                                                               
   int i, n;                                                                    
   char *temp, c;                                                               
                                                                                
   if ((temp = strchr(pBuff, 'E')) == NULL) {                                   
      /* Not an E format */                                                     
      i = strlen(pBuff);                                                        
      i--;                                                                      
      while ((i>=0) && ((pBuff[i] == '0') || (pBuff[i] == ' ')                  
         || (pBuff[i] == '.') )) {                                              
         if (pBuff[i] == '.') {pBuff[i] ='\0'; --i; break;}                     
         pBuff[i] = '\0';   --i;                                                
      }                                                                         
      if (i<0) { pBuff[0] = '0'; pBuff[1] = '\0'; }                             
   } else {                                                                     
      /* An E format */                                                         
      if ((*(temp+1)) == '0') {                                                 
        if ((*(temp+2)) == '0') { *temp = '\0';}                                
        else {                                                                  
           *(temp+1) = *(temp+2);                                               
           *(temp+2) = '\0';                                                    
        }                                                                       
      } else {                                                                  
        c = *(temp+1);                                                          
        if ((c == '-') || (c == '+')) {                                         
           if ((*(temp+2)) == '0') {                                            
              if ((*(temp+3)) == '0') { *temp = '\0';}                          
              else {                                                            
                 *(temp+2) = *(temp+3);                                         
                 *(temp+3) = '\0';                                              
              }                                                                 
           }                                                                    
        }                                                                       
      }                                                                         
      /* Squeeze out middle 0 */                                                
      n = (int) (temp - pBuff);                                                 
      i = n-1;                                                                  
      while ((i>=0) && ((pBuff[i] == '0') ||                                    
            (pBuff[i] == '.') )) {                                              
         if (pBuff[i] == '.') {pBuff[i] ='\0'; --i; break;}                     
         --i;                                                                   
      }                                                                         
      if (i<0) {pBuff[0] = '0';  pBuff[1] = '\0'; }                             
      if (i< (n-1)) { strcpy((pBuff+i+1), temp); }                              
   }                                                                            
   strcat(pBuff, " ");  /* add a tailing space */                               
                                                                                
 }                                                                              
                                                                                
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
char *a_fmtD(double *pData, int iQdpp, int npts) //data pointer, precision, #objects                                               
{                                                                               
   char temp[80];                                                               
   /* Assume that no one dare to use 80 char precision */                       
   char *pBuff=NULL;                                                            
   int  i, ntotal, nAlloc;                                                      
   int  width, nprecis, ndecade;                                                
   double r;                                                                    
                                                                                
                                                                                
   nAlloc = NBLOCK;                                                             
   if (!(pBuff= (char *) malloc(nAlloc)) ) {                                    
      printf("malloc failed in a_formatD\n");                                   
      exit(1);                                                                  
   }                                                                            
                                                                                
   ntotal = 0;                                                                  
   for (i=0; i<npts; i++) {                                                     
      /*   r = fabs(pData[i]); */                                               
      r = (pData[i] >= 0)? pData[i]: -pData[i];                                 
                                                                                
      if (r < DBLFMTBD) {                                                       
        sprintf(temp, "%*E", iQdpp, pData[i]);                                  
      } else {                                                                  
        ndecade = (int) log10(r);                                               
        if (r >= 1.0) {                                                         
           nprecis = iQdpp - 1 - ndecade;                                       
        } else {                                                                
           nprecis = iQdpp - ndecade;                                           
        }                                                                       
        sprintf(temp, "%-14.*lf", nprecis, pData[i]);                           
      } /* end r<DBMFMTBD */                                                    
                                                                                
      a_pack(temp, iQdpp);//changed********added iQdpp
                                                                                
      ntotal += strlen(temp);                                                   
      if (ntotal > (nAlloc+1)) {                                                
         nAlloc += NBLOCK;                                                      
         if (!(pBuff = (char *) realloc((char *) pBuff, nAlloc)) ) {            
            printf("realloc failed in a_formatD, n = %d\n", nAlloc);            
            exit(1);                                                            
         }                                                                      
      }                                                                         
      strcat(pBuff, temp);                                                      
   }                                                                            
                                                                                
   pBuff[ntotal -1 ] = '\0';                                                    
   return(pBuff);                                                               
}                                                                               
                                                                                
void a_prtD0(double v)                                                                 
{                                                                               
   char temp[30];  /* temporary string for analyzing variable size */           
   char temp1[30]; /* temporary string for processing the number   */           
   char * ind;     /* index of a character within a string         */           
   int num;        /* integer index for characters within a string */           
   int exp;        /* exponent of the floating point number        */           
   int width;      /* width for printing the floating point number */           
   int precis;     /* precision for printing                       */           
   int negative;   /* whether the number is negative or positive   */           
   int f_notat;    /* whether we formatted in f or e notation      */           
                                                                                
   if (v < 0)                                                                   
      negative = 1;                                                             
   else                                                                         
      negative = 0;                                                             
                                                                                
   sprintf(temp, "%.*E", QDPP, v);                                              
   /* find the power of the floating point number */                            
   ind = strchr(temp,'E');                                                      
   exp = atoi(ind + 1);                                                         
/*printf("input number: %s, power: %i\n", temp, exp);       ***/                
                                                                                
/* check for whether the exponent is positive or negative, and whether          
 * the number easily fits within the Printing Precision (QDPP).                 
    */                                                                          
   if (exp > 0)    /* number has positive exponent */                           
      if (exp < QDPP) {  /*and fits easily within printing precision */         
         f_notat = 1;                                                           
         width = QDPP + 1;     /* add one for the decimal point      */         
         if (v < 0)                                                             
            width++;           /* add one more for the negative sign */         
         precis = QDPP - exp - 1;                                               
         sprintf(temp, "%#*.*f", width, precis, v);                             
      }  /* end of positive exponent, fits within QDPP */                       
                                                                                
      else {  /* positive exponent, too big ==> needs E notation */             
         f_notat = 0;                                                           
         width = QDPP + 4;     /* add one for "e" and decimal point,            
                                * two for exponent                   */         
         if (v < 0)                                                             
            width++;           /* add one more for the negative sign */         
         if (exp > 99)                                                          
            width++;           /* add one more for large exponent    */         
         precis = QDPP - 1;                                                     
         sprintf(temp, "%*.*e", width, precis, v);                              
      }  /* end of positive exponent, does not fits within QDPP */              
                                                                                
   else { /* negative exponent */                                               
      /* see how many significant digits we've got */                           
      num = 0;                                                                  
      ind--;      /* pointer to last character before "E" */                    
      while ((*ind) == '0') {                                                   
         num++;                                                                 
         ind--;                                                                 
      }                                                                         
                                                                                
      if ((num >= -exp) || (7 > -exp))   {  /* use f format          */         
         f_notat = 1;                                                           
         width = QDPP +1 - exp; /*add one for decimal point, add exp */         
         if (v < 0)                                                             
            width++;            /*add one more for the negative sign */         
         precis = QDPP-1 - exp;                                                 
         /* increase precision for smaller numbers */                           
         sprintf(temp, "%*.*f", width, precis, v);                              
      }  /* end of negative exponent, use "f" notation */                       
                                                                                
      else {  /* negative exponent, use E notation */                           
         f_notat = 0;                                                           
         width = QDPP + 5;   /* add one for "e", one for decimal point,         
                      one for negative exp sign and two for exponent */         
         if (v < 0)                                                             
            width++;           /* add one more for the negative sign */         
         if (exp > 99)                                                          
            width++;           /* add one more for large exponent    */         
         precis = QDPP - 1;                                                     
         sprintf(temp, "%*.*e", width, precis, v);                              
      }  /* end of negative exponent, use "e" notation */                       
   }  /* end else negative exponent */                                          
/* printf("number so far ... \"%s\"\n", temp);      ***/                        
                                                                                
   /* strip off trailing 0's */                                                 
   if (f_notat) {  /* 0's start at the end of the string */                     
      num = strlen(temp);                                                       
      while (temp[num-1] == '0')  /* test last character */                     
         num--;                                                                 
      if (temp[num-1] == '.') /* skip decimal point if now last char */         
         num--;                                                                 
                                                                                
      temp[num] = '\0';                                                         
      printf("%s ", temp);                                                      
   }  /* end if "f" notation */                                                 
                                                                                
   else {  /* 0's start before the "e" */                                       
      ind = strchr(temp,'e');  /* rest of string, starting at "e" */            
      strcpy(temp1, ind);                                                       
      num = ind-temp;   /* string up to the "e" */                              
      while (temp[num-1] == '0')  /* test last character */                     
         num--;                                                                 
      if (temp[num-1] == '.') /* leave 1 digit past decimal point */            
         num++;                                                                 
                                                                                
      temp[num] = '\0';                                                         
      printf("%s%s ", temp, temp1);                                             
   }  /* end if "f" notation */                                                 
}                                                                               
                                                                                
/* This routine counts the no of ones in the boolean var pointed by p0.         
*/                                                                              
int no_of_ones(int r0, int * p0)                                                          
{                                                                               
int n, v1, v2, r1, t;                                                           
                                                                                
             n = 0;                                                             
             r1= (31+r0)>>5;                                                    
             for (v2=0; v2<r1; v2++) {                                          
               t = p0[v2];                                                      
               for (v1=0; v1<32; v1++) {                                        
                 if ( t==0)                                                     
                 break;                                                         
                 else if ( t < 0)                                               
                 n++;                                                           
                 t<<=1; }                                                       
               } return n;                                                      
}                                                                               
                                                                                
/*    Pass a boolean parameter to main function */                              
void passparmb (FILE * fpl, int lgth, int * p0)                                                  
    {int u0, tl, u1;                                                            
             for( u0 = 0; u0 <lgth/ 32; ++u0)  {                                
               p0[u0] = 0;                                                      
               for( u1 = 0; u1 < 32; ++u1)  {                                   
                 fscanf(fpl," %d",&tl);                                         
                 tl <<= (31 - u1);                                              
                 p0[u0] |= tl;                                                  
               }                                                                
             }                                                                  
             if( (lgth% 32) != 0)   p0[u0] = 0;                                 
               for( u1 = 0; u1 <lgth% 32; ++u1)  {                              
                 fscanf(fpl," %d",&tl);                                         
                 tl <<= (31 - u1);                                              
                 p0[u0] |= tl;                                                  
               }                                                                
     }                                                                          
                                                                                
/* print out boolean value */                                                   
void prntbool (int * p0, int cl)                                                          
    {int r0, r1, v1, v2, t;                                                     
       r0 = cl>> 5;                                                             
       r1 = cl & (0x0000001f);                                                  
                    for( v1 = 0; v1 < r0; ++v1)  {                              
                  t = p0[v1];                                                   
                  for(v2 = 0; v2 < 32; ++v2)  {                                 
                     if( t < 0 )    printf(" 1");                               
                     else    printf(" 0");                                      
                  t <<= 1; }                                                    
                  printf("\n");                                                 
               }                                                                
                  t = p0[v1];                                                   
                  for(v2 = 0; v2 < r1; ++v2)  {                                 
                     if( t < 0 )    printf(" 1");                               
                     else    printf(" 0");                                      
                  t <<= 1; }                                                    
     }                                                                          

                                                                                
/****** factorial fns ******/                                                   
int fact[13]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880,3628800,            
               39916800, 479001600};                                            
                                                                                
int ifac(int n)                                                                     
   {int z;                                                                      
    if (n<0 ) printf("Domain error in monadic ! fn.\n"); else                   
    if (n<13) z= fact[n];                                                       
    else                                                                        
  {printf("Change the result type of ifac fn(!A) to floating ponit.\n");        
    exit(99);}                                                                  
    return z;                                                                   
    }                                                                           
                                                                                
double efac(int n)                                                                  
   {double z;                                                                   
    int v1;                                                                     
    if (n<0 ) printf("Domain error in monadic ! fn.\n"); else                   
    if (n<13) z= fact[n];                                                       
    else                                                                        
      {z= fact[12];                                                             
       for (v1=13; v1<n+1; v1++)                                                
           z= z* v1;}                                                           
    return z;                                                                   
    }                                                                           
                                                                                
double ebin(int n,int m)                                                                
   {double z;                                                                   
    int u0, mn;                                                                 
    if (n<0 | m<0) printf("Domain error in monadic ! fn.\n");                   
    else if (n > m) z= 0; else if (n == m) z= 1; else                           
    if (m<13) z= fact[m]/(fact[n]*fact[m-n]);                                   
    else if (m < 86)                                                            
/*    z= efac(m)/(efac(n)*efac(m-n));      */                                   
      {z= 1;                                                                    
       if (n > m-n)                                                             
         {for (u0=n+1; u0<m+1; u0++)                                            
            z= z*u0;                                                            
          z= z/efac(m-n);}                                                      
       else                                                                     
         {for (u0=m-n+1; u0<m+1; u0++)                                          
            z= z*u0;                                                            
          z= z/efac(n);}}                                                       
    else                                                                        
      {z= 1; mn= m-n;                                                           
       if (n > mn)                                                              
/*       {for (u0=n+1; u0<m+1; u0++)       */                                   
          for (u0=1; u0<mn+1; u0++)                                             
            z= z*((u0+n)/u0);                                                   
/*        for (u0=mn+1; u0<m+1; u0++)                                           
            z= z*u0;}  */                                                       
       else                                                                     
          for (u0=1; u0<n+1; u0++)                                              
            z= z*((u0+mn)/u0); }                                                
/*        for (u0=n+1; u0<m+1; u0++)                                            
            z= z*u0;}}*/                                                        
    return z;                                                                   
    }                                                                           
/* random number generator for vs apl */                                        
                                                                                
int randomn(int n)                                                              
  {//extern int rseed;
	int rseed;                                                            
/* extern double floor(double x);  */                                           
/* double r2,m;                    */                                           
   int A, a, b, Q, Q_, r_, ab, bb, bbu, bbl, nl, nu, aa, ba, aba, i;            
   a= rseed>>16;                                                                
   b= rseed&m16; /* (rseed<<16)>>16;*/                                          
   ab= a*qdrl0;                                                                 
   bb= b*qdrl0;                                                                 
   bbl= bb&m16; /*(bb<<16)>>16;*/                                               
   bbu= bb>>16;                                                                 
   Q_= ab>>15;                                                                  
   if ( (i =bbu+(ab&m15))> m15)                                                 
     {Q_++; r_= ((i-m15-1)<<16)+bbl;}                                           
   else r_= (i<<16)+bbl;                                                        
/* rseed= (int) r2;  */                                                         
   rseed=  Q_+r_;                                                               
/* m= r2*n;          */                                                         
/* rseed= r*n;       */                                                         
/* i=1+(int)(ceil(m/largeint)); */                                              
   a= rseed>>16;                                                                
   b= rseed&m16; /* (rseed<<16)>>16;*/                                          
   nu= n>>16;                                                                   
   nl= n&m16;                                                                   
   ab= a*nl;                                                                    
   bb= b*nl;                                                                    
   bbl= bb&m16; /*(bb<<16)>>16;*/                                               
   aa= a*nu;                                                                    
   ba= b*nu;                                                                    
   bbu= bb>>16;                                                                 
   aba= ab+ba;                                                                  
/* i = ab>>15; */                                                               
   i = aa*2+(aba>>15);                                                          
/* if ( (r =bbu+(ab&m15))> m15) i++; */                                         
   if ( (bbu+(aba&m15))> m15) i++;                                              
/* i= i+QDIO; */                                                                
   return i;}                                                                   
                                                                                
/* This is a square matrix inverse program. The main function is a    */        
/* sample calling function. The algorithm is from W.H. Press et al,   */        
/* Numerical Recipes in C. The space for ro2 and p2 must be allocated */        
/* in advance. The variable n is the dimension of the square matrix   */        
/* ro2.This program only works for floating point numbers. For integer*/        
/* numbers, the matrix must be transferred to a floating point one.   */        
                                                                                
#define NMAX 100                                                                
#define TINY 1.0e-20                                                            
                                                                                
void mat_inverse(double* a,double* y,int n)                                                         
{  int i,j, indx[NMAX], q;                                                      
   double column[NMAX], d;                                                      
                                                                                
   if(n > NMAX)  {                                                              
     printf("The dimension is larger than %d\n",NMAX);                          
     printf("Increase NMAX in the library\n");                                  
     exit(99);                                                                  
   }                                                                            
                                                                                
   ludcmp(a,n,indx,&d);                                                         
   for(j = 0; j < n; ++j)  {                                                    
     for(i = 0; i < n; ++i)  column[i] = 0.0;                                   
     column[j] = 1.0;                                                           
     lubksb(a,n,indx,column);                                                   
     for(i = 0; i < n; ++i)  y[i*n+j] = column[i];                              
   }                                                                            
}                                                                               
                                                                                
void ludcmp(double *a,int n,int *indx,double *d)                                                              
{ int i,j,q,k,imax;                                                             
  double vv[NMAX], aamax, sum, dum, temp;                                       
                                                                                
  *d = 1.0;                                                                     
  for(i = 0; i < n; ++i)  {                                                     
    aamax = 0.0;                                                                
    q = i * n;                                                                  
    for(j = 0; j < n; ++j)                                                      
      if((temp=fabs(a[q+j])) > aamax)  aamax = temp;                            
    if(aamax == 0.0)  { printf("Singular matrix\n");  exit(99); }               
    vv[i] = 1./aamax;                                                           
  }                                                                             
                                                                                
  for(j = 0; j < n; ++j)  {                                                     
      for(i = 0; i < j; ++i)  {                                                 
        sum = a[i*n+j];                                                         
        for(k = 0; k < i; ++k)                                                  
            sum -= a[i*n+k] * a[k*n+j];                                         
          a[i*n+j] = sum;                                                       
      }                                                                         
    aamax = 0.0;                                                                
    for(i = j; i < n; ++i)  {                                                   
      sum = a[i*n+j];                                                           
      for(k = 0; k < j; ++k)                                                    
          sum -= a[i*n+k]*a[k*n+j];                                             
        a[i*n+j] = sum;                                                         
      dum = vv[i]*fabs(sum);                                                    
      if(dum >= aamax)  {                                                       
        imax = i;                                                               
        aamax = dum;                                                            
      }                                                                         
    }                                                                           
    if(j != imax)  {                                                            
      for(k = 0; k < n; ++k)   {                                                
        dum = a[imax*n+k];                                                      
        a[imax*n+k] = a[j*n+k];                                                 
        a[j*n+k] = dum;                                                         
      }                                                                         
      *d = -(*d);                                                               
      vv[imax] = vv[j];                                                         
    }                                                                           
    indx[j] = imax;                                                             
    if( a[j*(n+1)] == 0.0 )  a[j*(n+1)] = TINY;                                 
    if(j != (n-1))  {                                                           
      dum = 1./a[j*(n+1)];                                                      
      for(i = j+1; i < n; ++i)                                                  
        a[i*n+j] *= dum;                                                        
    }                                                                           
  }                                                                             
}                                                                               
                                                                                
                                                                                
void lubksb(double *a,int n,int *indx,double *b)                                                              
{ int i,j,ip,ii;                                                                
  double sum;                                                                   
                                                                                
  ii = -1;                                                                      
  for(i = 0; i < n; ++i)  {                                                     
    ip = indx[i];                                                               
    sum = b[ip];                                                                
    b[ip] = b[i];                                                               
    if(ii != -1)                                                                
      for(j = ii; j < i; ++j)                                                   
        sum -= a[i*n+j] * b[j];                                                 
    else  if(sum != 0)  ii = i;                                                 
    b[i] = sum;                                                                 
  }                                                                             
                                                                                
  for(i = n-1;i >= 0; --i)  {                                                   
    sum = b[i];                                                                 
    for(j = i+1; j < n; ++j)                                                    
        sum -= a[i*n+j]*b[j];                                                   
    b[i] = sum/a[i*(n+1)];                                                      
  }                                                                             
}                                                                               
//apl3lib3.c/* Convert boolean op to int or double  */                                      

void boolcvi (int* targ,int* ooc,int llgth,int lgth)                                           
   { int r1, v1, v2, t, u1;                                                     
             targ += llgth;                                                     
             r1= lgth>>5;                                                       
             v1=0;                                                              
             for (v2=0; v2<r1; v2++) {                                          
             t= ooc[v2];                                                        
             for (u1=0; u1<32; u1++) {                                          
               if ( t < 0)                                                      
                 targ[v1]=1;                                                    
               else                                                             
                 targ[v1]=0;                                                    
               t<<=1;                                                           
               v1++;}}                                                          
           if ( (r1=lgth&msk)!= 0 )                                             
             {t=  ooc  [v2];                                                    
             for (u1=0; u1<r1; u1++) {                                          
               if ( t < 0)                                                      
                targ[v1]=1;                                                     
               else                                                             
                targ[v1]=0;                                                     
               t<<=1;                                                           
               v1++;}}                                                          
      }                                                                         
                                                                                
/* Convert boolean op to int or double  */                                      
void boolcvd (double* targ,int* ooc,int llgth,int lgth)                                           
   { int r1, v1, v2, t, u1;                                                     
             targ += llgth;                                                     
             r1= lgth>>5;                                                       
             v1=0;                                                              
             for (v2=0; v2<r1; v2++) {                                          
             t= ooc[v2];                                                        
             for (u1=0; u1<32; u1++) {                                          
               if ( t < 0)                                                      
                 targ[v1]=1;                                                    
               else                                                             
                 targ[v1]=0;                                                    
               t<<=1;                                                           
               v1++;}}                                                          
           if ( (r1=lgth&msk)!= 0 )                                             
/*    GEN 'if (',OOPL,CHE,'=r1*32)' è** 91/7/3J**/                              
             {t=  ooc  [v2];                                                    
             for (u1=0; u1<r1; u1++) {                                          
               if ( t < 0)                                                      
                targ[v1]=1;                                                     
               else                                                             
                targ[v1]=0;                                                     
               t<<=1;                                                           
               v1++;}}                                                          
      }                                                                         
                                                                                
/* Convert segment of boolean op to int or double. Called by MDCATENA */        
void boolcv1i(int* targ,int* ooc,int n,int i,int sl)                                              
   { int r1, r2, r8, v1, v2, t, u1, u2;                                         
           r2 = msk& i;                                                         
           r1 = min(r2, sl);                                                    
/*    GEN 'if ((u1=0)',CHE,'= r1)' è initial segment è != */                    
           if ((u1=0) != r1)                                                    
             {t= ooc[i>>5]<<r2;                                                 
             for (u1=0; u1<r1; u1++) {                                          
               if ( t < 0)                                                      
/*6]  GEN '     ',TARC,'1;'     */                                              
                  targ[u1]= 1;                                                  
               else                                                             
                  targ[u1]= 0;                                                  
               t<<=1;}}                                                         
             r2= ( sl   -r1)>>5;                                                
             r8= (n-r1)>>5;                                                     
             for (v2=0; v2<r2; v2++) {                                          
               t= ooc[r8+v2];                                                   
             for (u1=0; u1<32; u1++) {                                          
               if ( t < 0)                                                      
                  targ[u1]= 1;                                                  
               else                                                             
                  targ[u1]= 0;                                                  
               t<<=1;                                                           
               u1++;}}                                                          
/*    GEN 'if ((r2= (',SL,'-r1)&msk)',CHE,'= 0)' è** 92/2/14**/                 
           if ((r2= (sl-r1)&msk) != 0)                                          
             {t=  ooc[(i-r1)>>5];                                               
             for (u2=0; u2<r2; u2++) {                                          
               if ( t < 0)                                                      
           /*   ',TARC,'1;' */                                                  
                  targ[u1]= 1;                                                  
               else                                                             
                  targ[u1]= 0;                                                  
               t<<=1;                                                           
               u1++;}}                                                          
      }                                                                         
                                                                                
void boolcv1d(double* targ,int* ooc,int n,int i,int sl)                                              
   { int r1, r2, r8, v1, v2, t, u1, u2;                                         
           r2 = msk& i;                                                         
           r1 = min(r2, sl);                                                    
/*    GEN 'if ((u1=0)',CHE,'= r1)' è initial segment è != */                    
           if ((u1=0) != r1)                                                    
             {t= ooc[i>>5]<<r2;                                                 
             for (u1=0; u1<r1; u1++) {                                          
               if ( t < 0)                                                      
/*6]  GEN '     ',TARC,'1;'     */                                              
                  targ[u1]= 1;                                                  
               else                                                             
                  targ[u1]= 0;                                                  
               t<<=1;}}                                                         
             r2= ( sl   -r1)>>5;                                                
             r8= (n-r1)>>5;                                                     
             for (v2=0; v2<r2; v2++) {                                          
               t= ooc[r8+v2];                                                   
             for (u1=0; u1<32; u1++) {                                          
               if ( t < 0)                                                      
                  targ[u1]= 1;                                                  
               else                                                             
                  targ[u1]= 0;                                                  
               t<<=1;                                                           
               u1++;}}                                                          
/*    GEN 'if ((r2= (',SL,'-r1)&msk)',CHE,'= 0)' è** 92/2/14**/                 
           if ((r2= (sl-r1)&msk) != 0)                                          
             {t=  ooc[(i-r1)>>5];                                               
             for (u2=0; u2<r2; u2++) {                                          
               if ( t < 0)                                                      
           /*   ',TARC,'1;' */                                                  
                  targ[u1]= 1;                                                  
               else                                                             
                  targ[u1]= 0;                                                  
               t<<=1;                                                           
               u1++;}}                                                          
      }                                                                         
//#include "aplc0.h"//apl3lib4.c
void bitsmove (int *targ,int* rrc,int r0,int n)                                                
    {int v1, r1, i, t, tl, ttl;                                                 
     unsigned int wa, wb;                                                       
           r1= r0; r0>>=5;                                                      
           if (n < 0) {                                                         
              for (v1=0; v1<r0; v1++)                                           
                 targ[v1]= rrc[v1];                                             
              if ((tl=r1&0x0000001f) != 0) /* CHE */                            
             {wa= rrc[v1];                                                      
              targ[v1]=(wa>>32-tl)<<32-tl;}}                                    
           else if ((i= n &0x0000001f)==0)                                      
             {r0 =(r1+31)>>5;                                                   
               n =n>>5;                                                         
              for (v1=0; v1<r0; v1++)                                           
                 targ[v1]= rrc[n+v1];}                                          
           else                                                                 
             {ttl=r1&0x0000001f;                                                
                n =n>>5;                                                        
                t = r1-32+i;                                                    
                r0 =t>>5;                                                       
               tl= t&0x0000001f;                                                
/*    BITSMOVE  */                                                              
/*   è move a bit-string to a targ starting at i-th bit                         
     è if r0=r1 then goto tail */                                               
              wa= rrc[n];                                                       
              wa <<=i;                                                          
              targ[0]=wa;                                                       
         if (t >= 0 )                                                           
            {n++;                                                               
             i= 32-i;                                                           
            for (v1=0; v1<r0; v1++)                                             
             {wa= wb= rrc[n+v1];                                                
              wa >>=i;                                                          
              wa |= targ[v1]; /* */                                             
              targ[v1]=wa;   /****** GETING THE FIRST HALP OF ROP.W*/           
              wb <<=(32-i);                                                     
              targ[v1+1]=wb;}                                                   
            if (tl|= 0) /* CHO */                                               
              {wa= wb=  rrc[n+r0];   /**** MOVE TAIL PIECE *****/               
               wa >>=i;                                                         
               wa |= targ[r0];  /* CHO */                                       
               targ[r0]=wa;}    /***** GETING THE FIRST HALP OF ROP.t */        
            if (ttl<i)                                                          
                {wb <<=(32-i);   /*** 90/11/19 DAVID[10]*/                      
              targ[r0+1]=wb;}}}  /*GETING THE 2nd HALP OF ROP.t92/8/6+*/        
   }                                                                            
                                                                                
/* BITSMOVEC 1992 9 3 */                                                        
/* move the complem of a bit-string to a targ place starti at i-th bit */       
void bitsmovc (int* targ,int* rrc,int ll,int rrl,int i)                                           
    {int v1, r1, r2, tl, ttl;                                                   
     unsigned int wa, wb;                                                       
              r1=   rrl    >>5;                                                 
              r2=   rrl    &msk;                                                
              for (v1=0; v1<r1; v1++)                                           
             {wa= wb= ~rrc[v1];                                                 
              wa >>=i;                                                          
              wa |= targ[ll+v1];                                                
              targ[ll+v1]= wa;                                                  
              wb <<=(32-i);                                                     
              targ[ll+v1+1]= wb;}                                               
           if (r2      != 0)                                                    
                {wb=  ~rrc[r1];                                                 
                 wa= wb= (wb>>32-r2)<<32-r2;                                    
                 wa >>=i;                                                       
                 wa |= targ[ll+r1];                                             
                 targ[ll+v1]= wa;                                               
                 if (i+r2 > 32)                                                 
                 targ[ll+r1+1]= wb<<32-i;}}                                     
                                                                                
/*   move a bit-string to a targ place starting at i-th bit */                  
void bitsmov0 (int* targ,int* rrc,int ll,int rrl,int i)                                           
    {int v1, r1, r2;                                                            
     unsigned int wa, wb;                                                       
              r1=   rrl    >>5;                                                 
              r2=   rrl&msk;                                                    
              for (v1=0; v1<r1; v1++)                                           
             {wa= wb= rrc[v1];                                                  
              wa >>=i;                                                          
              wa |= targ[ll+v1];                                                
              targ[ll+v1]= wa;                                                  
              wb <<=(32-i);                                                     
              targ[ll+v1+1]=wb;}                                                
           if (r2!= 0)                                                          
                 {wa= wb= rrc[r1];                                              
                  wa >>=i;                                                      
              wa |= targ[ll+r1];                                                
              targ[ll+r1]= wa;                                                  
             if (i+r2 > 32)                                                     
/* 93/1/13     if (r1==0) targ[ll+r1+1]= wb<<r2-(32-i);                         
               else */targ[ll+r1+1]= wb<<32-i;}                                 
      }                                                                         
                                                                                
void bitsmovs (int* targ,int rrc,int ll,int rrl,int i)                                           
    {int v1, r1, r2;                                                            
     unsigned int wa, wb;                                                       
              r1=   rrl    >>5;                                                 
              r2=   rrl&msk;                                                    
              for (v1=0; v1<r1; v1++)                                           
             {wa= wb= rrc;                                                      
              wa >>=i;                                                          
              wa |= targ[ll+v1];                                                
              targ[ll+v1]= wa;                                                  
              wb <<=(32-i);                                                     
              targ[ll+v1+1]=wb;}                                                
           if (r2!= 0)                                                          
                 {wa= wb= rrc;                                                  
                  wa >>=i;                                                      
              wa |= targ[ll+r1];                                                
              targ[ll+r1]= wa;                                                  
             if (i+r2 > 32)                                                     
             if (r1==0) targ[ll+r1+1]= wb<<r2-(32-i);                           
             else targ[ll+r1+1]= wb<<32-i;}                                     
      }                                                                         
                                                                                
/*     move a bit-string starting at word sw bit position si to                 
       targ word qw bit position qi. */                                         
int qw, qi;                                                              
//extern int qw, qi;                                                              
                                                                                
/*int  bitsmov1 (targ, rrc, sw, si, lslg) */                                    
void  bitsmov1 (int* targ,int* rrc,int sw,int si,int lslg)                                        
    {int v1, r1, r2, t, tl, ttl, v0;                                            
     unsigned int wa, wb;                                                       
/*            z= 0;                  */                                         
              if (si!= 0)                                                       
                {wa= rrc[sw];                                                   
                 wa <<= si;                                                     
                 wb= targ[qw]= targ[qw]|wa>>qi;                                 
                 t = qi+ lslg;                                                  
/*** 91/7/10§J, deal with t = 32 case in CUT ***/                               
                 if((t == 32) && (qi >= si))                                    
                   { qi = t = 0;  ++qw;                                         
/*                   if ((jumpmf=lsidef)) goto exitlb else continue;} */        
                     goto exit;}                                                
                 else                                                           
                 if (32> t)                                                     
                   if (32-si<  lslg  )                                          
                     {qi= qi+(32-si); r2=   lslg -(32-si);                      
                      sw++; goto tail;}                                         
                   else                                                         
                     {qi= t;                                                    
                      wb>>=32-t;                                                
                      targ[qw]= wb<<32-t;                                       
/*                   if (lsidef) goto midlb else continue;}*/                   
/*                   z= rsidef; goto exit;}                */                   
                     goto exit;}                                                
                   else {sw++;                                                  
                   if (qi> si)                                                  
                     {if (32>  lslg  +si) t=   lslg  -(32-qi);                  
                      else {t= qi-si;}                                          
                      wa<<= 32-qi;                                              
                      wa>>= 32-t;                                               
                      targ[++qw]= wa<<32-t;                                     
                      qi= t;                                                    
/*                   if (lsidef) {if (32>',LSLG,'+si) goto midbb;}              
                     else if (32>',LSLG,'+si) continue;}   */                   
                     if (32>lslg+si) goto exit;}                                
                   else                                                         
                     qi=qi+32-si;}                                              
                   r1= (  lslg  -(32-si))>>5;                                   
                   r2= (  lslg  -(32-si))&msk;}                                 
              else                                                              
                {r1=   lslg  >>5;                                               
                 r2=   lslg  &msk;}                                             
              si= 0;                                                            
          for (v0=0; v0<r1; v0++)                                               
             {wa= wb=   rrc  [sw++];                                            
              wa >>= qi;                                                        
              wa       |=  targ[qw];                                            
              targ[qw++] =wa;                                                   
              wb <<=(32-qi);                                                    
              targ[qw]=wb;                                                      
              }                                                                 
tail:                                                                           
           if (r2 != 0)                                                         
             {wb= rrc[sw]>>32-r2;                                               
              wb= wa= wb<<32-r2;                                                
              wa >>=qi;                                                         
              wa |=  targ[qw];                                                  
              targ[qw]= wa;                                                     
              t = r2+qi;                                                        
              if (t< 32) qi= t;                                                 
              else if (t==32) {qi= 0; qw++;}                                    
              else                                                              
                {targ[++qw]= wb<<32-qi;                                         
                 qi= qi+r2-32;}}                                                
exit:; }                                                                        
                                                                                
//#include "aplc0.h" apl3lib5.c
/*** called by genidxof boolean case ***/                                       
int  findfst0(int* llc,int lopl,int qdio)                                                  
     {int i, r0, t, v1, u0, tl;                                                 
           i= qdio;                                                             
           r0= lopl;                                                            
           r0>>=5;                                                              
        for (v1=0; v1<r0; v1++)                                                 
             if ((t=llc[v1] )==0xffffffff)                                      
             i+=32;                                                             
             else                                                               
        for (u0=0; u0<32; u0++)                                                 
             if (t>=0) goto found;                                              
             else                                                               
              {t<<=1;                                                           
               i++;}                                                            
             if ((tl= lopl&0x0000001f) != 0)                                    
               {t= llc[v1];                                                     
        for (u0=0; u0<tl; u0++)                                                 
             if (t>=0) goto found;                                              
             else                                                               
              {t<<=1;                                                           
               i++;}}                                                           
found:return i;}                                                                
                                                                                
int  findfst1(int* llc,int lopl,int qdio)                                                  
     {int i, r0, t, v1, u0, tl;                                                 
           i= qdio;                                                             
           r0= lopl;                                                            
           r0>>=5;                                                              
        for (v1=0; v1<r0; v1++)                                                 
             if ((t=llc[v1] )==0)                                               
             i+=32;                                                             
             else                                                               
        for (u0=0; u0<32; u0++)                                                 
             if (t< 0) goto found;                                              
             else                                                               
              {t<<=1;                                                           
               i++;}                                                            
             if ((tl=  lopl  &0x0000001f)     != 0)                             
             if ((t= llc[v1])== 0) i+= tl;                                      
             else                                                               
        for (u0=0; u0<tl; u0++)                                                 
             if (t< 0) goto found;                                              
             else                                                               
              {t<<=1;                                                           
               i++;}                                                            
found: return i;}                                                               
                                                                                
void boolidxof(int* ttc,int* llc,int* rrc,int lopl,int ropl,int qdio)                                 
    {int w0, w1, r1, n, j, u0, v1;                                              
     w0= findfst0(llc, lopl, qdio);                                             
     w1= findfst1(llc, lopl, qdio);                                             
     r1= ropl>>5;                                                               
     for (v1=0; v1<r1; v1++)                                                    
        {n= rrc[v1];                                                            
         for (u0=0; u0<32; u0++)                                                
             {if (n<0)                                                          
              ttc[32*v1+u0]= w1;                                                
              else ttc[32*v1+u0]= w0;                                           
              n<<=1;}}                                                          
     j = ropl&msk;                                                              
     n= rrc[v1];                                                                
     for (u0=0; u0<j ; u0++)                                                    
        {if (n<0)                                                               
         ttc[32*r1+u0]= w1;                                                     
         else ttc[32*r1+u0]= w0;                                                
             n<<=1;}                                                            
     }                                                                          
                                                                                
void bol1idxof(int* ttc,int llc,int* rrc,int ropl,int qdio)                                       
    {int w0, w1, r1, n, j, u0, v1;                                              
/*   w0= findfst0(llc, lopl, qdio);                                             
     w1= findfst1(llc, lopl, qdio);                                             
     if (llc== 0) w0= qdio; else w0= qdio+1;                                    
     if (llc== 0) w1= qdio+1; else w1= qdio;   */                               
     w0= qdio+llc; w1= qdio+(llc==0);                                           
     r1= ropl>>5;                                                               
     for (v1=0; v1<r1; v1++)                                                    
        {n= rrc[v1];                                                            
         for (u0=0; u0<32; u0++)                                                
             {if (n<0)                                                          
              ttc[32*v1+u0]= w1;                                                
              else ttc[32*v1+u0]= w0;                                           
              n<<=1;}}                                                          
     j = ropl&msk;                                                              
     n= rrc[v1];                                                                
     for (u0=0; u0<j ; u0++)                                                    
        {if (n<0)                                                               
         ttc[32*r1+u0]= w1;                                                     
         else ttc[32*r1+u0]= w0;                                                
             n<<=1;}                                                            
     }                                                                          
/* code containing wrapmove in genreshp */                                      
void wrapmove(int* ttc,int* rrc,int r0,int ropl)                                               
    {int i, u0, n, tl, ttl, r1, v1, j;                                          
     unsigned int wa, wb;                                                       
            n=r0;                                                               
            r0+=31;                                                             
            r0 >>= 5;                                                           
            ttl= n&0x0000001f;                                                  
            tl= ropl   &0x0000001f;                                             
            if (n<=  ropl  )                                                    
              for (v1=0; v1<r0; v1++)                                           
                ttc[v1]= rrc[v1];                                               
            else if ( 0 == tl)                                                  
                  {r1=0;                                                        
                   j=  ropl  >>5;                                               
                   while  (r0>j      ) {                                        
                     for (v1=0; v1< j; v1++)                                    
                       ttc[r1+v1]= rrc[v1];                                     
                       r0=r0-j;                                                 
                       r1=r1+j;}                                                
                   if (r0  != 0)                                                
                   for (v1=0; v1<r0; v1++)                                      
                     ttc[r1+v1]= rrc[v1];}                                      
                 else    /*** irregular case **/                                
/*8  HVTL:≈(RLGTH∂ 2 4 8 16)/EASYPAD */                                         
                   if (ropl&0xffffffe1 == 0)                                    
                     {r1=tl=0;                                                  
                      for (v1=0; v1<32%ropl; v1++)                              
                        {tl>>= ropl;                                            
                         tl|=  rrc[0];}                                         
                      for (v1=0; v1<r0; v1++)                                   
                        ttc[v1]= tl;}                                           
                   else                                                         
/*9] è We first move ROP to TARG (i=0 case).*/                                  
                     {r1= ropl;                                                 
                      r1+=31;                                                   
                      r1 >>= 5;                                                 
                      for (v1=0; v1<r1; v1++)                                   
                        ttc[v1]= rrc[v1];                                       
/*     move a bit-string wrapped around ROP into a targ starting                
       at i-th bit; if r0=r1 then goto tail */                                  
/*     WHILE v1<r0 DO                                                           
         {FOR u0<r1 move whole words of ROP to TARG                             
              u1++; v1++; if v1=r0 break FOR}                                   
         IF (v1=r1 & iÚtl THEN break;                                           
         {move tail of ROP to TARG                                              
            if 32Ûnew(i)=(Rtail)+i then                                         
              {move half-tail; v1++; if v1=r0 break}}                           
       ENDWHILE */                                                              
                      i=tl;                                                     
                      v1=r1=r1-1;                                               
                      while (v1<r0) {                                           
                        for (u0=0; u0<r1; u0++)                                 
                          {wa= wb= rrc[u0];                                     
                           wa >>=i;                                             
                           wa |= ttc[v1];                                       
                           ttc[v1]=wa;                                          
                           if (v1+1==r0) {v1++; i=ttl; break;}                  
                           wb <<=(32-i);                                        
                           ttc[v1+1]=wb;                                        
                           v1++;}                                               
                      if ((v1==r0)&(i>=ttl))                                    
                        break;                                                  
                      wa= wb= rrc[r1];                                          
                      wa >>=i;                                                  
                      wa |=  ttc  [v1];                                         
                      ttc [v1]=wa;                                              
                      i +=tl;                                                   
                      if (32<=i)                                                
                        {i-=32;                                                 
                         wb <<=(tl-i);                                          
                         if (v1+1<r0)                                           
                           ttc[v1+1]=wb;                                        
                         v1++;}}                                                
                }                                                               
            if (ttl!=0)                                                         
              {wa= ttc[n>>5];                                                   
               ttc[n>>5] =(wa>>32-ttl)<<32-ttl;}                                
   }                                                                            
//apl3lib7.c
//#include "aplc0.h"

int count3b0(int tl,int j,int n)
    {int v1;
               for (v1=0; v1<j; v1++) {
                 if ( tl==0)
                 break;
                 else if ( ((int) tl) < 0)
                 n++;
                 tl<<=1; }
     return n;
     }

/* extern int n; */
int count32b(int t,int n)
    {int v1;
               for (v1=0; v1<32; v1++) {
                 if ( t==0)
                 break;
                 else if ( t< 0)
                 n++;
                 t<<=1; }
     return n;
     }

/*     +/BM    */
void breductv(int *ttc,int * rrc,int  r0,int lplg0)
    {int u0, v2, n, i, j, t, tl, r2, r1;
     i= t= 0; r2= -1;
     for (u0=0; u0<r0; u0++)
            {n = 0;
             j= min(lplg0, 32-i);
             if (i!=0)
             {tl=t<<i;
              n = count3b0(tl, j, n);
             }
             else if (lplg0<32)
               {i= lplg0; r2++; goto cutlb;}
             else {j=0; if (u0!= 0) r2--;}
             if (i+lplg0 <32)
                {i+= lplg0; goto clb;}
             else if (i+lplg0  ==32)
                {i=0; goto clb;}
             r1= (lplg0-j)>>5;
             i = (lplg0+i)&msk;
              r2++;
             for (v2=0; v2<r1; v2++) {
                t = rrc[r2++];
                n = count32b(t, n);
               }
cutlb:       if (i!=0)
             {t = tl= rrc[r2];
              n = count3b0(tl, i, n);}
clb: ttc[u0]= n;}
    }

/*     +/Bool vect */
int  breduct0(int *rrc, int ropl)
    {int v1, n, t, v2, r0, r1;
             r0=  ropl  ;
             n = 0;
             r1= (31+r0)>>5;
             for (v1=0; v1<r1; v1++) {
               t = rrc[v1];
               for (v2=0; v2<32; v2++) {
                 if ( t==0) break; else if (t<0) n++; t<<=1;}}
             return  n;
     }

/*     +ªBool vect  */
void bscan0(int* ttc,int* rrc, int ropl)
    {int n, t, tl, v1, v2, r0, u1, r1;
             r0= ropl;
             n = 0;
             r1= r0>>5;
             for (v1=0; v1<r1; v1++) {
               u1=32*v1;
               t = rrc[v1] ;
               for (v2=0; v2<32; v2++) {
                 if ( t < 0) n++;
                 ttc[u1+v2]= n;
                 t<<=1;}}
               if ((tl=r0&msk)!=0)
                 {u1=r1*32;
               t = rrc[r1];
               for (v2=0; v2<tl; v2++) {
                 if ( t < 0) n++;
               ttc[u1+v2]= n;
                 t<<=1;}}
      }

/*     Kernel of Bool ÿª   */
void bscan20(int* ttc,int* pt,unsigned int * pwa,int  v1,int  segl, int i, int j)
    {int v2, t;
     unsigned int wa;
     t= *pt; wa= *pwa;
     for (v2=0; v2< segl; v2++)
         {if (wa & (t<0)) wa=0;
          else wa |= (t<0);
          if (wa == 1)
            ttc[j+v1]= ttc[j+v1]|(lfb>>v2+i);
          t<<=1;}
     *pwa= wa; *pt= t;
     }

/* ÿªB                              */
void gscan20m(int* ttc,int* rrc,int r0,int n)
    {int i, v1, u0, tl, t, r8, r2, r1, j;
     unsigned int wa;
       for (u0=0; u0<r0/n; u0++)
              {j= n*u0; i= j&msk; v1= j= j>>5;
               wa=0;
               if (i>0) {r8= min(n,32-i);
                 bscan20(ttc,&t,&wa, v1, r8, i, 0);
                 if (r8>n) goto segend;
                 else {r2= n-r8; j++;}}
               else r2= n;
               r1= r2>>5;
               for (v1=0; v1<r1; v1++)
                 {t = rrc[v1];
                  bscan20(ttc,&t,&wa, v1, 32, 0, j);}
               if ((tl= r2 &msk) > 0)
                 {t = rrc[j+v1];
                  bscan20(ttc,&t,&wa, v1, tl, 0, j);}
segend:;       }
      }

void gscan20v(int* ttc,int* rrc,int r0,int n)
    {int t, tl, i, v1, u0, r2, r1, r8, j;
     unsigned int wa;
              r2= r0;
              wa=0;
              r1= r2>>5;
              for (v1=0; v1<r1; v1++)
                {t = rrc[v1];
                 bscan20(ttc,&t,&wa, v1, 32, 0, 0);}
              if ((tl= r2 &msk) > 0)
                {t = rrc[v1];
                 bscan20(ttc,&t,&wa, v1, tl, 0, 0);}
     }
//apl3lib8.c
//#include "aplc0.h"                                                              
                                                                                
/*    copy string of 1s to targ place word TW position i lgth RLTH */           
void copybits1(int* ttc,int i,int j,int rlth)                                                 
    {int n, r1, v1;                                                             
     unsigned int wa;                                                           
             if (i      |=0)  {                                                 
               wa= alf>>i;                                                      
               if ((n=32-i-rlth  )>0)  {wa= (wa>>n)<<n;                         
                 ttc[j]= ttc[j]    |wa;                                         
                 goto cutlb;}                                                   
               else { ttc[j] = ttc[j] | wa;                                     
                     n= rlth-32+i; j++;}}                                       
               else n= rlth;                                                    
             r1= n>>5;                                                          
             for (v1=0; v1<r1; v1++)                                            
               ttc[v1+j]= alf;                                                  
             if ((n= n&msk) > 0)                                                
               ttc[v1+j]= (alf>>32-n)<<32-n;                                    
cutlb:;                                                                         
     }                                                                          
                                                                                
/* bits OR reduction subroutine for linking by c language program */            
/* void aplbit0(r0, size, ro0)                                  */              
/* pos: bool-element position, i:bit pos/rel.32. size:string length */          
/* ro0 is the ROP variable */                                                   
void aplbit0(int* p0,int u0,int r0,int size,int* ro0)                                             
{                                                                               
 int v2, i, j, t, w, u1, u2, r1, r2, i0, r3, pos;                               
/*unsigned int lfb= 0x80000000;  92/10/19 */                                    
for (pos=0; pos<r0; pos++)                                                      
 {t= v2= 0;                                                                     
  i0= pos&msk;                                                                  
  r3= pos>>5;                                                                   
  i= (pos*size)&msk;                                                            
  r2= (pos*size)>>5;                                                            
  j= min(size,32-i);                                                            
/* head segment */                                                              
  if (i!=0)                                                                     
   {w= ro0[r2]<<i;                                                              
    for (u1=0; u1<j; u1++)                                                      
      {if (w<0) goto end; w<<=1;}}                                              
  else if (size<32) {i= size; goto cutlb;}                                      
/*else {j= 0;} */                                                               
  else {j= 0; if (u0!=0) r2--;}                                                 
  if (i+size<32) {i+=size; goto end0;}                                          
  else if (i+size==32) {i= 0; goto end0;}                                       
  r1= (size-j)>>5;                                                              
  i= (size+i)&msk;                                                              
  r2++;                                                                         
/* whole word loop */                                                           
  for (u2=0; u2<r1; u2++)                                                       
    {if (ro0[r2]!=0) goto end; r2++;}                                           
/* tail segment */                                                              
cutlb: if (i!=0)                                                                
  { w= ro0[r2];                                                                 
    for (u1=0; u1<i; u1++)  /* 91/7/11Ju, the upper bound was j. */             
      {if (w<0) goto end; w<<=1;}}                                              
    goto end0;                                                                  
end: t=1;                                                                       
end0:/* return t; */                                                            
  if (t!=0)                                                                     
  p0[r3]= p0[r3]|(lfb>>i0);}                                                    
}                                                                               
                                                                                
                                                                                
void  aplbit1(int r0,int v3,int* ttc,int* rrc)                                                 
     {int u0, u2, v1, j, t, r1;                                                 
      for (u0=0; u0<r0; u0++)                                                   
        {t= 1;                                                                  
         for (u2=0; u2<v3; u2++)                                                
           {j= rrc[(r1=u0*v3+u2)>>5];                                           
            if (j<<(r1&msk)>=0) {t= 0; break;}}                                 
         if (t==1)                                                              
           {v1=u0>>5;                                                           
            ttc[v1]= ttc[v1]|lfb>>(u0&msk);}}                                   
      }                                                                         
                                                                                
void  aplbit2(int r0,int v3,int* ttc,int* rrc)                                                 
     {int u0, u2, v1, t, j, r1;                                                 
      for (u0=0; u0<r0; u0++)                                                   
             {t= 0;                                                             
         for (u2=0; u2<v3; u2++)                                                
              {j= rrc[(r1=r0*u2+u0)>>5];                                        
               if (j<<(r1&msk)<0) {t= 1; break;}}                               
             if (t==1)                                                          
              {v1=u0>>5;                                                        
               ttc[v1]= ttc[v1]|lfb>>(u0&msk);}}                                
      }                                                                         
                                                                                
void  aplbit3(int r0,int v3,int* ttc,int* rrc)                                                 
     {int u0, u2, v1, t, j, r1;                                                 
      for (u0=0; u0<r0; u0++)                                                   
          {t= 1;                                                                
         for (u2=0; u2<v3; u2++)                                                
              {j= rrc[(r1=r0*u2+u0)>>5];                                        
               if (j<<(r1&msk)>=0) {t= 0; break;}}                              
             if (t==1)                                                          
              {v1=u0>>5;                                                        
               ttc[v1]= ttc[v1]|lfb>>(u0&msk);}}                                
      }                                                                         
                                                                                
void all1s(int* ttc,int r0)                                                             
    {int v1, r1, r2;                                                            
     r1= r0>>5;                                                                 
     for (v1=0; v1<r1; v1++)                                                    
       ttc[v1]= 0xffffffff;                                                     
     if ((r2= r0&msk) != 0)                                                     
       ttc[v1]= 0x80000000;                                                     
    }                                                                           
//apl3lib9.c
void reversi(int* ttc,int* rrc,int v3,int n0,int r1,int seg,int tl)                                     
    {int u0, v1, u1, t;                                                         
              for (u1=0; u1<r1; ++u1) {                                         
                t = u1 * seg;                                                   
              for (v1=0; v1< seg; ++v1) {                                       
                ttc[n0+v1+t] = rrc[n0+v1+v3-t];                                 
                ttc[n0+v1+v3-t] = rrc[n0+v1+t];}}                               
              if (tl |=0) {                                                     
                t = r1 * seg;                                                   
              for (v1=0; v1< seg; ++v1)                                         
                ttc[n0+v1+t] = rrc[n0+v1+t];}                                   
    }                                                                           
                                                                                
void reversm(double* ttc,int* rrc,int v3,int n0,int r1,int seg,int tl)                                     
    {int u0, v1, u1, t;                                                         
              for (u1=0; u1<r1; ++u1) {                                         
                t = u1 * seg;                                                   
              for (v1=0; v1< seg; ++v1) {                                       
                ttc[n0+v1+t] = rrc[n0+v1+v3-t];                                 
                ttc[n0+v1+v3-t] = rrc[n0+v1+t];}}                               
              if (tl |=0) {                                                     
                t = r1 * seg;                                                   
              for (v1=0; v1< seg; ++v1)                                         
                ttc[n0+v1+t] = rrc[n0+v1+t];}                                   
    }                                                                           
                                                                                
void reversd(double* ttc,double* rrc,int v3,int n0,int r1,int seg,int tl)                                     
    {int u0, v1, u1, t;                                                         
              for (u1=0; u1<r1; ++u1) {                                         
                t = u1 * seg;                                                   
              for (v1=0; v1< seg; ++v1) {                                       
                ttc[n0+v1+t] = rrc[n0+v1+v3-t];                                 
                ttc[n0+v1+v3-t] = rrc[n0+v1+t];}}                               
              if (tl |=0) {                                                     
                t = r1 * seg;                                                   
              for (v1=0; v1< seg; ++v1)                                         
                ttc[n0+v1+t] = rrc[n0+v1+t];}                                   
    }                                                                           
                                                                                
void reversc(char* ttc,char* rrc,int v3,int n0,int r1,int seg,int tl)                                     
    {int u0, v1, u1, t;                                                         
              for (u1=0; u1<r1; ++u1) {                                         
                t = u1 * seg;                                                   
              for (v1=0; v1< seg; ++v1) {                                       
                ttc[n0+v1+t] = rrc[n0+v1+v3-t];                                 
                ttc[n0+v1+v3-t] = rrc[n0+v1+t];}}                               
              if (tl |=0) {                                                     
                t = r1 * seg;                                                   
              for (v1=0; v1< seg; ++v1)                                         
                ttc[n0+v1+t] = rrc[n0+v1+t];}                                   
    }                                                                           
                                                                                
void areversi(int* ttc,int* rrc,int q0,int r1,int r2,int seg)                                        
    {int v3, tl, n, u0;                                                         
              v3 = seg*(r1-1);                                                  
              tl=r1; tl<<=31; tl>>=31; r1>>=1;                                  
              for (u0=0; u0<r2; ++u0)                                           
                { n=u0*q0;                                                      
                  reversi(ttc, rrc, v3, n, r1, seg, tl);}                       
    }                                                                           
                                                                                
void areversm(double* ttc,int* rrc,int q0,int r1,int r2,int seg)                                        
    {int v3, tl, n, u0;                                                         
              v3 = seg*(r1-1);                                                  
              tl=r1; tl<<=31; tl>>=31; r1>>=1;                                  
              for (u0=0; u0<r2; ++u0)                                           
                { n=u0*q0;                                                      
                  reversm(ttc, rrc, v3, n, r1, seg, tl);}                       
    }                                                                           
                                                                                
void areversd(double* ttc,double* rrc,int q0,int r1,int r2,int seg)                                        
    {int v3, tl, n, u0;                                                         
              v3 = seg*(r1-1);                                                  
              tl=r1; tl<<=31; tl>>=31; r1>>=1;                                  
              for (u0=0; u0<r2; ++u0)                                           
                { n=u0*q0;                                                      
                  reversd(ttc, rrc, v3, n, r1, seg, tl);}                       
    }                                                                           
                                                                                
void areversc(char* ttc,char* rrc,int q0,int r1,int r2,int seg)                                        
    {int v3, tl, n, u0;                                                         
              v3 = seg*(r1-1);                                                  
              tl=r1; tl<<=31; tl>>=31; r1>>=1;                                  
              for (u0=0; u0<r2; ++u0)                                           
                { n=u0*q0;                                                      
                  reversc(ttc, rrc, v3, n, r1, seg, tl);}                       
    }                                                                           
                                                                                
void breversi(int* ttc,int* rrc,int r0)                                                     
    {int v3, tl, u1, r1;                                                        
         tl=r0<<31; tl>>=31; v3= r0-1; r1= r0>>1;                               
         for (u1=0; u1<r1; ++u1)                                                
              {ttc[u1] = rrc[v3-u1];                                            
               ttc[v3-u1] = rrc[u1];}                                           
              if (tl!=0)                                                        
               ttc[r1] = rrc[r1];                                               
     }                                                                          
                                                                                
void breversm(double* ttc,int* rrc,int r0)                                                     
    {int v3, tl, u1, r1;                                                        
         tl=r0<<31; tl>>=31; v3= r0-1; r1= r0>>1;                               
         for (u1=0; u1<r1; ++u1)                                                
              {ttc[u1] = rrc[v3-u1];                                            
               ttc[v3-u1] = rrc[u1];}                                           
              if (tl!=0)                                                        
               ttc[r1] = rrc[r1];                                               
     }                                                                          
                                                                                
void breversd(double* ttc,double* rrc,int r0)                                                     
    {int v3, tl, u1, r1;                                                        
         tl=r0<<31; tl>>=31; v3= r0-1; r1= r0>>1;                               
         for (u1=0; u1<r1; ++u1)                                                
              {ttc[u1] = rrc[v3-u1];                                            
               ttc[v3-u1] = rrc[u1];}                                           
              if (tl!=0)                                                        
               ttc[r1] = rrc[r1];                                               
     }                                                                          
                                                                                
void breversc(char* ttc,char* rrc,int r0)                                                     
    {int v3, tl, u1, r1;                                                        
         tl=r0<<31; tl>>=31; v3= r0-1; r1= r0>>1;                               
         for (u1=0; u1<r1; ++u1)                                                
              {ttc[u1] = rrc[v3-u1];                                            
               ttc[v3-u1] = rrc[u1];}                                           
              if (tl!=0)                                                        
               ttc[r1] = rrc[r1];                                               
     }                                                                          
//apl3liba.c
//#include "aplc0.h"                                                              
                                                                                
void rotatfxi(int* ttc,int* llc,int* rrc,int notb,int q1,int q2)                                      
    {int w0, w1, w2, u0, v1, qw, qi, sw, si, t;                                 
         w0 = q1;                                                               
         for (v1=0; v1<q2; v1++) {                                              
            if (llc[v1] >= 0) {                                                 
               w1 = (llc[v1])%w0;                                               
               w2 = w0 - w1;                                                    
          } else {                                                              
               w2 = (-llc[v1])%w0;                                              
               w1 = w0 - w2;}                                                   
            for (u0=0; u0<w2; u0++)                                             
               if (notb)                                                        
                  ttc[u0*q2+v1] = rrc[(w1+u0)*q2+v1];                           
               else                                                             
                 {qi= u0*q2+v1; sw= (w1+u0)*q2+v1; si= sw&msk;                  
                  qw= qi>>5; t= rrc[sw>>5];                                     
                  if ( t<<si < 0)                                               
                     ttc[qw]= ttc[qw] |lfb>>(qi&msk);}                          
            for (u0=0; u0<w1; u0++)                                             
               if (notb)                                                        
                  ttc[(w2+u0)*q2+v1] = rrc[u0*q2+v1];                           
               else                                                             
                 {qi= (w2+u0)*q2+v1; sw= u0*q2+v1; si= sw&msk;                  
                  qw= qi>>5; t= rrc[sw>>5];                                     
                  if ( t<<si < 0)                                               
                     ttc[qw]= ttc[qw] |lfb>>(qi&msk);}                          
         }                                                                      
     }                                                                          
                                                                                
void rotatfxd(double* ttc,int* llc,double* rrc,int q1,int q2)                                            
   {int w0, w1, w2, u0, v1, qw, qi, sw, si, t;                                 
         w0 = q1;                                                               
         for (v1=0; v1<q2; v1++) {                                              
            if (llc[v1] >= 0) {                                                 
               w1 = (llc[v1])%w0;                                               
               w2 = w0 - w1;                                                    
          } else {                                                              
               w2 = (-llc[v1])%w0;                                              
               w1 = w0 - w2;}                                                   
            for (u0=0; u0<w2; u0++)                                             
                  ttc[u0*q2+v1] = rrc[(w1+u0)*q2+v1];                           
            for (u0=0; u0<w1; u0++)                                             
                  ttc[(w2+u0)*q2+v1] = rrc[u0*q2+v1];                           
         }                                                                      
     }                                                                          
                                                                                
void rotatfxc(char* ttc,int* llc,char* rrc,int q1,int q2)                                            
    {int w0, w1, w2, u0, v1, qw, qi, sw, si, t;                                 
         w0 = q1;                                                               
         for (v1=0; v1<q2; v1++) {                                              
            if (llc[v1] >= 0) {                                                 
               w1 = (llc[v1])%w0;                                               
               w2 = w0 - w1;                                                    
          } else {                                                              
               w2 = (-llc[v1])%w0;                                              
               w1 = w0 - w2;}                                                   
            for (u0=0; u0<w2; u0++)                                             
                  ttc[u0*q2+v1] = rrc[(w1+u0)*q2+v1];                           
            for (u0=0; u0<w1; u0++)                                             
                  ttc[(w2+u0)*q2+v1] = rrc[u0*q2+v1];                           
         }                                                                      
     }                                                                          
                                                                                
void rotatfxm(double* ttc, int* llc,int* rrc,int q1,int q2)                                            
    {int w0, w1, w2, u0, v1, qw, qi, sw, si, t;                                 
         w0 = q1;                                                               
         for (v1=0; v1<q2; v1++) {                                              
            if (llc[v1] >= 0) {                                                 
               w1 = (llc[v1])%w0;                                               
               w2 = w0 - w1;                                                    
          } else {                                                              
               w2 = (-llc[v1])%w0;                                              
               w1 = w0 - w2;}                                                   
            for (u0=0; u0<w2; u0++)                                             
                  ttc[u0*q2+v1] = rrc[(w1+u0)*q2+v1];                           
            for (u0=0; u0<w1; u0++)                                             
                  ttc[(w2+u0)*q2+v1] = rrc[u0*q2+v1];                           
         }                                                                      
     }                                                                          
//apl3libb.c
//#include "aplc0.h"                                             

void takei(int* ttc,int* rrc,int r0,int rrl,int lopv)
{int r1, v1, r2;                                                              
   r1= min(r0, rrl);                                                            
   if (0<= lopv) {                                                              
      for (v1=0; v1<r1; v1++)                                                   
         ttc[v1]= rrc[v1];                                                      
      for (v1=r1; v1<r0; v1++)                                                  
         ttc[v1]= 0;}                                                           
   else if (rrl<r0) { r2= r0-rrl;                                               
      for (v1=0; v1<r2; v1++)                                                   
         ttc[v1]= 0;                                                            
      for (v1=r2; v1<r0; v1++)                                                  
         ttc[v1]= rrc[v1-r2];}                                                  
      else { r2= rrl-r0;                                                        
      for (v1=0; v1<r0; v1++)                                                   
         ttc[v1]= rrc[v1+r2];}                                                  
   }                                                                            
                                                                                
void taked(double* ttc,double* rrc,int r0,int rrl,int lopv)                                             
  {int r1, v1, r2;                                                              
   r1= min(r0, rrl);                                                            
   if (0<= lopv) {                                                              
      for (v1=0; v1<r1; v1++)                                                   
         ttc[v1]= rrc[v1];                                                      
      for (v1=r1; v1<r0; v1++)                                                  
         ttc[v1]= 0;}                                                           
   else if (rrl<r0) { r2= r0-rrl;                                               
      for (v1=0; v1<r2; v1++)                                                   
         ttc[v1]= 0;                                                            
      for (v1=r2; v1<r0; v1++)                                                  
         ttc[v1]= rrc[v1-r2];}                                                  
      else { r2= rrl-r0;                                                        
      for (v1=0; v1<r0; v1++)                                                   
         ttc[v1]= rrc[v1+r2];}                                                  
   }                                                                            
                                                                                
void takec(char* ttc,char* rrc,int r0,int rrl,int lopv)                                             
  {int r1, v1, r2;                                                              
   r1= min(r0, rrl);                                                            
   if (0<= lopv) {                                                              
      for (v1=0; v1<r1; v1++)                                                   
         ttc[v1]= rrc[v1];                                                      
      for (v1=r1; v1<r0; v1++)                                                  
         ttc[v1]= ' ';}                                                         
   else if (r1<r0) { r2= r0-rrl;                                                
      for (v1=0; v1<r2; v1++)                                                   
         ttc[v1]= ' ';                                                          
      for (v1=r2; v1<r0; v1++)                                                  
         ttc[v1]= rrc[v1-r2];}                                                  
      else { r2= rrl-r0;                                                        
      for (v1=0; v1<r0; v1++)                                                   
         ttc[v1]= rrc[v1+r2];}                                                  
   }                                                                            
                                                                                
void takem(double* ttc,int* rrc,int r0,int rrl,int lopv)                                             
  {int r1, v1, r2;                                                              
   r1= min(r0, rrl);                                                            
   if (0<= lopv) {                                                              
      for (v1=0; v1<r1; v1++)                                                   
         ttc[v1]= rrc[v1];                                                      
      for (v1=r1; v1<r0; v1++)                                                  
         ttc[v1]= 0;}                                                           
   else if (r1<r0) { r2= r0-rrl;                                                
      for (v1=0; v1<r2; v1++)                                                   
         ttc[v1]= 0;                                                            
      for (v1=r2; v1<r0; v1++)                                                  
         ttc[v1]= rrc[v1-r2];}                                                  
      else { r2= rrl-r0;                                                        
      for (v1=0; v1<r0; v1++)                                                   
         ttc[v1]= rrc[v1+r2];}                                                  
   }                                                                            
                                                                                
/*extern int * cad, * tdl, * dl; */                                             
void tak2d(double* p2,int* v19,double* ro2,int ropd0,int ropd1,int s0,int s1,int* cad,int* tdl,int* dl)                    
{ int u0, u1, q0, q1, w0, k0, k1;                                             
    k0= min(ropd0, cad[2]);                                                     
    k1= min(ropd1, cad[3]);                                                     
if (v19[0]>=0) {                                                                
  for (u0=0; u0<k0; u0++)                                                       
  { q0= tdl[0]*u0;                                                              
    w0= dl[0]*u0;                                                               
if (v19[1]>=0) {                                                                
  for (u1=0; u1<k1; u1++)                                                       
 p2[q0+u1]=  ro2[w0+u1];                                                        
  for (u1=ropd1; u1<cad[3]; u1++)                                               
  { q1= tdl[1]*u1;                                                              
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u1=0; u1<cad[3]-ropd1; u1++)                                             
 p2[q0+u1]= 0 ;                                                                 
  for (u1=max(0,cad[3]-ropd1); u1<cad[3]; u1++)                                 
 p2[q0+u1]=  ro2[w0+u1+s1];}                                                    
  }                                                                             
  for (u0=ropd0; u0<cad[2]; u0++)                                               
  { q0= tdl[0]*u0;                                                              
  for (u1=0; u1<cad[3]; u1++)                                                   
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u0=0; u0<cad[2]-ropd0; u0++)                                             
  { q0= tdl[0]*u0;                                                              
  for (u1=0; u1<cad[3]; u1++)                                                   
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  for (u0=max(0,cad[2]-ropd0); u0<cad[2]; u0++)                                 
  { q0= tdl[0]*u0;                                                              
    w0= dl[0]*(u0+s0);                                                          
if (v19[1]>=0) {                                                                
  for (u1=0; u1<k1; u1++)                                                       
 p2[q0+u1]=  ro2[w0+u1];                                                        
  for (u1=ropd1; u1<cad[3]; u1++)                                               
  { q1= tdl[1]*u1;                                                              
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u1=0; u1<cad[3]-ropd1; u1++)                                             
 p2[q0+u1]= 0 ;                                                                 
  for (u1=max(0,cad[3]-ropd1); u1<cad[3]; u1++)                                 
 p2[q0+u1]=  ro2[w0+u1+s1];}                                                    
  }}                                                                            
  }                                                                             
                                                                                
void tak2i(int* p2,int* v19,int* ro2,int ropd0,int ropd1,int s0,int s1,int* cad,int* tdl,int* dl)                    
  { int u0, u1, q0, q1, w0, k0, k1;                                             
    k0= min(ropd0, cad[2]);                                                     
    k1= min(ropd1, cad[3]);                                                     
if (v19[0]>=0) {                                                                
  for (u0=0; u0<k0; u0++)                                                       
  { q0= tdl[0]*u0;                                                              
    w0= dl[0]*u0;                                                               
if (v19[1]>=0) {                                                                
  for (u1=0; u1<k1; u1++)                                                       
 p2[q0+u1]=  ro2[w0+u1];                                                        
  for (u1=ropd1; u1<cad[3]; u1++)                                               
  { q1= tdl[1]*u1;                                                              
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u1=0; u1<cad[3]-ropd1; u1++)                                             
 p2[q0+u1]= 0 ;                                                                 
  for (u1=max(0,cad[3]-ropd1); u1<cad[3]; u1++)                                 
 p2[q0+u1]=  ro2[w0+u1+s1];}                                                    
  }                                                                             
  for (u0=ropd0; u0<cad[2]; u0++)                                               
  { q0= tdl[0]*u0;                                                              
  for (u1=0; u1<cad[3]; u1++)                                                   
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u0=0; u0<cad[2]-ropd0; u0++)                                             
  { q0= tdl[0]*u0;                                                              
  for (u1=0; u1<cad[3]; u1++)                                                   
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  for (u0=max(0,cad[2]-ropd0); u0<cad[2]; u0++)                                 
  { q0= tdl[0]*u0;                                                              
    w0= dl[0]*(u0+s0);                                                          
if (v19[1]>=0) {                                                                
  for (u1=0; u1<k1; u1++)                                                       
 p2[q0+u1]=  ro2[w0+u1];                                                        
  for (u1=ropd1; u1<cad[3]; u1++)                                               
  { q1= tdl[1]*u1;                                                              
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u1=0; u1<cad[3]-ropd1; u1++)                                             
 p2[q0+u1]= 0 ;                                                                 
  for (u1=max(0,cad[3]-ropd1); u1<cad[3]; u1++)                                 
 p2[q0+u1]=  ro2[w0+u1+s1];}                                                    
  }}                                                                            
  }                                                                             
                                                                                
void tak2m(double* p2,int* v19,int* ro2,int ropd0,int ropd1,int s0,int s1,int* cad,int* tdl,int* dl)                    
  { int u0, u1, q0, q1, w0, k0, k1;                                             
    k0= min(ropd0, cad[2]);                                                     
    k1= min(ropd1, cad[3]);                                                     
if (v19[0]>=0) {                                                                
  for (u0=0; u0<k0; u0++)                                                       
  { q0= tdl[0]*u0;                                                              
    w0= dl[0]*u0;                                                               
if (v19[1]>=0) {                                                                
  for (u1=0; u1<k1; u1++)                                                       
 p2[q0+u1]=  ro2[w0+u1];                                                        
  for (u1=ropd1; u1<cad[3]; u1++)                                               
  { q1= tdl[1]*u1;                                                              
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u1=0; u1<cad[3]-ropd1; u1++)                                             
 p2[q0+u1]= 0 ;                                                                 
  for (u1=max(0,cad[3]-ropd1); u1<cad[3]; u1++)                                 
 p2[q0+u1]=  ro2[w0+u1+s1];}                                                    
  }                                                                             
  for (u0=ropd0; u0<cad[2]; u0++)                                               
  { q0= tdl[0]*u0;                                                              
  for (u1=0; u1<cad[3]; u1++)                                                   
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u0=0; u0<cad[2]-ropd0; u0++)                                             
  { q0= tdl[0]*u0;                                                              
  for (u1=0; u1<cad[3]; u1++)                                                   
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  for (u0=max(0,cad[2]-ropd0); u0<cad[2]; u0++)                                 
  { q0= tdl[0]*u0;                                                              
    w0= dl[0]*(u0+s0);                                                          
if (v19[1]>=0) {                                                                
  for (u1=0; u1<k1; u1++)                                                       
 p2[q0+u1]=  ro2[w0+u1];                                                        
  for (u1=ropd1; u1<cad[3]; u1++)                                               
  { q1= tdl[1]*u1;                                                              
 p2[q0+u1]= 0 ;                                                                 
  }                                                                             
  } else {                                                                      
  for (u1=0; u1<cad[3]-ropd1; u1++)                                             
 p2[q0+u1]= 0 ;                                                                 
  for (u1=max(0,cad[3]-ropd1); u1<cad[3]; u1++)                                 
 p2[q0+u1]=  ro2[w0+u1+s1];}                                                    
  }}                                                                            
  }                                                                             
                                                                                
void tak2c(char* p2,int* v19,char* ro2,int ropd0,int ropd1,int s0,int s1,int* cad,int* tdl,int* dl)                    
  { int u0, u1, q0, q1, w0, k0, k1;                                             
    k0= min(ropd0, cad[2]);                                                     
    k1= min(ropd1, cad[3]);                                                     
if (v19[0]>=0) {                                                                
  for (u0=0; u0<k0; u0++)                                                       
  { q0= tdl[0]*u0;                                                              
    w0= dl[0]*u0;                                                               
if (v19[1]>=0) {                                                                
  for (u1=0; u1<k1; u1++)                                                       
 p2[q0+u1]=  ro2[w0+u1];                                                        
  for (u1=ropd1; u1<cad[3]; u1++)                                               
  { q1= tdl[1]*u1;                                                              
 p2[q0+u1]=' ';                                                                 
  }                                                                             
  } else {                                                                      
  for (u1=0; u1<cad[3]-ropd1; u1++)                                             
 p2[q0+u1]=' ';                                                                 
  for (u1=max(0,cad[3]-ropd1); u1<cad[3]; u1++)                                 
 p2[q0+u1]=  ro2[w0+u1+s1];}                                                    
  }                                                                             
  for (u0=ropd0; u0<cad[2]; u0++)                                               
  { q0= tdl[0]*u0;                                                              
  for (u1=0; u1<cad[3]; u1++)                                                   
 p2[q0+u1]=' ';                                                                 
  }                                                                             
  } else {                                                                      
  for (u0=0; u0<cad[2]-ropd0; u0++)                                             
  { q0= tdl[0]*u0;                                                              
  for (u1=0; u1<cad[3]; u1++)                                                   
 p2[q0+u1]=' ';                                                                 
  }                                                                             
  for (u0=max(0,cad[2]-ropd0); u0<cad[2]; u0++)                                 
  { q0= tdl[0]*u0;                                                              
    w0= dl[0]*(u0+s0);                                                          
if (v19[1]>=0) {                                                                
  for (u1=0; u1<k1; u1++)                                                       
 p2[q0+u1]=  ro2[w0+u1];                                                        
  for (u1=ropd1; u1<cad[3]; u1++)                                               
  { q1= tdl[1]*u1;                                                              
 p2[q0+u1]=' ';                                                                 
  }                                                                             
  } else {                                                                      
  for (u1=0; u1<cad[3]-ropd1; u1++)                                             
 p2[q0+u1]=' ';                                                                 
  for (u1=max(0,cad[3]-ropd1); u1<cad[3]; u1++)                                 
 p2[q0+u1]=  ro2[w0+u1+s1];}                                                    
  }}                                                                            
  }                                                                             
//apl3libc.c
//#include "aplc0.h"                                                              
                                                                                
int membsp0b (int lop0,int* rrc,int ropl)                                                  
   { int r1, r2, z, v1;                                                         
     r1= ropl+31>>5; z= 0;                                                      
     if (1 == lop0)                                                             
     for (v1=0; v1<r1; v1++)                                                    
       if (0 != rrc[v1])                                                        
         { z=1; break;}                                                         
       if (0 == lop0)  /* restore back 93/3/11 for pf9b error 7 */              
/*   else {r1= ropl>>5; r2= ropl&msk;                           */              
       {r1= ropl>>5; r2= ropl&msk;                                              
     for (v1=0; v1<r1; v1++)                                                    
       if (0xffffffff != rrc[v1])                                               
         { z=1; break;}                                                         
       if (0 != r2)                                                             
         z= ((0xffffffff>>32-r2)<<32-r2) != rrc[r1];}                           
     return z;                                                                  
    }                                                                           
                                                                                
//void membspc(int* ttc,char* llc,int lopl,char* rrc,int ropl) 0/8
void membspc(long* ttc,char* llc,int lopl,char* rrc,int ropl)                                          
   { int r0, r1, tl, n, v1, v2, i, v32, hx, r2, t, rx, r3, lx0;                 
     int u0, v3;                                                                
     char rox, lox;                                                             
     char  htab[256];                                                           
             r0 = lopl;                                                         
             r1= r0>>5;                                                         
           if (0== ropl)                                                        
             for (v1=0; v1<(r0+31>>5); v1++)                                    
               ttc[v1]=  0;                                                     
           else if ((ropl*lopl<16*32)| ropl==1 | lopl==1)                       
            {for (v2=0; v2<r1; v2++) {                                          
                 t = 0; v32= v2<<5;                                             
               for (v1=0; v1<32; v1++)                                          
                {n= 0;                                                          
                 for (i=0; i<ropl; i++)                                         
                   if (llc[v32+v1]==rrc[i])                                     
                     {n = 1; break;}                                            
                 t = t<<1|n;}                                                   
                   ttc[v2] = t;}                                                
             if (0 != (tl= r0&msk))                                             
               { t = 0;                                                         
               for (v1=0; v1<tl; v1++)                                          
                { n =0;                                                         
                 for (i=0; i<ropl; i++)                                         
                   if (llc[r1*32+v1] == rrc[i])                                 
                     {n = 1; break;}                                            
                   t = t<<1|n;}                                                 
                   ttc[r1] = t<<(32-tl);}}                                      
            else /* hashing */                                                  
             {r0= 255; r1= 119;                                                 
              for (v1=1; v1<256; v1++)                                          
                 htab[v1]= '\n';                                                
              rx= 0;                                                            
              r2= lopl+31>>5;                                                   
              for (v1=0; v1<r2; v1++)                                           
               {if (v1<r2-1) r3= 32; else r3= lopl&msk; t=0; u0= v1<<5;         
                  for (v2=0; v2<r3; v2++)                                       
                { lox=llc[u0+v2]; lx0= (int) lox;                               
seek:             hx= lx0&r0;                                                   
                  if (lox == (int) htab[hx]) goto found;                        
                  if (htab[hx] != '\n') {lx0= lx0+r1; goto seek;}               
                  else /* chech to see whether all rops are in */               
                  for (v3=rx; v3<ropl; v3++)                                    
                { rox=rrc[v3]; lx0= (int) rox; rx++;                            
seek0:            hx= lx0&r0;                                                   
                  if (rox == htab[hx]) continue; /* already in */               
                  if (htab[hx] != '\n') {lx0= lx0+r1; goto seek0;}              
                  else {                                                        
insert:           htab[hx]= rox; /* insert */                                   
                    if (lox == rox) goto found;}}                               
                  continue; /************************/                          
found:            t= t|(lfb>>v2);}                                              
                  ttc[v1]= t;}}                                                 
     }                                                                          
                                                                                
void idxofc(int* ttc,char* llc,int lopl,char* rrc,int ropl,int qdio)                                    
   { int r0, v1, u1, hx, t, rx, r1, r2, lx0, outx, qdm1, v3;                    
     char lox, rox;                                                             
     char  htab[256];                                                           
     int  ihtab[256];                                                           
           if (0== lopl)                                                        
             for (v1=0; v1<ropl; v1++)                                          
               ttc[v1]= qdio;                                                   
           else if ((ropl*lopl<16*32)| ropl==1 | lopl==1)                       
            {for (v1=0; v1<ropl; v1++) {                                        
                 t = qdio;                                                      
               for (u1=0; u1<lopl; u1++)                                        
                 {if (llc[u1]==rrc[v1]) break; t++;}                            
               ttc[v1] = t;}                                                    
            }                                                                   
            else /* hashing */                                                  
             {for (v1=0; v1<256; v1++)                                          
                {htab[v1]= '\n'; ihtab[v1]= 0;}                                 
              r0=255; r1= 119;                                                  
              rx= 0; outx= lopl+qdio; qdm1= qdio-1;                             
              for (v1=0; v1<ropl; v1++)                                         
/*              { rox=rrc[v1]; lx0= (int) rox;    */                            
                { rox=rrc[v1]; hx = (int) rox;                                  
/*seek:           hx= lx0&r0;                     */                            
seek:             if (rox == htab[hx]) goto found;                              
/*                if (htab[hx]!= '\n') {lx0= lx0+r1; goto seek;}   */           
                  if (htab[hx]!= '\n') {hx = (hx+r1)&r0; goto seek;}            
                  else /* chech to see whether all rops are in */               
                  for (v3=rx; v3<lopl; v3++)                                    
/*              { lox=llc[v3]; lx0= (int) lox; rx++;               */           
                { lox=llc[v3]; hx = (int) lox; rx++;                            
/*seek0:            hx= lx0&r0;                                    */           
seek0:            if (lox == htab[hx]) continue; /* already in */               
/*                if (htab[hx] != '\n') {lx0= lx0+r1; goto seek0;} */           
                  if (htab[hx] != '\n') {hx = (hx+r1)&r0; goto seek0;}          
                  else {                                                        
insert:             htab[hx]= lox; ihtab[hx]=rx+qdm1;/* insert */               
                    if (lox == rox) goto found;}}                               
                  ttc[v1]= outx;                                                
                  continue; /************************/                          
found:            ttc[v1]= ihtab[hx];}}                                         
    }                                                                           
//apl3libd.c
/***** integer hashing for membership and index of *****/

//#include <stdlib.h>
//#include "aplc0.h"

int dvz[20]= {31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383,
              32767, 65535, 131071, 262143, 524287, 1048575, 2097151,
              4194303, 8388607, 16777215};

#define Hngi    0x80000001

void * acalloc(int size, int chuck);
/*{void * z;
   if (size<0)
     {printf ("* size negative in allocate. *\n"); exit(1);}
   z= calloc(size, chuck);
   if (z == NULL)
     {printf ("* insufficient memery to allocate. *\n"); exit(1);}
   return z;
} */

//void membspi(int* ttc,int* llc,int lopl,int* rrc,int ropl) 0/8
void membspi(long* ttc,long* llc,int lopl,long* rrc,int ropl)
   { int r0, r1, tl, n, v1, v2, i, v32, rox, lox, hx, r2, t, rx, lx0;
     int u0, r3, v3;
     int * htab;
             r0 = lopl;
             r1= r0>>5;
           if (0== ropl)
             for (v1=0; v1<(r0+31>>5); v1++)
               ttc[v1]=  0;
           else if ((ropl*lopl<32*32)| ropl==1 | lopl==1)
            {for (v2=0; v2<r1; v2++) {
                 t = 0; v32= v2<<5;
               for (v1=0; v1<32; v1++)
                {n= 0;
                 for (i=0; i<ropl; i++)
                   if (llc[v32+v1]==rrc[i])
                     {n = 1; break;}
                 t = t<<1|n;}
                   ttc[v2] = t;}
             if (0 != (tl= r0&msk))
               { t = 0;
               for (v1=0; v1<tl; v1++)
                { n =0;
                 for (i=0; i<ropl; i++)
                   if (llc[r1*32+v1] == rrc[i])
                     {n = 1; break;}
                   t = t<<1|n;}
                   ttc[r1] = t<<(32-tl);}}
            else /* hashing */
/*           {if (ropl<10000) r1= ropl<<2; else r1= ropl<<1;  */
             {r1= ropl<<1;
              for (v1=0; v1<20; v1++)
                if ((r0=dvz[v1])> r1) break;
/*            htab= malloc((r0+1)<<2);                  */
              htab= (int*)acalloc(r0+2, 4);    /* 93/6/1 *///added int*cast*********************
              r1= r0+18;
              htab[0]= Hngi;
              htab[r0+1]= Hngi;
              rx= 0;
              r2= lopl+31>>5;
              for (v1=0; v1<r2; v1++)
            { if (v1<r2-1) r3= 32; else r3= lopl&msk; t=0; u0= v1<<5;
                  for (v2=0; v2<r3; v2++)
                { lox=llc[u0+v2]; lx0= lox;
seek:             hx= lx0&r0;
                  if (lox == htab[hx]) goto found;
              if (lox==0) if (htab[r0+1]==0) goto found; else goto rsd;
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hngi))
                  {lx0= lx0+r1; goto seek;}
                  else /* chech to see whether all rops are in */
rsd:              for (v3=rx; v3<ropl; v3++)
                { rox=rrc[v3]; lx0= rox; rx++;
seek0:            hx= lx0&r0;
                  if (rox == htab[hx]) continue; /* already in */
   if (rox==0) if (htab[r0+1]==0) continue; else {hx=r0+1;goto insert;}
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hngi))
                     {lx0= lx0+r1; goto seek0;}
                  else {
insert:           htab[hx]= rox; /* insert */
                    if (lox == rox) goto found;}}
                  continue; /************************/
found:            t= t|(lfb>>v2);}
                  ttc[v1]= t;}
                  free(htab);}
     }

void idxofi(int* ttc,int* llc,int lopl,int* rrc,int ropl,int qdio)
   { int r0, v1, u1, rox, lox, hx, t, rx, r1, r2, lx0, outx, qdm1, v3;
     int * htab;
           if (0== lopl)
             for (v1=0; v1<ropl; v1++)
               ttc[v1]= qdio;
           else if ((ropl*lopl<32*32)| ropl==1 | lopl==1)
            {for (v1=0; v1<ropl; v1++) {
                 t = qdio;
               for (u1=0; u1<lopl; u1++)
                 {if (llc[u1]==rrc[v1]) break; t++;}
               ttc[v1] = t;}
            }
            else /* hashing */
             {r1= lopl<<1;
              for (v1=0; v1<20; v1++)
                if ((r0= dvz[v1]) > r1) break;
              r2= r0+2;
              htab= (int*)acalloc(r2<<1, 4);//added cast************************
              r1= r0+18;
              htab[0]= Hngi;
              htab[r0+1]= Hngi;
              rx= 0; outx= lopl+qdio; qdm1= qdio-1;
              for (v1=0; v1<ropl; v1++)
                { rox=rrc[v1]; lx0= rox;
seek:             hx= lx0&r0;
                  if (rox == htab[hx]) goto found;
   if (rox==0) if (htab[r0+1]==0) {hx=r0+1; goto found;} else goto rsd;
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hngi))
                  {lx0= lx0+r1; goto seek;}
                  else /* chech to see whether all rops are in */
rsd:              for (v3=rx; v3<lopl; v3++)
                { lox=llc[v3]; lx0= lox; rx++;
seek0:            hx= lx0&r0;
                  if (lox == htab[hx]) continue; /* already in */
   if (lox==0) if (htab[r0+1]==0) continue; else {hx=r0+1;goto insert;}
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hngi))
                     {lx0= lx0+r1; goto seek0;}
                  else {
insert:             htab[hx]= lox; htab[r2+hx]=rx+qdm1;/* insert */
                    if (lox == rox) goto found;}}
                  ttc[v1]= outx;
                  continue; /************************/
found:            ttc[v1]= htab[r2+hx];}
                  free(htab);}
     }
//apl3libe.c
/***** floating point hashing for membership and index of *****/

/*#include <stdlib.h>
#include "aplc0.h"*/

int dvs[20]= {31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383,
              32767, 65535, 131071, 262143, 524287, 1048575, 2097151,
              4194303, 8388607, 16777215};

int sfr[20]= {18, 17, 16, 15, 14, 13, 13, 12, 11, 10, 9, 8,
              7, 6, 5, 4, 3, 2, 1, 0};

double Hflt= 7.662478e+53;

//void * amalloc(int size);
/*{void * z;
   if (size<0)
     {printf ("* size negative in allocate. *\n"); exit(1);}
   z= malloc(size);
   if (z == NULL)
     {printf ("* insufficient memery to allocate. *\n"); exit(1);}
   return z;
}*/
//void * acalloc(int size, int chuck);
/*{void * z;
   if (size<0)
     {printf ("* size negative in allocate. *\n"); exit(1);}
   z= calloc(size, chuck);
   if (z == NULL)
     {printf ("* insufficient memery to allocate. *\n"); exit(1);}
   return z;
}*/

//void membspd(int* ttc,double* llc,int lopl,double* rrc,int ropl) 0/8
void membspd(long* ttc,double* llc,int lopl,double* rrc,int ropl)
   { int r0, r1, tl, n, v1, v2, i, v32, hx, r2, t, rx, r3, lx0, rs, v3;
     int u0;
     int * ip;
     double lox, rox;
     double * htab;
             r0 = lopl;
             r1= r0>>5;
           if (0== ropl)
             for (v1=0; v1<(r0+31>>5); v1++)
               ttc[v1]=  0;
           else if ((ropl*lopl<32*32)| ropl==1 | lopl==1)
            {for (v2=0; v2<r1; v2++) {
                 t = 0; v32= v2<<5;
               for (v1=0; v1<32; v1++)
                {n= 0;
                 for (i=0; i<ropl; i++)
                   if (llc[v32+v1]==rrc[i])
                     {n = 1; break;}
                 t = t<<1|n;}
                   ttc[v2] = t;}
             if (0 != (tl= r0&msk))
               { t = 0;
               for (v1=0; v1<tl; v1++)
                { n =0;
                 for (i=0; i<ropl; i++)
                   if (llc[r1*32+v1] == rrc[i])
                     {n = 1; break;}
                   t = t<<1|n;}
                   ttc[r1] = t<<(32-tl);}}
            else /* hashing */
             {r1= ropl<<1;
              for (v1=0; v1<20; v1++)
                if ((r0= dvs[v1]) > r1) break;
              rs= sfr[v1];
              htab=(double*)acalloc(r0+2, 8);//cast added**************
              r1= r0+18 ;
              htab[0]= Hflt;
              htab[r0+1]= Hflt;
              rx= 0;
              r2= lopl+31>>5;
              for (v1=0; v1<r2; v1++)
              { if (v1<r2-1) r3= 32; else r3= lopl&msk; t=0; u0= v1<<5;
                  for (v2=0; v2<r3; v2++)
                { lox=llc[u0+v2];
                  ip = (int *) &lox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek:             hx= lx0&r0;
                  if (lox == htab[hx]) goto found;
              if (lox==0) if (htab[r0+1]==0) goto found; else goto rsd;
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                  {lx0= lx0+r1; goto seek;}
                  else /* chech to see whether all rops are in */
rsd:              for (v3=rx; v3<ropl; v3++)
                { rox=rrc[v3]; rx++;
                  ip = (int *) &rox; lx0= *ip; lx0>>= rs;
seek0:            hx= lx0&r0;
                  if (rox == htab[hx]) continue; /* already in */
   if (rox==0) if (htab[r0+1]==0) continue; else {hx=r0+1;goto insert;}
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                     {lx0= lx0+r1; goto seek0;}
                  else {
insert:           htab[hx]= rox; /* insert */
                    if (lox == rox) goto found;}}
                  continue; /************************/
found:            t= t|(lfb>>v2);}
                  ttc[v1]= t;}
                  free(htab);}
     }

//void membspm(int* ttc,double* llc,int lopl, int* rrc,int ropl) 0/8
void membspm(long* ttc,double* llc,int lopl, long* rrc,int ropl)
   { int r0, r1, tl, n, v1, v2, i, v32, hx, r2, t, rx, r3, lx0, rs, v3;
     int * ip;
     int u0;
     double lox, rox;
     double * htab;
             r0 = lopl;
             r1= r0>>5;
           if (0== ropl)
             for (v1=0; v1<(r0+31>>5); v1++)
               ttc[v1]=  0;
           else if ((ropl*lopl<32*32)| ropl==1 | lopl==1)
            {for (v2=0; v2<r1; v2++) {
                 t = 0; v32= v2<<5;
               for (v1=0; v1<32; v1++)
                {n= 0;
                 for (i=0; i<ropl; i++)
                   if (llc[v32+v1]==rrc[i])
                     {n = 1; break;}
                 t = t<<1|n;}
                   ttc[v2] = t;}
             if (0 != (tl= r0&msk))
               { t = 0;
               for (v1=0; v1<tl; v1++)
                { n =0;
                 for (i=0; i<ropl; i++)
                   if (llc[r1*32+v1] == rrc[i])
                     {n = 1; break;}
                   t = t<<1|n;}
                   ttc[r1] = t<<(32-tl);}}
            else /* hashing */
             {r1= ropl<<1;
              for (v1=0; v1<20; v1++)
                if ((r0= dvs[v1]) > r1) break;
              rs= sfr[v1];
              htab=(double*)acalloc(r0+2, 8);//*********************8
              r1= r0+18;
              htab[0]= Hflt;
              htab[r0+1]= Hflt;
              rx= 0;
              r2= lopl+31>>5;
              for (v1=0; v1<r2; v1++)
              { if (v1<r2-1) r3= 32; else r3= lopl&msk; t=0; u0= v1<<5;
                  for (v2=0; v2<r3; v2++)
                { lox=llc[u0+v2];
                  ip = (int *) &lox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek:             hx= lx0&r0;
                  if (lox == htab[hx]) goto found;
              if (lox==0) if (htab[r0+1]==0) goto found; else goto rsd;
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                  {lx0= lx0+r1; goto seek;}
                  else /* chech to see whether all rops are in */
rsd:              for (v3=rx; v3<ropl; v3++)
                { rox=rrc[v3]; rx++;
                  ip = (int *) &rox; lx0= *ip; lx0>>= rs;
seek0:            hx= lx0&r0;
                  if (rox == htab[hx]) continue; /* already in */
   if (rox==0) if (htab[r0+1]==0) continue; else {hx=r0+1;goto insert;}
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                     {lx0= lx0+r1; goto seek0;}
                  else {
insert:           htab[hx]= rox; /* insert */
                    if (lox == rox) goto found;}}
                  continue; /************************/
found:            t= t|(lfb>>v2);}
                  ttc[v1]= t;}
                  free(htab);}
     }

//void membspn(int* ttc,int* llc,int lopl,double* rrc,int ropl) 0/8
void membspn(long* ttc,long* llc,int lopl,double* rrc,int ropl)
   { int r0, r1, rs, tl, n, v1, v2, i, v32, hx, r2, t, rx, r3, lx0, v3;
     int * ip;
     int u0;
     double lox, rox;
     double * htab;
             r0 = lopl;
             r1= r0>>5;
           if (0== ropl)
             for (v1=0; v1<(r0+31>>5); v1++)
               ttc[v1]=  0;
           else if ((ropl*lopl<32*32)| ropl==1 | lopl==1)
            {for (v2=0; v2<r1; v2++) {
                 t = 0; v32= v2<<5;
               for (v1=0; v1<32; v1++)
                {n= 0;
                 for (i=0; i<ropl; i++)
                   if (llc[v32+v1]==rrc[i])
                     {n = 1; break;}
                 t = t<<1|n;}
                   ttc[v2] = t;}
             if (0 != (tl= r0&msk))
               { t = 0;
               for (v1=0; v1<tl; v1++)
                { n =0;
                 for (i=0; i<ropl; i++)
                   if (llc[r1*32+v1] == rrc[i])
                     {n = 1; break;}
                   t = t<<1|n;}
                   ttc[r1] = t<<(32-tl);}}
            else /* hashing */
             {r1= ropl<<1;
              for (v1=0; v1<20; v1++)
                if ((r0= dvs[v1]) > r1) break;
              rs= sfr[v1];
              htab=(double*)acalloc(r0+2, 8);//***********************8
              r1= r0+18 ;
              htab[0]= Hflt;
              htab[r0+1]= Hflt;
              rx= 0;
              r2= lopl+31>>5;
              for (v1=0; v1<r2; v1++)
              { if (v1<r2-1) r3= 32; else r3= lopl&msk; t=0; u0= v1<<5;
                  for (v2=0; v2<r3; v2++)
                { lox=llc[u0+v2];
                  ip = (int *) &lox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek:             hx= lx0&r0;
                  if (lox == htab[hx]) goto found;
              if (lox==0) if (htab[r0+1]==0) goto found; else goto rsd;
/*                if (!((htab[hx]==0)∫∫(hx==0 && htab[0]==Hflt))     */
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                  {lx0= lx0+r1; goto seek;}
                  else /* chech to see whether all rops are in */
rsd:              for (v3=rx; v3<ropl; v3++)
                { rox=rrc[v3]; rx++;
                  ip = (int *) &rox; /* ip++; */ lx0= *ip; lx0>>= rs;
seek0:            hx= lx0&r0;
                  if (rox == htab[hx]) continue; /* already in */
   if (rox==0) if (htab[r0+1]==0) continue; else {hx=r0+1;goto insert;}
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                     {lx0= lx0+r1; goto seek0;}
                  else {
insert:           htab[hx]= rox; /* insert */
                    if (lox == rox) goto found;}}
                  continue; /************************/
found:            t= t|(lfb>>v2);}
                  ttc[v1]= t;}
                  free(htab);}
     }

void idxofd(int* ttc,double* llc,int lopl,double* rrc,int ropl,int qdio)
   { int r0, v1, u1, hx, t, rx, r1, r2, rs, lx0, outx, qdm1, v3;
     double rox, lox;
     int * ihtab, * ip;
     double * htab;
           if (0== lopl)
             for (v1=0; v1<ropl; v1++)
               ttc[v1]= qdio;
           else if ((ropl*lopl<16*32)| ropl==1 | lopl==1)
            {for (v1=0; v1<ropl; v1++) {
                 t = qdio;
               for (u1=0; u1<lopl; u1++)
                 {if (llc[u1]==rrc[v1]) break; t++;}
               ttc[v1] = t;}
            }
            else /* hashing */
             {r1= lopl<<1;
              for (v1=0; v1<20; v1++)
                if ((r0= dvs[v1]) > r1) break;
              rs= sfr[v1];
/*            r2= (r0+1)<<1;                         */
              r2=  r0+2;
/*            htab= calloc(r2<<1, 8);
              ihtab= malloc(r2<<3);                  */
              htab=(double*)acalloc(r2, 8);//****************************
              ihtab=(int*)amalloc(r2<<2);//**********************
              r1= r0+18 ;
              htab[0]= Hflt;
              htab[r0+1]= Hflt;
              rx= 0; outx= lopl+qdio; qdm1= qdio-1;
              for (v1=0; v1<ropl; v1++)
                { rox=rrc[v1]; /* lx0= rox; */
                  ip = (int *) &rox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek:             hx= lx0&r0;
                  if (rox == htab[hx]) goto found;
   if (rox==0) if (htab[r0+1]==0) {hx=r0+1; goto found;} else goto rsd;
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
/*                if (htab[hx]!=0 && hx!=0 ∫∫ hx==0 && htab[0]!=Hflt)*/
                  {lx0= lx0+r1; goto seek;}
                  else /* chech to see whether all rops are in */
rsd:              for (v3=rx; v3<lopl; v3++)
                { lox=llc[v3];/* lx0= lox;*/ rx++;
                  ip = (int *) &lox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek0:            hx= lx0&r0;
                  if (lox == htab[hx]) continue; /* already in */
   if (lox==0) if (htab[r0+1]==0) continue; else {hx=r0+1;goto insert;}
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                     {lx0= lx0+r1; goto seek0;}
                  else {
/*insert:             htab[hx]= lox; htab[r2+hx]=rx+qdm1;   insert */
insert:             htab[hx]= lox; ihtab[hx]=rx+qdm1;/* insert */
                    if (lox == rox) goto found;}}
                  ttc[v1]= outx;
                  continue; /************************/
found:            ttc[v1]= ihtab[hx];}
                  free(htab); free(ihtab);}
     }

void idxofm(int* ttc,double* llc,int lopl,int* rrc,int ropl,int qdio)
   { int r0, v1, u1, hx, t, rx, r1, r2, rs, lx0, outx, qdm1, v3;
     double rox, lox;
     int * ihtab, * ip;
     double * htab;
           if (0== lopl)
             for (v1=0; v1<ropl; v1++)
               ttc[v1]= qdio;
           else if ((ropl*lopl<16*32)| ropl==1 | lopl==1)
            {for (v1=0; v1<ropl; v1++) {
                 t = qdio;
               for (u1=0; u1<lopl; u1++)
                 {if (llc[u1]==rrc[v1]) break; t++;}
               ttc[v1] = t;}
            }
            else /* hashing */
             {r1= lopl<<1;
              for (v1=0; v1<20; v1++)
                if ((r0= dvs[v1]) > r1) break;
              rs= sfr[v1];
              r2= r0+2;
              htab=(double*)acalloc(r2, 8);//////////////////////////////////
              ihtab=(int*)amalloc(r2<<2);////////////////////////
              r1= r0+18;
              htab[0]= Hflt;
              htab[r0+1]= Hflt;
              rx= 0; outx= lopl+qdio; qdm1= qdio-1;
              for (v1=0; v1<ropl; v1++)
                { rox=rrc[v1]; /* lx0= rox; */
                  ip = (int *) &rox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek:             hx= lx0&r0;
                  if (rox == htab[hx]) goto found;
   if (rox==0) if (htab[r0+1]==0) {hx=r0+1; goto found;} else goto rsd;
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                  {lx0= lx0+r1; goto seek;}
                  else /* chech to see whether all rops are in */
rsd:              for (v3=rx; v3<lopl; v3++)
                { lox=llc[v3];/* lx0= lox;*/ rx++;
                  ip = (int *) &lox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek0:            hx= lx0&r0;
                  if (lox == htab[hx]) continue; /* already in */
   if (lox==0) if (htab[r0+1]==0) continue; else {hx=r0+1;goto insert;}
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                     {lx0= lx0+r1; goto seek0;}
                  else {
/*insert:             htab[hx]= lox; htab[r2+hx]=rx+qdm1;   insert */
insert:             htab[hx]= lox; ihtab[hx]=rx+qdm1;/* insert */
                    if (lox == rox) goto found;}}
                  ttc[v1]= outx;
                  continue; /************************/
found:            ttc[v1]= ihtab[hx];}
                  free(htab); free(ihtab);}
     }

void idxofn(int* ttc,int* llc,int lopl,double* rrc,int ropl,int qdio)
   { int r0, v1, u1, hx, t, rx, r1, r2, rs, lx0, outx, qdm1, v3;
     double rox, lox;
     int * ihtab, * ip;
     double * htab;
           if (0== lopl)
             for (v1=0; v1<ropl; v1++)
               ttc[v1]= qdio;
           else if ((ropl*lopl<16*32)| ropl==1 | lopl==1)
            {for (v1=0; v1<ropl; v1++) {
                 t = qdio;
               for (u1=0; u1<lopl; u1++)
                 {if (llc[u1]==rrc[v1]) break; t++;}
               ttc[v1] = t;}
            }
            else /* hashing */
             {r1= lopl<<1;
              for (v1=0; v1<20; v1++)
                if ((r0= dvs[v1]) > r1) break;
              rs= sfr[v1];
              r2= r0+2;
              htab=(double*)acalloc(r2, 8);/////////////////////////
              ihtab=(int*)amalloc(r2<<2);///////////////////
              r1= r0+18 ;
              htab[0]= Hflt;
              htab[r0+1]= Hflt;
              rx= 0; outx= lopl+qdio; qdm1= qdio-1;
              for (v1=0; v1<ropl; v1++)
                { rox=rrc[v1]; /* lx0= rox; */
                  ip = (int *) &rox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek:             hx= lx0&r0;
                  if (rox == htab[hx]) goto found;
   if (rox==0) if (htab[r0+1]==0) {hx=r0+1; goto found;} else goto rsd;
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                  {lx0= lx0+r1; goto seek;}
                  else /* chech to see whether all rops are in */
rsd:              for (v3=rx; v3<lopl; v3++)
                { lox=llc[v3];/* lx0= lox;*/ rx++;
                  ip = (int *) &lox;/* ip++;*/ lx0= *ip; lx0>>= rs;
seek0:            hx= lx0&r0;
                  if (lox == htab[hx]) continue; /* already in */
   if (lox==0) if (htab[r0+1]==0) continue; else {hx=r0+1;goto insert;}
                  if (htab[hx]!=0 && (hx!=0 || htab[0]!=Hflt))
                     {lx0= lx0+r1; goto seek0;}
                  else {
/*insert:             htab[hx]= lox; htab[r2+hx]=rx+qdm1;   insert */
insert:             htab[hx]= lox; ihtab[hx]=rx+qdm1;/* insert */
                    if (lox == rox) goto found;}}
                  ttc[v1]= outx;
                  continue; /************************/
found:            ttc[v1]= ihtab[hx];}
                  free(htab); free(ihtab);}
     }

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
int compeqI(int* v,int* Indx,int qdio,int i,int j)                                                
{                                                                               
   if (v[Indx[i]-qdio] == v[Indx[j]-qdio]) return 1;                            
      else return 0;                                                            
}                                                                               
                                                                                
/*                                                                              
 * compare values, return 1 if equal, 0 otherwise; for double type              
 * N. Shi.. 12/16/90.                                                           
 */                                                                             
int compeqD(double* v,int* Indx,int qdio,int i,int j)                                                
{                                                                               
   if (v[Indx[i]-qdio] == v[Indx[j]-qdio]) return 1;                            
      else return 0;                                                            
}                                                                               
                                                                                
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
int qcompIndx(const void *i,const void *j)
{
	if (*(long*)i < *(long*)j) return -1;
	else if (*(long*)i == *(long*)j) return 0;
	else return 1;
}
                                                                                
/*                                                                              
 * compare for grade up, for integer array v                                    
 * N. Shi.. 12/15/90.                                                           
 */                                                                             
int compupI(int* v, int i,int j,int size)                                                      
{                                                                               
   if (v[i] <= v[j]) return 1;                                                  
      else return 0;                                                            
}                                                                               
                                                                                
/*                                                                              
 * compare for grade up, for double array v                                     
 * N. Shi.. 12/15/90.                                                           
 */                                                                             
int compupD(double* v,int i,int j,int size)                                                      
{                                                                               
   if (v[i] <= v[j]) return 1;                                                  
      else return 0;                                                            
}                                                                               
                                                                                
/*                                                                              
 * compare for grade up, for char array v                                       
 * N. Shi.. 12/15/90.                                                           
 */                                                                             
int compupC(char* v,int i,int j,int size)                                                      
{                                                                               
   if (v[i] <= v[j]) return 1;                                                  
      else return 0;                                                            
}                                                                               
                                                                                
/*                                                                              
 * compare for grade down, for integer array v                                  
 * N. Shi.. 12/16/90.                                                           
 */                                                                             
int compdnI(int* v,int i,int j,int size)                                                      
{                                                                               
   if (v[i] > v[j]) return 1;                                                   
      else return 0;                                                            
}                                                                               
                                                                                
/*                                                                              
 * compare for grade down, for double array v                                   
 */                                                                             
int compdnD(double* v,int i,int j,int size)                                                      
{                                                                               
   if (v[i] > v[j]) return 1;                                                   
      else return 0;                                                            
}                                                                               
                                                                                
/*                                                                              
 * compare for grade down, for char array v                                     
 * N. Shi.. 12/16/90.                                                           
 */                                                                             
int compdnC(char* v,int i,int j,int size)                                                      
{                                                                               
   if (v[i] > v[j]) return 1;                                            
      else return 0;                                                            
}                                                                               
                                                                                
                                                                                
                                                                                
/*                                                                              
 * compare and swap if needed, for integer array v                              
 * For grade up for integer.                                                    
 * N. Shi.. 12/15/90.                                                           
 */                                                                             
void swap(void* v,int* Indx,int i,int j,int size)                                                  
{                                                                               
   char buff[8], *ptr ;                                                         
   int  temp;                                                                   
   ptr = (char *) v;  /* cast */                                                
   memcpy(buff, ptr+(size*i), size);                                            
   memcpy(ptr+(size*i), ptr+(size*j), size);                                    
   memcpy(ptr+(size*j), buff, size);                                            
   temp = Indx[i];                                                              
   Indx[i] = Indx[j];                                                           
   Indx[j] = temp;                                                              
}                                                                               
                                                                                
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
int TotalBytes(int iType,int n)                                                        
{                                                                               
   int nbytes;                                                                  
   switch (iType) {                                                             
   case BOOLTYPE:                                                               
     /* Boolean */                                                              
     nbytes = (n+7)>>3;                                                         
     break;                                                                     
   case INTTYPE:                                                                
     /* Integer */                                                              
     nbytes = n * sizeof(int);                                                  
     break;                                                                     
   case DOUBLETYPE:                                                             
     /* double */                                                               
     nbytes = n * sizeof(double);                                               
     break;                                                                     
   case CHARTYPE:                                                               
     /* char */                                                                 
     nbytes = n;                                                                
     break;                                                                     
   }                                                                            
   return nbytes;                                                               
}                                                                               
                                                                                
/* sort array v in ascending order by N. Shi 91/1/3 */                          
/* itemp is the indices, will be rearranged accoding to v */                    
void sortI(int n,int* v,int* itemp)                                                           
{  int l,j,ir,i;                                                                
   int iidx, *idx;                                                              
   int rra, *ra;                                                                
                                                                                
   ra= v-1;                                                                     
   idx= itemp-1;                                                                
   l= (n>>1) +1;                                                                
   ir=n;                                                                        
   for (;;) {                                                                   
      if (l>1) {                                                                
         rra= ra[--l];                                                          
         iidx= idx[l];}                                                         
      else {                                                                    
         rra= ra[ir];                                                           
         iidx= idx[ir];                                                         
         ra[ir]= ra[1];                                                         
         idx[ir]= idx[1];                                                       
         if (--ir == 1) {                                                       
         ra[1]= rra;                                                            
         idx[1]= iidx;                                                          
         return;}}                                                              
    i= l;                                                                       
    j= l<<1;                                                                    
    while (j <= ir) {                                                           
       if (j<ir && ra[j]<ra[j+1]) ++j;                                          
       if (rra < ra[j]) {                                                       
         ra[i]= ra[j];                                                          
         idx[i]= idx[j];                                                        
         j+= (i=j);}                                                            
       else j= ir+1;}                                                           
    ra[i]= rra;                                                                 
    idx[i]= iidx;}}                                                             
                                                                                
/* sort array v in decending order by N. Shi 91/1/3 */                          
/* itemp is the indices, will be rearranged accoding to v */                    
void sortD(int n,double* v,int* itemp)                                                           
{  int l,j,ir,i;                                                                
   int iidx, *idx;                                                              
   double rra, *ra;                                                             
                                                                                
   ra= v-1;                                                                     
   idx= itemp-1;                                                                
   l= (n>>1) +1;                                                                
   ir=n;                                                                        
   for (;;) {                                                                   
      if (l>1) {                                                                
         rra= ra[--l];                                                          
         iidx= idx[l];}                                                         
      else {                                                                    
         rra= ra[ir];                                                           
         iidx= idx[ir];                                                         
         ra[ir]= ra[1];                                                         
         idx[ir]= idx[1];                                                       
         if (--ir == 1) {                                                       
         ra[1]= rra;                                                            
         idx[1]= iidx;                                                          
         return;}}                                                              
    i= l;                                                                       
    j= l<<1;                                                                    
    while (j <= ir) {                                                           
       if (j<ir && ra[j]<ra[j+1]) ++j;                                          
       if (rra < ra[j]) {                                                       
         ra[i]= ra[j];                                                          
         idx[i]= idx[j];                                                        
         j+= (i=j);}                                                            
       else j= ir+1;}                                                           
    ra[i]= rra;                                                                 
    idx[i]= iidx;}}                                                             
                                                                                
/*                                                                              
 * grade                                                                        
 * N. Shi. 12/15/90                                                             
 * v = data array, iType = data type                                            
 * Indx = output indices for grade up or grade down.                            
 * qdio = quad-IO,  n = the number of data points.                              
 * option = GRADEUP or GRADEDOWN             /* Target array must have been allocated */                                   

//Paul 10/99
void a_grade(void* v,int iType,int* Indx,int qdio,int n,int option)
{																		
   void *buff;															
   int	nbytes, i, nrep, i0, iidx;	/* 91/1/3 */						
   int	size;	/* data element size in bytes */						
/* int (*comp)();					   91/1/3 */						
//	 int (*compeq)(int *,int *,int,int,int); /* return 1 if equal */changing to switch
   double *ptrD;															
   int	  *ptrI;															
																			
   if(n == 1)  { Indx[0] = qdio;  return; }  /* 91/7/11J, for a single		
												 element. */				
   nbytes = TotalBytes(iType, n);											
   if (!(buff = (void *) malloc(nbytes))) { 								
	  printf("malloc failed in grade\n");	  exit(1);						
	  } 																	
   memcpy(buff, v, nbytes); /* make a temporary copy */ 					
   for (i=0; i<n; i++) Indx[i] = qdio + i;	/* set up indices */			
   switch (iType) { 														
   case BOOLTYPE:															
	  printf("Boolean grade not implemented yet\n");						
	  break; /* exit(0);					  91/1/3 */ 					
   case INTTYPE:															
/*	  comp = (option==GRADEUP)? compupI: compdnI;	 */ 					
	  ptrI = (int *) buff;													
	  sortI(n, ptrI, Indx);  /* sort in ascending order */					
//		compeq = compeqI;												 *****		   
/*	  size = sizeof(int);							 */ 						
	  break;																	
   case DOUBLETYPE: 															
/*	  comp = (option==GRADEUP)? compupD: compdnD;	 */ 						
	  ptrD = (double *) buff;													
	  sortD(n, ptrD, Indx);  /* sort in ascending order */						
//		compeq = compeqD;										  *******
/*	  size = sizeof(double);						 */ 						
	  break;																	
   case CHARTYPE:																
	  printf("Character type grade not defined\n"); 							
	  exit(1);																	
	  break;																	
   default:;																	
   }  /* endswitch */															
/* order(buff, Indx, 0, (n-1), size, comp); */									
/* free(buff);								*/									
																				
if (option == -1) { /*GRADEDOWN) { */											
   /* grade down, we switch the indices only */ 								
   i0 = n/2;																	
/* for (i=0; i<=i0; i++) { *91/6/17 Ju, changed the bound */					
   for (i=0; i<i0; i++) {														
   iidx = Indx[i];															   
   Indx[i] = Indx[n-1-i];														
   Indx[n-1-i] = iidx;	 }} 													
																				
																				
#ifdef TEST 																	
/* printf("Indx inside grade function\n"); */									
   printf("Indicse\n"); 														
   for (i=0; i<n; i++) printf("%4d", Indx[i]);									
   printf("\n");																
																				
   printf("Data array rearranged\n");											
   ptrI = (int *) v;															
   for (i=0; i<n; i++) printf("%4d", ptrI[Indx[i]-qdio]);						
   printf("\n");																
#endif																			
																				
   free(buff);																	
																				
   i = 0;
   switch (iType)
   {//*****************taking out function pointer
   case BOOLTYPE:
   case INTTYPE:
	   do 
	   {
			nrep = 0;  i0 = i;  i++;
			/* while ((*compeq)(v, Indx, qdio, i0, i) && (i<n)) Ju, 8/1/91
			if i = n, don't do compeq. */
			while ((i < n) && compeqI((int*)v, Indx, qdio, i0, i))						
			{
				i++; nrep++;
			}
		   if (nrep) qsort(Indx+i0, nrep+1, sizeof(int), *qcompIndx);//back in after function changed paul 99/7/28
	   } while (i<n);
	   break;
   case DOUBLETYPE:
	   do { 																		
		   nrep = 0;  i0 = i;  i++; 												
		   /* while ((*compeq)(v, Indx, qdio, i0, i) && (i<n)) Ju, 8/1/91				
		   if i = n, don't do compeq. */												
		   while ((i < n) && compeqD((double*)v, Indx, qdio, i0, i))						
		   { i++; nrep++;}														
		   if (nrep) qsort(Indx+i0, nrep+1, sizeof(int), *qcompIndx);
	   } while (i<n);																
	   break;
   case CHARTYPE:
	   break;
   } 
	//	 do {																		
	//	   nrep = 0;  i0 = i;  i++; 												
	//	   /* while ((*compeq)(v, Indx, qdio, i0, i) && (i<n)) Ju, 8/1/91				
	//	   if i = n, don't do compeq. */												
	//	   while ((i < n) && (*compeq)(v, Indx, qdio, i0, i))						
	//	   { i++; nrep++;}														
	//	   if (nrep) qsort(Indx+i0, nrep+1, sizeof(int), qcompIndx);				
	 //  } while (i<n);took out functio n pointers
/********************** 93/3/25 ************									
#ifdef TEST 																	
   printf("Indx inside grade function\n");										
   printf("Indicse\n"); 														
   for (i=0; i<n; i++) printf("%4d", Indx[i]);									
   printf("\n");																
#endif																			
********************************************/									
}


