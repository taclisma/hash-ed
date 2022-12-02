#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define MAXCHAR 81
#define N 8000


int hash2 (int mat)
{
	return N - 2 - mat%(N-2);
}


Cidade* busca2 (Hash tab, int cod){
	int cont = 0;	
	int h2 = hash2(cod);

	node *aux = NULL;

	if (tab[h2] != NULL) {
		aux = tab[h2]->start;
		while (aux != NULL){
			cont++;
			printf("\t %i \n", cont);
			if (aux->cidade->codmun == cod) {
				return aux->cidade;
			}
			aux = aux->next;
		}
	}
	return NULL;
}


int insere2 (Hash tab, Cidade auxc){//, char* email, char turma){                  
	int h = hash2(auxc.codmun);
	node *aux = NULL;
	Cidade *newdata = NULL;

	if(tab[h] != NULL) {
		aux = tab[h]->start;
		while (aux != NULL){
			
			if (aux->cidade->codmun == auxc.codmun){ //Se matricula Igual sai do loop
				break;
			}

			aux = aux->next; //se não, prox
		
		}
		//nao encontrado na lista existente
	}

	// se tab nao existe
	if (tab[h] == NULL){ /* nao encontrou a lista */
		tab[h] = init(); 	//inicia lista  
	}
	
	/* atribui informacao */		
	newdata = (Cidade*) malloc(sizeof(Cidade));
	newdata->coduf = auxc.coduf;
	newdata->pop = auxc.pop;
	newdata->codmun = auxc.codmun;
	strcpy(newdata->nome, auxc.nome);
	strcpy(newdata->uf, auxc.uf);
	insert(tab[h], newdata);
	
	return h;
}


void print_cidade(Cidade *a){
	if (a != NULL){
		printf("nome da cidade: "); 
		puts(a->nome);
		printf("\n"); 
		printf("populaçao: %i", a->pop); 
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

	Cidade auxc;
	Hash  dados; 
	FILE *csv;
	FILE *ind;

	//Inicializando
	for(int i = 0; i < N; i++)
		dados[i] = NULL;
	
	if((ind = fopen("ind.txt", "w")) == NULL){
		printf("Erro ao abrir arquivo indice");
	} else {
		// le arq de dados
		if((csv = fopen("muni.csv","r")) == NULL){
			printf("Erro ao abrir arquivo dados");

		} else {
			
			printf("carregando arquivo");
			
			while (fgets(row, MAXCHAR, csv)){
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
						
						printf("col p uf: %s\n", col);
						strcpy(auxc.uf,col);
						col = strtok(NULL,";");
						
						printf("col p coduf: %s\n", col);
						auxc.coduf = atoi(col);
						col = strtok(NULL,";");
						
						printf("col p codmun: %s\n", col);
						auxc.codmun = atoi(col);
						col = strtok(NULL,";");
						
						printf("col p nome: %s\n", col);
						strcpy(auxc.nome,col);
						col = strtok(NULL,";");

						printf("col p pop: %s\n", col);
						auxc.pop = atoi(col);
						//getchar();

						// insere
						fprintf(ind, "%i\n", auxc.codmun);
						insere2(dados, auxc);

						// sai
						col = strtok(NULL,";");
					}
				}

			} // while / fim do arq dados 

			fclose(csv);
		
		} // fecha arq indice
		fclose(ind);
		printf("\narquivo carregado\n");

		print_cidade(busca2(dados, 14209)); //cod mun pedrosorio
		print_cidade(busca2(dados, 14407)); //cod mun pelotas
		print_cidade(busca2(dados, 100000)); // n existe

	}

	return 0; 
}
