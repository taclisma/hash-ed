#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define N 200


int hash (int mat){
	return (mat%100);
}


int hash2 (int mat)
{
	return N - 2 - mat%(N-2);
}


// Aluno* busca (Hash tab, int mat){
// 	int cont = 0;
// 	int h = hash(mat);
// 	while (tab[h] != NULL) {
// 		cont++;
// 		if (tab[h]->mat == mat){
// 			printf("\n\t %i \n", cont);
// 			return tab[h];
// 			}
// 		h = (h+1) % N;
// 	}
// 	return NULL;
// }


// Aluno* busca2 (Hash tab, int mat)
// {
// 	int cont = 0;	
// 	int h = hash(mat);
// 	int h2 = hash2(mat);
// 	while (tab[h] != NULL) {
// 		cont++;
// 		if (tab[h]->mat == mat){
// 			printf("\n\t %i \n", cont);
// 			return tab[h];
// 		}
// 		h = (h+h2) % N;
// 	}
// 	return NULL;
// }


// int insere (Hash tab, int mat, char* nome){
// 	int h = hash(mat);
// 	while (tab[h] != NULL) {
// 		if (tab[h]->start->aluno->mat == mat) //Se matricula Igual, atualiza os dados
// 			break;
// 		h = (h+1) % N;
// 	}
// 		if (tab[h]==NULL) { /* nï¿½o encontrou o elemento */
// 		tab[h] = (Aluno*) malloc(sizeof(Aluno));
// 		tab[h]->mat = mat;
// 	}
// 	/* atribui informaï¿½ï¿½o */
// 	strcpy(tab[h]->nome,nome);
// 	return h;
// }


int insere2 (Hash tab, int mat, char* nome){//, char* email, char turma){                  
	int h = hash2(mat);
	node *aux = NULL;
	Aluno *newdata = NULL;

	while(aux != NULL) {
		if (aux->aluno->mat == mat){ //Se matricula Igual sai do loop
		return -1;
		}

		aux = aux->next; //se não, prox

	}

	// aux == NULL
	if (tab[h] == NULL){ /* nao encontrou a lista */
		tab[h] = init(); 	//inicia lista  
	}
	aux = tab[h]->start;
	/* atribui informacao */		
	newdata = (Aluno*) malloc(sizeof(Aluno));
	newdata->mat = mat;
	strcpy(newdata->nome, nome);
	insert(tab[h], newdata);
	
	
	return h;
}


int main(){
	int aux_mat = 0;
	int hashed = 0;
	char aux_nome[81];
	
	Hash  dados; 
	FILE *txt;

	//Inicializando
	for(int i = 0; i < N; i++)
		dados[i] = NULL;

	// le arq de dados
	if((txt = fopen("dados.txt","r")) == NULL){
		printf("Erro ao abrir arquivo");
	} else {
		
		printf("carregando arquivo");
		
		while (!feof(txt)){
			fscanf(txt, "%d\t %[^\n]s ", &aux_mat, aux_nome);
			printf("\nMat...: %d\nNome..: %s", aux_mat, aux_nome);
			insere2(dados, aux_mat, aux_nome);
		}
		fclose(txt);
		
		printf("\narquivo carregado\n");

	}

	return 0; 
}
