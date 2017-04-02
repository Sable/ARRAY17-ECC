
#ifndef __ELI_MACROS__
#define __ELI_MACROS__
// from INCHEAPP
#define INCHEAPP3(v0, inchptyp) do{ cad[1]=r0; if (new_v=r0>v0.maxl) {v0.maxl=r0; inchptyp;v0.valp= &heap[r15];} v0.reall=r0; }while(0)
//#define INCHEAPPH(v0, inchptyp, ptyp, pstyp) do{ cad[1]=r0; if (new_v=r0>v0.maxl) {v0.maxl=r0; inchptyp;cad0= &heap[r15];} else cad0= v0.valp; pstyp=(pstyp *)cad0;  }
#define INCHEAPPH(v0, inchptyp, pstr) do{ cad[1]=r0; if (new_v=r0>v0.maxl) {v0.maxl=r0; inchptyp;cad0= &heap[r15];} else cad0= v0.valp; pstr;  } while(0)

// from GENLE , default "\n"
// #define LEMSG(n,i) do{printf(" length error at %d line %d.\n",n,i);  exit(99);}while(0)
#define LEMSG(n,i) do{printf(" length error at %d line %d. (in %s line %d)\n",n,i,__FILE__,__LINE__);  exit(99);}while(0)
#define IDMSG(n,i) do{printf(" index error at %d line %d. (in %s line %d)\n",n,i,__FILE__,__LINE__); exit(99);}while(0)

// test, can del
// void BlkSchls ();
// void CNDF     (double* p47);

void print(double* p) { int i=0; for(;i<4;i++) printf("%lf ",p[i]); printf("\n---debug---\n"); }
void writedata(double* p, int len) { int i=0; FILE* pr;
 if((pr=fopen("1M.out","w"))!=NULL){ fprintf(pr,"%d\n",len); for(;i<len;i++) fprintf(pr,"%.18lf\n",p[i]); fclose(pr);}
 else printf("write error"); }

#endif
