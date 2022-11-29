#ifndef HEADER_FILE_LIST
#define HEADER_FILE_LIST

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 200

struct aluno {
	int mat;
	char nome[81];
};
typedef struct aluno Aluno;


typedef struct node{
    struct node *next;
    Aluno *aluno;
 } node;

typedef struct list{
    node *start;
    node *end;
} list;

typedef list *Hash[N];

//cria lista
list* init(){
    list *lista = (list*) malloc(sizeof(list));
	if(lista != NULL){
        lista->start = NULL;
        lista->end = NULL;
        return lista;
    }
    return NULL;
}


// true = vazia
bool empty(list *l){
    return (!l->start);
}


bool insert(list* l, Aluno* a){
    node *aux = l->start;
    node *newnode; 

    // cria novo nó
    newnode = (node*) malloc(sizeof(node));
    if(!newnode) return false;
    newnode->next = NULL;
    newnode->aluno = a;

    // insere no inicio
    if(!l->start){ //funciona
        l->start = newnode;
        l->end = newnode;
        return true;

    // insere ultimo
    } else {
        
        //caminha na lista
        while(aux->next){
            aux = aux->next;
        }

        //chega na inserção
        aux->next = newnode;
        l->end = newnode;
        return true;
    }

}


// // imprime lista
// void printlist(list *l){
//     node *aux = l->start;
//     if(empty(l)){
//         printf("lista vazia\n");
//     } else {
//         while(aux != NULL){
//             printf("%i\n", aux->aluno);
//             aux = aux->next;;
//         }
//     }
// }


//limpa lista
void cleanlist(list *l){
    node *aux = l->start, *aux2;
    while(aux != NULL){
        aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
}


// busca em lista
Aluno* lista_busca(list *l, int m){
    node *aux = NULL;
    
    if (l->start != NULL){
        aux = l->start;
        while(aux != NULL){
            if(aux->aluno->mat == m) return aux->aluno;
            
            aux = aux->next;
        }
    }
        return NULL;
}


#endif
