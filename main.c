#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef unsigned short int boolean;
#define TRUE 1
#define FALSE 0

struct list{
    float value;
    struct list *next_ptr;
};

void init(struct list **ptrptr);
void ord_insert(struct list ** ptrptr,float value);
void merge(struct list **ptrptr, struct list **ptr);
boolean is_lower_or_equal(float a, float b);
void visit(struct list* ptr);
void pre_insert(struct list ** ptrptr, float value);


int main() {

    struct list *A ,*B;
    init(&A);
    init(&B);

    int i=0;
    int b=0;
    float values=0;

    printf("Quanti elementi vuoi inserire nella prima lista?");
    scanf("%d",&i);
    for (b=0;b<i;b++){
        printf("Inserisci il valore %d ",b);
        scanf("%f",&values);
        ord_insert(&A,values);
    }
    printf("Quanti elementi vuoi inserire nella seconda lista?");
    scanf("%d",&i);
    for(b=0;b<i;b++){
        printf("Inserisci il valore %d ", b);
        scanf("%f",&values);
        ord_insert(&B,values);
    }
    merge(&A,&B);
    visit(A);
}


void init(struct list **ptrptr){
    *ptrptr=NULL;
}

void merge(struct list **ptrptr, struct list **ptr) {
    struct list * tmpA;
    tmpA=(*ptrptr)->next_ptr;

    while(*ptr != NULL && *ptrptr != NULL){
        if((*ptrptr)->next_ptr == NULL){
            (*ptrptr)->next_ptr = *ptr;
            break;
        }
        else if(is_lower_or_equal((*ptrptr)->value,(*ptr)->value )== TRUE && is_lower_or_equal((*ptr)->value,tmpA->value)== TRUE ) {
            (*ptrptr)->next_ptr=*ptr;
            *ptr=(*ptr)->next_ptr;
            (*ptrptr)->next_ptr->next_ptr=tmpA;
            ptrptr = &(*ptrptr)->next_ptr;

        }else{
            ptrptr = &(*ptrptr)->next_ptr;
            tmpA=(*ptrptr)->next_ptr;
        }
    }
}

boolean is_lower_or_equal(float a, float b){
    if(a-b<FLT_EPSILON || (a - b < FLT_EPSILON*a && -FLT_EPSILON*a < (a-b) )) {
        return TRUE;
    }else return FALSE;
}

void visit(struct list* ptr){
    int count = 0;
    while (ptr!=NULL){
        printf("Elemento %d: %f\n",count,ptr->value);
        ptr = ptr->next_ptr;
        count++;
    }
}

void pre_insert(struct list ** ptrptr, float value){
    struct list * tmp_ptr;
    tmp_ptr = * ptrptr;
    * ptrptr = (struct list *)malloc(sizeof(struct list));
    (* ptrptr)->value = value;
    (* ptrptr)->next_ptr = tmp_ptr;
}

void ord_insert(struct list ** ptrptr, float value){
    while(*ptrptr != NULL && (*ptrptr)->value < value)
        ptrptr = &((*ptrptr)->next_ptr);

    pre_insert(ptrptr, value);
}