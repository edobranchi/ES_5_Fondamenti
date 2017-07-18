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
void merge(struct list **ptrptr, struct list *ptr);
boolean is_lower(struct list a, struct list b);
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
        ord_insert(&A,values);
    }
    merge(&A,B);
    visit(A);
}


void init(struct list **ptrptr){
    *ptrptr=NULL;
}

void merge(struct list **ptrptr, struct list *ptr) {
    while(ptr != NULL){
        if(is_lower(**ptrptr, *ptr) == TRUE ) {
            (*ptrptr) = (*ptrptr)->next_ptr;
        }else{
            struct list * tmp;
            *tmp = **ptrptr;
            *ptrptr = (*ptrptr)->next_ptr;
            tmp->next_ptr = ptr;
            tmp = ptr;
            ptr = ptr->next_ptr;
            tmp->next_ptr = (*ptrptr);
        }
        if((*ptrptr) == NULL && ptr != NULL){
            (*ptrptr)->next_ptr = ptr;
            ptr = ptr->next_ptr;
        }
    }

}

boolean is_lower(struct list a, struct list b){
    if(a.value - b.value < FLT_EPSILON) {
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