#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>

#define TAM_LINHA 34
#define SIZE 1024
#define KILL_PROCESS 2
#define WORK 1

typedef struct {
	char** texto;
	int linhas;
}Matriz;

long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

Matriz lerTxt() {
	Matriz m;
	FILE* fp = fopen("/home/jhillian/mdcrack-1.2/crackme.txt", "r");
	if (fp == NULL) return m;
	printf("Arquivo aberto\n");

	char** texto = (char**) malloc(TAM_LINHA * sizeof (char*));
	char linha[TAM_LINHA];
	int i = 0;

	while (!feof(fp)) {
		if (fgets(linha, TAM_LINHA, fp)) {
			texto[i] = (char*)malloc(TAM_LINHA * sizeof(char));
			strcpy(texto[i], linha);
			if (texto[i][TAM_LINHA - 2] == '\n')
				texto[i][TAM_LINHA - 2] = 0;
			i++;
		}
	}
	m.linhas = i;
	m.texto = texto;
	return m;
}

void Descriptografa(char* texto) {
	FILE* out;
	char linha[114 + TAM_LINHA];
	char buffer[SIZE];
	char* found = (char*) malloc(sizeof(char)*20);
	strcpy(linha, "/home/jhillian/mdcrack-1.2/bin/mdcrack -M MD5 -s abcdefghijklmnopqrstuvwxyz ");
	strcat(linha, texto);
	strcat(linha, " | grep \"Collision\" ");
	out = popen(linha, "r");
	if(!out){
		fprintf(stderr, "Couldn't open file\n");
		return;
	}
	fgets(buffer, SIZE, out);

	found = strstr(buffer, "=>");
	//desloca ponteiro
	found+=3;
	//copia pro endereço
	strcpy(texto, found);
}


void Sequencial(Matriz m) {
	int i;
	char** result =  (char**) malloc(m.linhas * sizeof (char*));
	char aux[50];

	for(i = 0; i < m.linhas; i++){
		result[i] =  (char*) malloc(20 * sizeof (char));
		strcpy(aux, m.texto[i]);
		printf("Decoding: %s\n", aux);
		Descriptografa(&aux);
		printf("Dedecoded: %s\n", aux);
		strcpy(result[i], aux);
	}

	for(i = 0; i < m.linhas; i++)
		printf("Hash: %s ----- Result: %s\n", m.texto[i], result[i]);

}


void Paralelo(int rank, Matriz m, int ntasks) {
	if (m.texto == NULL) return;

	bool trabalhar = true;
	int i = 0, dest = 0;
	char resposta[34];
	char msg[100];
	char** texto = (char**) malloc(sizeof(char*) * m.linhas);
	int posicoes[ntasks];
	int source, espera = 0;

	MPI_Status status;

	for(i = 0; i < m.linhas; i++)
		texto[i] = (char*) malloc(sizeof(char) * 100);

	for (i = 1; i < ntasks && i <= m.linhas; i++){
		MPI_Send(m.texto[i-1], 34, MPI_CHAR, i, WORK, MPI_COMM_WORLD); //envia pra todos inicialmente
		posicoes[i] = i-1;
		espera++;
	}

	while(i <= m.linhas || espera > 0){
		MPI_Recv(msg, 100, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		//printf("Gerenciador: Processo (%d) me respondeu...:   %s\n", status.MPI_SOURCE, msg);

		strcpy(texto[posicoes[status.MPI_SOURCE]], msg);
		espera--;
		if (i <= m.linhas){
			MPI_Send(m.texto[i-1], 34, MPI_CHAR, status.MPI_SOURCE, WORK, MPI_COMM_WORLD);			
			espera++;
			posicoes[status.MPI_SOURCE] = i-1;
			i++;
		}
	}

	for (i = 1; i < ntasks; i++)
		MPI_Send("Morre", 5, MPI_CHAR, i, KILL_PROCESS, MPI_COMM_WORLD); //morre diabo!

	for (i = 0; i < m.linhas; i++)
		printf("Hash: %s ---------- Result: %s\n", m.texto[i], texto[i]);

}

void Escravos(int rank) {
	MPI_Status status;
	char msg[34];
	char* buffer = (char*) malloc(sizeof(char) * 20);
	bool done = true;
	char aux[50];
	

	while (done) {

		MPI_Recv(msg, 34, MPI_CHAR, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		switch(status.MPI_TAG){
			case WORK:
				//printf("Trabalhador %d:  Mestre me enviou...:   %s\n", rank, msg);
				//DESCOBRIR PQ O Descriptografa RETORNA NADA
				//Já que não dá pra retornar, eu passo um endereço pra ele alterar
				strcpy(aux, msg);
				printf("Decoding: %s\n", aux);
				Descriptografa(&aux);
				printf("Dedecoded: %s\n", aux);
				MPI_Send(aux, 100, MPI_CHAR, 0, WORK, MPI_COMM_WORLD);
				break;
			case KILL_PROCESS:
				done = false;
				printf("Acabou tarefas! Sou o processo : %d\n", rank);
				break;
		}

	}
}

int main(int argc, char** argv) {
	int ntasks, rank;
	int inicio, fim;
	double start, end;
	bool trabalhar = true;
	MPI_Request request;
	MPI_Status status;
	int source = 0;
	long start_time, end_time;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	Matriz m;
	char msg[100];
	int i, j;
	int dest;
	
	if (rank == 0) {
		//printf("Vou abrir o txt...\n");
		m = lerTxt();
		start_time = wtime();
		Sequencial(m);
		end_time = wtime();
		printf("Tempo Sequencial: %ld usec\n", (long)(end_time - start_time));
	}

	MPI_Barrier(MPI_COMM_WORLD);
	printf("Paralelo\n");
	if (rank == 0) {
		start_time = wtime();
		Paralelo(rank, m, ntasks);
		end_time = wtime();
		printf("Tempo Paralelo: %ld usec\n", (long)(end_time - start_time));
	}
	else {
		Escravos(rank);
	}

	MPI_Finalize();
	return 0;
}
