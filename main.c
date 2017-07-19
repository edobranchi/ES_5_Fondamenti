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

    printf("Quanti elementi vuoi inserire nella prima lista?");                      //inserimento della lista A
    scanf("%d",&i);
    for (b=0;b<i;b++){
        printf("Inserisci il valore %d ",b+1);
        scanf("%f",&values);
        ord_insert(&A,values);                                                       //inserimento in ordine per assicurarsi che la lista sia ordinata
    }

    printf("Quanti elementi vuoi inserire nella seconda lista?");                    //inserimento lista B
    scanf("%d",&i);
    for(b=0;b<i;b++){
        printf("Inserisci il valore %d ", b+1);
        scanf("%f",&values);
        ord_insert(&B,values);
    }

    merge(&A,&B);                                                                   //chiamata della funzione merge che unisce in maniera ordinata le due liste
    visit(A);                                                                       //funzione di stampa
}


void init(struct list **ptrptr){
    *ptrptr=NULL;                                                                   //inizializzazione delle due liste
}

void merge(struct list **ptrptr, struct list **ptr) {
    struct list * tmpA;
    tmpA=(*ptrptr)->next_ptr;                                                        //Associa il puntatore temporaneo al secondo elemento della prima lista

    while(*ptr != NULL && *ptrptr != NULL){                                          //Controllo che entrambe le liste non siano vuote
        if((*ptrptr)->next_ptr == NULL){                                             //Se la prima lista si è esaurita la collega agli elementi rimanenti della seconda
            (*ptrptr)->next_ptr = *ptr;
            break;                                                                   //ed esce dalla funzione
        }
        else if(is_lower_or_equal((*ptrptr)->value,(*ptr)->value )== TRUE && is_lower_or_equal((*ptr)->value,tmpA->value)== TRUE ) {  //controlla che l'elemento di B da inserire sia compreso tra i due valori di A presi in considerazione
            (*ptrptr)->next_ptr=*ptr;                                                //collega l'elemento di A all' elemento di B
            *ptr=(*ptr)->next_ptr;                                                   //sposta ptr al prossimo elemento di B
            (*ptrptr)->next_ptr->next_ptr=tmpA;                                      //ricollega l'elemento inserito alla lista A
            ptrptr = &(*ptrptr)->next_ptr;                                           //sposta ptrptr all' elemento successivo

        }else{
            ptrptr = &(*ptrptr)->next_ptr;                                           //sposta ptrptr all' elemento successivo
            tmpA=(*ptrptr)->next_ptr;                                                //sposta tmpA all'elemento successivo
        }
    }
}

boolean is_lower_or_equal(float a, float b){
    if(a-b<FLT_EPSILON || (a - b < FLT_EPSILON*a && -FLT_EPSILON*a < (a-b) )) {    //funzione che controlla se un valore
        return TRUE;                                                               //float è minore o uguale ad un altro
    }else return FALSE;
}

void visit(struct list* ptr){                                                     //funzione di visita e di stampa della lista
    int count = 0;
    while (ptr!=NULL){
        printf("Elemento %d: %f\n",count,ptr->value);
        ptr = ptr->next_ptr;
        count++;
    }
}

void pre_insert(struct list ** ptrptr, float value){
    struct list * tmp_ptr;                                                        //alloca un puntatore temporaneo
    tmp_ptr = * ptrptr;                                                           //lo assegna al primo elemento della lista
    * ptrptr = (struct list *)malloc(sizeof(struct list));                        //alloca spazio per l' elemento da inserire
    (* ptrptr)->value = value;                                                    //scrive il valore nel campo value
    (* ptrptr)->next_ptr = tmp_ptr;                                               //ricollega la lista
}

void ord_insert(struct list ** ptrptr, float value){                              //inserimento in ordine
    while(*ptrptr != NULL && (*ptrptr)->value < value)                            //controlla se *ptrptr punta ad elemento
        ptrptr = &((*ptrptr)->next_ptr);                                          // e se il valore da inserire è maggiore del
                                                                                  //valore presente in lista
    pre_insert(ptrptr, value);                                                    //chiama l'inserimento in testa
}