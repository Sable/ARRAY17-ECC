/*
 * This program is translated from rprime.esf
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define assign(p,v,g) {p->value=v; p->length=g;}
int v100[]={2,3,4,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

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

bool* allocBool(int m){
    return (bool*)alloc(m * sizeof(bool));
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


vector* rprime(int n){
    int i,k,count,size,pl,total,len;
    int *resP, *tempInt, *first100;
    bool *tempBool, *b;
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
    tempBool = allocBool(p->length);
    for(i=0;i<p->length;i++){
        tempBool[i] = n >= p->value[i];
    }
    size = 0;
    for(i=0;i<p->length;i++){
        size += tempBool[i];
    }
    resP  = allocInt(size);
    count = 0;
    for(i=0;i<p->length;i++){
        if(tempBool[i])
            resP[count++] = p->value[i];
    }
    assign(p, resP, size);
    goto L1;
L0:
    p  = rprime(floor(sqrt(n)));
    pl = p->length;
    b  = allocBool(n);
    for(i=0; i<n; i++){
        b[i] = false;
    }
    k = 0;  /* rename i to k */
L2:
    len      = p->value[k];
    tempBool = allocBool(n);
    for(i=0; i<n; i++){
        tempBool[i] = ((i+1)%len) == 0? true : false;
    }
    for(i=0; i<n; i++)
        b[i] = b[i] || tempBool[i];
    if(pl > ++k) {
        tryFree(tempBool);
        goto L2;
    }
    size = 0;
    for(i=0; i<n; i++){
        if(!b[i]) size++;
    }
    tempInt = allocInt(size);
    count   = 0;
    for(i=0; i<n; i++){
        if(!b[i]) tempInt[count++] = i+1;
    }
    total = p->length + size - 1;
    resP  = allocInt(total);
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

int main(int argc, char**  argv){
    if(argc != 2){
        errorMessage("Usage: ./rprime n\n");
    }
    int n = atoi(argv[1]); 
    printVector(rprime(n));
    return 0;
}

