- Alunos: Gabriel Cardoso dos Santos, Jhillian Bianchi
- Matricula: 201510710, 201310739

- T8 - Quebra de Senhas com OpenMPI
- Prof. Andrea Schwertner Charao


1 - Estratégias de Paralelização

- Utilizando-se do OpenMPI, a paralelização foi desenvolvida sob o formato chefe-trabalhador. Consiste de um processo chefe que distribui as tarefas entre seus processos "empregados". Foi utilizado MPI_Send e MPI_Recv para fazer a comunicação entre os processos chefe e empregado. Também foram utilizadas duas MPI_Tags diferentes, sendo uma (work) para indicar que algum trabalho deve ser feito e (kill_process) para indicar que não há mais trabalho a fazer e o processo pode finalizar.

- Código do chefe e do empregado:
- Diferenciação entre as MPI_tags:

   ```
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

   ```
   
   ```
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
				strcpy(aux, msg);
				printf("Decoding: %s\n", aux);
				Descriptografa(&aux);
				printf("Dedecoded: %s\n", aux);
				MPI_Send(aux, 100, MPI_CHAR, 0, WORK, MPI_COMM_WORLD);
				break;
			case KILL_PROCESS:
				done = false;
				//printf("Acabou tarefas! Sou o processo : %d\n", rank);
				break;
		}

	}
   }
   ```


O código completo se encontra em [MD5_.c](MD5_.c).

2 - Resultados:

Para o programa sequencial os resultados obtidos na média de execuções sobre o arquivo [crackme.txt](crackme.txt),foram: 
                     
                     |        1        | SpeedUp()|
                     |-----------------|----------|
                     | 1225763343 usec |     -    |
                     
Já com 2 threads obtivemos:
  
                     |        2        | SpeedUp()|
                     |-----------------|----------|
                     | 1244648037 usec |   0,98   |

E com 4:

                     |        4        | SpeedUp()|
                     |-----------------|----------|
                     | 1030846979 usec |   1,18   |


O hardware usado foi:

       Arquitetura:           x86_64
       Modo(s) operacional da CPU:32-bit, 64-bit
       Ordem dos bytes:       Little Endian
       CPU(s):                4
       Lista de CPU(s) on-line:0-3
       Thread(s) per núcleo: 2
       Núcleo(s) por soquete:2
       Soquete(s):            1
       Nó(s) de NUMA:        1
       ID de fornecedor:      GenuineIntel
       Família da CPU:       6
       Modelo:                61
       Nome do modelo:        Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz
       Step:                  4
       CPU MHz:               2182.409
       CPU MHz máx.:         2700,0000
       CPU MHz mín.:         500,0000
       BogoMIPS:              4391.85
       Virtualização:       VT-x
       cache de L1d:          32K
       cache de L1i:          32K
       cache de L2:           256K
       cache de L3:           3072K
       CPU(s) de nó0 NUMA:   0-3
 
       OBS: na verdade são 2 cores e 2 hiperthreads mas o linux não pega
       OBS2: Código rodou em máquina virtual sobre o Ubuntu 16.04
	




