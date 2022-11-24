
#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

#define N 200


struct aluno {
	int mat;
	char nome[81];
};
typedef struct aluno Aluno;

typedef Aluno* Hash[N];


int hash (int mat)
{
	return (mat%100);
}


int hash2 (int mat)
{
	return N - 2 - mat%(N-2);
}


Aluno* busca (Hash tab, int mat)
{
	int cont = 0;

	int h = hash(mat);
	while (tab[h] != NULL) {
		cont++;

		if (tab[h]->mat == mat){
			printf("\n\t %i \n", cont);
			return tab[h];
			}
		h = (h+1) % N;
	}
	return NULL;
}


Aluno* busca2 (Hash tab, int mat)
{
	int cont = 0;
	
	int h = hash(mat);
	int h2 = hash2(mat);
	while (tab[h] != NULL) {
		cont++;
	
		if (tab[h]->mat == mat){
			printf("\n\t %i \n", cont);
			return tab[h];
		}
		h = (h+h2) % N;
	}
	return NULL;
}


int insere (Hash tab, int mat, char* nome)
{
	int h = hash(mat);
	while (tab[h] != NULL) {
		if (tab[h]->mat == mat) //Se matricula Igual, atualiza os dados
			break;
		h = (h+1) % N;
	}
		if (tab[h]==NULL) { /* nï¿½o encontrou o elemento */
		tab[h] = (Aluno*) malloc(sizeof(Aluno));
		tab[h]->mat = mat;
	}
	/* atribui informaï¿½ï¿½o */
	strcpy(tab[h]->nome,nome);
	return h;
}

int insere2 (Hash tab, int mat, char* nome)//, char* email, char turma)
{                  
	int h = hash(mat);
	int h2 = hash2(mat);
	while (tab[h] != NULL) {
		if (tab[h]->mat == mat) //Se matricula Igual, atualiza os dados
			break;
			h = (h+h2) % N;
	}

	if (tab[h]==NULL) { /* nï¿½o encontrou o elemento */
		tab[h] = (Aluno*) malloc(sizeof(Aluno));
		tab[h]->mat = mat;
		//printf("\n\ttabh %d", tab[h]->mat);
	}
	
	/* atribui informaï¿½ï¿½o */
	strcpy(tab[h]->nome,nome);
	return h;
}


int main(){
	int aux_mat = 0;
	int hashed = 0;
	char aux_nome[81];
	
	Hash  dados; 
	FILE *txt;
	FILE *txt2;


	//Inicializando
		for(int i = 0; i < N; i++)
		  dados[i] = NULL;
	
	
	if((txt2 = fopen("indices2.txt", "w")) == NULL){
		printf("erro");
	} else {
		
		// le arq de
		if((txt = fopen("dados.txt","r")) == NULL){
			printf("Erro ao abrir arquivo");
		} else {
			
			printf("carregando arquivo");
			
			while (!feof(txt)){
				fscanf(txt, "%d\t %[^\n]s ", &aux_mat, aux_nome);
				printf("\nMat...: %d", aux_mat \nNome..: %s", aux_nome);
				hashed = insere2(dados, aux_mat, aux_nome);
				fprintf(txt2, "%i \n", hashed);
			}
			fclose(txt);
			
			printf("\narquivo carregado\n");

		}
		fclose(txt2);
		
	}



	// while (true){
	// 	printf("digite matricula para buscar:\n  =>");
	// 	scanf("%i",&mat );
	// 	getchar(); 
	// 	busca(dados, mat);
	// }

	
	 //Mostra
	//  for(int i = 0; i < N; i++)
	//  {
	//    	if (dados[i]!= NULL) 
	//    	{
	// 	 	    printf("\n------------------------");
	// 			printf("\nIndice: %d", i);
	// 			printf("\nMat...: %d", dados[i]->mat);
	// 			printf("\nNome..: %s", dados[i]->nome);
	// 		//	printf("\nemail.: %s", dados[i]->email);
	// 		//	printf("\nTurma.: %c", dados[i]->turma);
	// 	}
	// }


	return 0;
}
	 
 
