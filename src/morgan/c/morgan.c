/*
 * This program comes from morgran.esf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    double *value;
    int dim0, dim1;
}array;

#define newArray() (array*)malloc(sizeof(array))
#define initArray(t,d0,d1) {t=newArray();\
   t->dim0=d0; t->dim1=d1; t->value=allocDouble((d0)*(d1));}

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

double* allocDouble(double m){
    return (double*)alloc(m * sizeof(double));
}

void tryFree(void* t){
    if(t != NULL){
        free(t);
    }
}

void tryFreeArray(array *t){
    if(t != NULL){
        tryFree(t->value);
        tryFree(t);
    }
}

array* scan(array* a){
    int i,j,dim0,dim1;
    array* t;
    dim0 = a->dim0;
    dim1 = a->dim1;
    initArray(t, dim0, dim1);
    for(i=0; i<dim0; i++){
        t->value[i*dim1] = a->value[i*dim1];
        for(j=1; j<dim1; j++){
            t->value[i*dim1+j] =
                a->value[i*dim1+j] + t->value[i*dim1+j-1];
        }
    }
    return t;
}

array* drop(int x0, array* a){
    int i,j,count;
    int dim0,dim1,newDim1;
    array *t;
    dim0 = a->dim0;
    dim1 = a->dim1;
    count= 0; 
    if(abs(x0) > dim1){
        initArray(t,0,0);
    }
    else if(x0 < 0){
        newDim1 = dim1 + x0;
        initArray(t,dim0,newDim1);
        for(i=0; i<dim0; i++){
            for(j=0; j<newDim1; j++){
                t->value[count++] = a->value[i*dim1+j];
            }
        }
    }
    else{
        newDim1 = dim1 - x0;
        initArray(t,dim0,newDim1);
        for(i=0; i<dim0; i++){
            for(j=x0; j<dim1; j++){
                t->value[count++] = a->value[i*dim1+j];
            }
        }
    }
    return t;
}

array* concat(array *a){
    array *t;
    int i,j,dim0, dim1,newDim1,count;
    dim0    = a->dim0;
    dim1    = a->dim1;
    newDim1 = dim1 + 1;
    count   = 0;
    initArray(t, dim0, newDim1);
    for(i=0; i<dim0; i++){
        t->value[count++] = 0;
        for(j=0; j<dim1; j++){
            t->value[count++] = a->value[i*dim1+dim0];
        }
    }
    return t;
}

array* minus(array *a, array *b){
    if(a->dim0 != b->dim0 || a->dim1 != b->dim1){
        errorMessage("Two arrays have different shape in minus");
    }
    array *t;
    int i,j,dim0, dim1;
    dim0 = a->dim0;
    dim1 = a->dim1;
    initArray(t,dim0,dim1);
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++){
            t->value[i*dim1+j] = 
                a->value[i*dim1+j] - b->value[i*dim1+j];
        }
    }
    return t;
}

array* plus(array *a, array *b){
    if(a->dim0 != b->dim0 || a->dim1 != b->dim1){
        errorMessage("Two arrays have different shape in plus");
    }
    array *t;
    int i,j,dim0, dim1;
    dim0 = a->dim0;
    dim1 = a->dim1;
    initArray(t,dim0,dim1);
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++){
            t->value[i*dim1+j] = 
                a->value[i*dim1+j] + b->value[i*dim1+j];
        }
    }
    return t;
}

array* msum(int n, array *a){
    array *t,*t0,*t1,*r; 
    t  = scan(a);
    t0 = concat(drop(-n,t));
    t1 = drop(n-1,t);
    r  = minus(t0,t1);
    tryFreeArray(t);
    tryFreeArray(t0);
    tryFreeArray(t1);
    return r;
}

array* power(array *a, double c){
    int i,j,dim0,dim1;
    array *t;
    dim0 = a->dim0;
    dim1 = a->dim1;
    initArray(t, dim0, dim1);
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++){
            t->value[i*dim1+j] = pow(a->value[i*dim1+j],c);
        }
    }
    return t;
}

array* multiply(array *a, array *b){
    if(a->dim0 != b->dim0 || a->dim1 != b->dim1){
        errorMessage("Two arrays have different shape in multiplication");
    }
    int i,j,dim0,dim1;
    array *t;
    dim0 = a->dim0;
    dim1 = a->dim1;
    initArray(t, dim0, dim1);
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++){
            t->value[i*dim1+j] =
                a->value[i*dim1+j] * b->value[i*dim1+j];
        }
    }
    return t;
}

array* divide(array *a, double c){
    int i,j,dim0,dim1;
    array *t;
    dim0 = a->dim0;
    dim1 = a->dim1;
    initArray(t, dim0, dim1);
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++){
            t->value[i*dim1+j] = a->value[i*dim1+j]/c;
        }
    }
    return t;
}

array* divideArray(array *a, array *b){
    int i,j,dim0,dim1;
    array *t;
    dim0 = a->dim0;
    dim1 = a->dim1;
    initArray(t, dim0, dim1);
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++){
            t->value[i*dim1+j] = a->value[i*dim1+j]/b->value[i*dim1+j];
        }
    }
    return t;
}


array* absolute(array *a){
    int i,j,dim0,dim1;
    array *t;
    dim0 = a->dim0;
    dim1 = a->dim1;
    initArray(t, dim0, dim1);
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++){
            t->value[i*dim1+j] = fabs(a->value[i*dim1+j]);
        }
    }
    return t;
}

array* morgan(int n, array *x, array *y){
    array *sx,*sx2,*sy,*sy2,*sxy;
    array *t0,*t1,*t2,*part0,*part1,*part2;
    array *r;
    sx = msum(n, x);
    sy = msum(n, y);
    sx2 = msum(n, power(x, 2));
    sy2 = msum(n, power(y, 2));
    sxy = msum(n, multiply(x, y));
    // last line
    // part 0
    t0 = divide(sy, n);
    t1 = power (t0, 2); tryFreeArray(t0);
    t0 = divide(sy2, n);
    t2 = minus(t0, t1); tryFreeArray(t0); tryFreeArray(t1);
    t0 = absolute(t2);  tryFreeArray(t2); 
    part0 = power(t0, 0.5);tryFreeArray(t0); 
    // part 1
    t0 = divide(sx,n);
    t1 = power(t0, 2); tryFreeArray(t0);
    t0 = divide(sx2,n);
    t2 = plus(t0,t1); tryFreeArray(t0); tryFreeArray(t1); 
    part1 = power(t2, 0.5); tryFreeArray(t2);
    // part 2
    t0 = multiply(sx, sy);
    t1 = divide(t0, pow(n,2)); tryFreeArray(t0); 
    t0 = divide(sxy, n);
    part2 = minus(t0, t1); tryFreeArray(t0); tryFreeArray(t1);
    // r
    t0 = multiply(part0, part1);
    r  = divideArray(part2, t0);
    tryFreeArray(t0);
    tryFreeArray(part0);
    tryFreeArray(part1);
    tryFreeArray(part2);
    return r;
}

array* loadArray(){
    int i,j,dim0, dim1;
    array *t;
    initArray(t, dim0, dim1);
    scanf("%d %d",&dim0,&dim1);
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++)
            scanf("%d", &(t->value[i*dim1+j]));
    }
    return t;
}

void printArray(array *r){
    int i,j, dim0, dim1;
    dim0 = r->dim0;
    dim1 = r->dim1;
    for(i=0; i<dim0; i++){
        for(j=0; j<dim1; j++){
            if(j!=0) printf(" ");
            printf("%lf", r->value[i*dim1+j]);
        }
        printf("\n");
    }
    printf("[dim = (%d, %d)]\n", dim0, dim1);
}

int main(int argc, char**  argv){
    if(argc != 1){
        errorMessage("Usage: ./rprime < file.txt \n");
    }
    int n; 
    array *x, *y;
    scanf("%d",&n);
    x = loadArray();
    y = loadArray();
    // time_start
    array* r = morgan(n, x, y);
    // time_end
    printArray(r);
    tryFreeArray(x);
    tryFreeArray(y);
    tryFreeArray(r);
    return 0;
}

