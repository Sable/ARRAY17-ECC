/*
 * This program is translated from rprime.esf
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

#define assign(p,v,g) {p->value=v; p->length=g;}
int v100[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

typedef struct _vector{
    int *value;
    int length;
}vector;

void errorMessage(char* msg){
    fprintf(stderr, msg);
    exit(1);
}

char* alloc(int m){
    char* p = malloc(m);
    if(p == NULL){
        errorMessage("Insufficient memory\n");
    }
    return p;
}

int* allocInt(int m){
    return (int*)alloc(m * sizeof(int));
}

int* allocBool(int m, int isOne){
    int size = (1 + (m >> 5)) << 5;
    char *res = alloc(size);
    if(isOne)
        memset(res, -1, size);
    else
        memset(res, 0, size);
    return (int*)res;
}

void tryFree(void* t){
    if(t != NULL){
        free(t);
    }
}

void printVector(vector *p){
    if(p != NULL){
        for(int i=0; i<p->length; i++){
            if(i != 0) printf(" ");
            printf("%d", p->value[i]);
        }
        printf("\n");
        printf("[%d found]\n", p->length);
    }
    else{
        errorMessage("p is a NULL vector\n");
    }
}

void printBit(int x, int n){
    int i;
    if(n < 0) n = 32;
    printf("===\n");
    for(i=0; i<n; i++){
        printf("%3d", i+1);
    }
    printf("\n");
    for(i=0; i<n; i++){
        printf("%3d", (x<0));
        x <<= 1;
    }
    printf("\n");
    printf("===\n");
}

vector* rprime(int n){
    int count,size,pl,total,len;
    int *resP, *tempInt, *first100;
    int *tempBool, *b;
    int blockTotal, blockRemain, blockAll;
    int i,j,k,t,newLen;
    vector *p;
    tempBool = NULL;
    tempInt  = NULL;
    /* new p */
    p = (vector*)alloc(sizeof(vector));
    len = sizeof(v100)/sizeof(int);
    first100 = allocInt(len);
    for(i=0; i<len; i++)
        first100[i] = v100[i];
    assign(p, first100, len);
    if(!(n <= 100)) goto L0;
    /* boolean selection */
    tempBool = allocBool(p->length, 0);
    /* initialize tempBool */
    blockTotal = p->length >> 5;
    blockRemain= p->length - (blockTotal << 5);
    blockAll   = blockTotal + 1;
    for(i=0; i<blockTotal; i++){
        for(j=0; j<32; j++){
            t = n >= p->value[(i<<5)+j];
            tempBool[i] = (tempBool[i] << 1) & (t > 0 ? 1 : 0);
        }
    }
    for(i=0; i<blockRemain; i++){
        t = n >= p->value[(blockTotal<<5)+i];
        tempBool[blockTotal] = (tempBool[blockTotal] << 1) | (t > 0 ? 1 : 0);
        // printf("k = %d, index = %d, tempBool[0]=%d\n", k, (blockTotal<<5)+i, tempBool[0]);
    }
    if(blockRemain > 0){
        tempBool[blockTotal] <<= (32 - blockRemain);
    }
    size = 0;
    /* bit */
    for(i=0; i<blockTotal; i++){
        t = tempBool[i];
        for(j=0; j<32; j++){
            size += (t<0);
            t <<= 1;
        }
    }
    t = tempBool[blockTotal];
    for(i=0; i<blockRemain; i++){
        size += (t<0);
        t <<= 1;
    }
    resP  = allocInt(size);
    count = 0;
    /* bit */
    for(i=0; i<blockTotal; i++){
        t = tempBool[i];
        for(j=0; j<32; j++){
            if(t<0)
                resP[count++] = p->value[(i<<5)+j];
            t <<= 1;
        }
    }
    t = tempBool[blockTotal];
    for(i=0; i<blockRemain; i++){
        if(t<0)
            resP[count++] = p->value[(blockTotal<<5)+i];
        t<<=1;
    }
    assign(p, resP, size);
    goto L1;
