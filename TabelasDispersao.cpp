#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define MAXCHAR 81
#define N 8000


int hash2 (int mat, int uf){
	return N - uf - mat%(N - uf);
}


Cidade* busca2 (Hash tab, int cod, int uf){
	int cont = 0;	
	int h2 = hash2(cod, uf);

	FILE *log = NULL;
	node *aux = NULL;

	if (tab[h2] != NULL) {
		aux = tab[h2]->start;
		while (aux != NULL){
			cont++;
			printf("\t %i \n", cont);
			if (aux->cidade->codmun == cod) {
				if((log = fopen("log.csv", "a")) == NULL){
					printf("erro ao abrir log");
				} else {
					fprintf(log, "%i,%i,%s,%i,%i\n", aux->cidade->coduf, aux->cidade->codmun, aux->cidade->nome, h2, cont);
					fclose(log);
				}
				return aux->cidade;
			}
			aux = aux->next;
		}
	}
	return NULL;
}


int insere2 (Hash tab, Cidade auxc){//, char* email, char turma){                  
	int h = hash2(auxc.codmun, auxc.coduf);
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
	if (tab[h] == NULL){ 	//nao encontrou a lista
		tab[h] = init(); 	//inicia lista  
	}
	
	/* atribui informacao */		
	newdata = (Cidade*) malloc(sizeof(Cidade));
	newdata->coduf = auxc.coduf;
	newdata->pop = auxc.pop;
	newdata->codmun = auxc.codmun;
	strcpy(newdata->nome, auxc.nome);
	strcpy(newdata->uf, auxc.uf);
	insert(tab[h], newdata); // insere na lista
	
	return h;
}


void print_cidade(Cidade *a){
	if (a != NULL){
		printf("nome da cidade: "); 
		puts(a->nome);
		printf(""); 
		printf("populaçao: %i", a->pop); 
		printf("\n");	
	} else {
		printf("\nnao encontrado\n");
	}
}


int main(){
	char header[5][31];
	int flag = 0;
	int codbusca = 0;
	int codufbusca = 0;
	char ccod[10];
	char row[MAXCHAR];
	char *col = NULL;

	Cidade auxc;

	Hash  dados; 
	FILE *csv;
	FILE *busca;
	FILE *cod;

	//Inicializando
	for(int i = 0; i < N; i++)
		dados[i] = NULL;
	

	// le arq de dados
	if((csv = fopen("muni.csv","r")) == NULL){
		printf("Erro ao abrir arquivo dados");

	} else {
		
		printf("carregando arquivo");
		
		while (fgets(row, MAXCHAR, csv)){
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
				
				} else {
					
					// salva dados no auxiliar
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
					insere2(dados, auxc);

					// sai
					col = strtok(NULL,";");
				}
			}

		} // while / fim do arq dados 
		fclose(csv);
	}

	// busca todas as cidades
	printf("\narquivo carregado\n");
	getchar();
	
	if((busca = fopen("pbusca.csv", "r")) == NULL){
		printf("Erro ao abrir arquivo indice");
	} else {
		while((fgets(row, MAXCHAR, busca))){
			col = strtok(row,",");
			
			while(col != NULL){
			codbusca = atoi(col);
			col = strtok(NULL,",");
			codufbusca = atoi(col);
			print_cidade(busca2(dados, codbusca, codufbusca)); //n existe
			col = strtok(NULL,",");
			}

		}
	}
	fclose(busca);
	getchar();
	// Insira um novo Registro: (Código 6000, Município "Novo Registro", RS, População 6.000). 
	// Onde foi inserido e qual é a quantidade de acessos para esse novo registro? 

	strcpy(auxc.uf,"RS");
	auxc.coduf = 43;
	auxc.codmun = 6000;
	strcpy(auxc.nome,"Novo Registro");
	auxc.pop = 6000;
	insere2(dados, auxc);
	print_cidade(busca2(dados, auxc.codmun, auxc.coduf)); //n existe


	return 0; 
}
