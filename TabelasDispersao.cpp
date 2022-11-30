#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define MAXCHAR 81
#define N 5580


int hash (int mat){
	return (mat%100);
}


int hash2 (int mat)
{
	return N - 2 - mat%(N-2);
}


// Cidade* busca (Hash tab, int mat){
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


Cidade* busca2 (Hash tab, int mat){
	int cont = 0;	
	int h2 = hash2(mat);
	node *aux = NULL;

	if (tab[h2] != NULL) {
		aux = tab[h2]->start;
		while (aux != NULL){
			cont++;
			printf("\t %i \n", cont);
			if (aux->cidade->mat == mat) {
				return aux->cidade;
			}
			aux = aux->next;
		}
	}
	return NULL;
}


// int insere (Hash tab, int mat, char* nome){
// 	int h = hash(mat);
// 	while (tab[h] != NULL) {
// 		if (tab[h]->start->cidade->mat == mat) //Se matricula Igual, atualiza os dados
// 			break;
// 		h = (h+1) % N;
// 	}
// 		if (tab[h]==NULL) { /* nï¿½o encontrou o elemento */
// 		tab[h] = (Cidade*) malloc(sizeof(Cidade));
// 		tab[h]->mat = mat;
// 	}
// 	/* atribui informaï¿½ï¿½o */
// 	strcpy(tab[h]->nome,nome);
// 	return h;
// }


int insere2 (Hash tab, Cidade auxc){//, char* email, char turma){                  
	int h = hash2(auxc.codmun);
	node *aux = NULL;
	Cidade *newdata = NULL;

	while(aux != NULL) {
		if (aux->cidade == auxc.codmun){ //Se matricula Igual sai do loop
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
	newdata = (Cidade*) malloc(sizeof(Cidade));
	newdata->mat = mat;
	strcpy(newdata->nome, nome);
	insert(tab[h], newdata);
	
	
	return h;
}

// busca em lista
Cidade* lista_busca(list *l, int m){
	int cont = 0;	

    node *aux = NULL;
    
    if (l->start != NULL){
        aux = l->start;
        while(aux != NULL){
            if(aux->cidade->mat == m) return aux->cidade;
            
            aux = aux->next;
        }
    }
        return NULL;
}

void print_cidade(Cidade *a){
	if (a != NULL){
		printf("nome: "); 
		puts(a->nome);
		printf("\n"); 
		printf("matricula: %d", a->mat); 
		printf("\n");	
	} else {
		printf("\nnao encontrado\n");
	}
}






int main(){
	char header[5][31];
	int flag = 0;
	int hashed = 0;
	char row[MAXCHAR];
	char *col = NULL;

	Cidade *auxc = NULL;
	Hash  dados; 
	FILE *csv;

	//Inicializando
	for(int i = 0; i < N; i++)
		dados[i] = NULL;

	// le arq de dados
	if((csv = fopen("muni.csv","r")) == NULL){
		printf("Erro ao abrir arquivo");
	} else {
		
		printf("carregando arquivo");
		
		while (!feof(csv)){
			fgets(row, MAXCHAR, csv);
			col = strtok(row, ";");

		//navega strtok
			while (col != NULL){
			//flag p pegar header
				if(!flag){
					for(int i = 0; i < 5; i++){
						strcpy(header[i], col);
						col = strtok(NULL,";");
					}
					flag = 1;
				
			// salva dados no auxiliar
				} else {
					strcpy(auxc->uf,col);
					col = strtok(NULL,";");
					
					auxc->coduf = atoi(col);
					col = strtok(NULL,";");
					
					auxc->codmun = atoi(col);
					col = strtok(NULL,";");
					
					strcpy(auxc->nome,col);
					col = strtok(NULL,";");

					auxc->pop = atoi(col);
					col = strtok(NULL,";");
				}
			}

			// insere
			insere2(dados, auxc);
		}
		fclose(csv);
		
		printf("\narquivo carregado\n");

		print_cidade(busca2(dados, 1010));
		print_cidade(busca2(dados, 2010));
		print_cidade(busca2(dados, 100));

	}

	return 0; 
}