L0:
    p  = rprime(floor(sqrt(n)));
    pl = p->length;
    b  = allocBool(n, 0);
    k = 0;  /* rename i to k */
L2:
    len        = p->value[k];
    tempBool   = allocBool(n, 0);
    blockTotal = n >> 5;
    blockRemain= n - (blockTotal << 5);
    blockAll   = blockTotal + 1;
    // wrapmove
    for(i=0, j=0; i<blockAll;){
        if(j>0) tempBool[i] = 1;
        newLen = j + len;
        if(newLen < 32){
            for(; j<32; j+=len){
                tempBool[i] = (tempBool[i] << len) | 1;
            }
            if(j>32){
                tempBool[i] <<= len - (j - 32);
            }
            j -= 32;
            i++;
        }
        else {
            //printf("j = %d, len = %d, newLen = %d\n", j,len,newLen);
            tempBool[i] <<= 32 - j; //shift before move to next line
            i += newLen / 32;
            j  = newLen % 32;
        }
    }
    if(i==blockAll){
        t = tempBool[blockTotal];
        int cleanBit = 0;
        for(i=0; i<blockRemain;i++)
            cleanBit = (cleanBit<<1) | 1;
        cleanBit <<= 32-blockRemain;
        tempBool[blockTotal] &= cleanBit;
    }
    for(i=0; i<blockAll;i++){
        b[i] = b[i] | tempBool[i];
    }
    //printBit(b[blockTotal], -1);
    if(pl > ++k) {
        tryFree(tempBool);
        goto L2;
    }
    /*printf("output:\n");
    for(i=0; i<blockAll; i++){
        printf("i = %d\n", i);
        printBit(b[i], -1);
    }*/
    size    = 0;
    for(i=0; i<blockTotal; i++){
        t = b[i];
        for(j=0; j<32; j++){
            if(t>=0) size++;
            t <<= 1;
        }
    }
    t = b[blockTotal];
    for(i=0; i<blockRemain; i++){
        if(t>=0) size++;
        t <<= 1;
    }
    tempInt = allocInt(size);
    count   = 0;
    for(i=0; i<blockTotal; i++){
        t = b[i];
        for(j=0; j<32; j++){
            if(t>=0)
                tempInt[count++]=(i<<5)+j+1;
            t <<= 1;
        }
    }
    t = b[blockTotal];
    for(i=0; i<blockRemain; i++){
        if(t>=0)
            tempInt[count++]=(blockTotal<<5)+i+1;
        t <<= 1;
    }
    count   = 0;
    total   = p->length + size - 1;
    resP    = allocInt(total);
    for(i=0; i<p->length; i++)
        resP[i] = p->value[i];
    for(i=1; i<size; i++)
        resP[i - 1 + p->length] = tempInt[i];
    free(p->value);
    assign(p, resP, total);
L1:
    tryFree(tempBool);
    tryFree(tempInt);
    tryFree(first100);
    return p;
}

/*
 * Get millisecond from timeval
 */
double getTime(struct timeval tv1, struct timeval tv2){
    return ((double) (tv2.tv_usec - tv1.tv_usec) / 1000 +
            (double) (tv2.tv_sec - tv1.tv_sec) * 1000);
}

int main(int argc, char**  argv){
    int n = 0;
    int isPrint = 0;
    struct timeval tv1, tv2;
    if(argc == 2 || argc == 3){
        n = atoi(argv[1]);
        if(argc == 3){
            isPrint = atoi(argv[2]) == 1;
        }
    }
    else {
        errorMessage("Usage: ./rprime n or ./rprime n 1\n");
    }
    gettimeofday(&tv1, NULL);  // time_start
    vector* p = rprime(n);
    gettimeofday(&tv2, NULL);  // time_end
    printf("The elapsed time (ms): %lf\n", getTime(tv1,tv2));
    if(isPrint) printVector(p);
    return 0;
}

