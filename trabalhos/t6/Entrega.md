Aluno: Jhillian Bianchi
Mat:201310739

ELC139 - Programação Paralela
Prof. Andrea Schwertner Charão

T6 - Práticas em MPI

- Parte 1: 

- a)Baixado e estudado 

- b) 
- Particionamento: part_size = n/ntasks
- Aglomeração: O processo pai acumula os cálculos das partes em, MPI_Recv(&dot, .....)
- Comunicação: Envio do resultado dos filhos ao pai, em, MPI_Send(&mydot, ....)
- Mapeamento: MPI_Comm_rank, MPI_Comm_size, MPI_Init(&argc, &argv)

- c) Tempo Sequencial: 15504883 usec 
	- Case B:
	- 7921554 usec
	- SpeedUp(2) = 1,95
	
	- Case D:
	- 4161455 usec
	- SpeedUp(4) = 3,72
	
	O servidor lsc5 ficou off durante todo fim de semana :(

- Parte 2:

-a)
- O código está disponível neste repositório, [mpi_msg.c](mpi_msg.c)
- Para executar, deve-se passar o número inicial como argumento 
- Exemplo: mpiexec -np 15 mpi_msg 0 , onde 0 é o numero inicial

b)
- Bastava trocar as linhas onde dizia tag = rank, para tag = 0.
- O código corrigido se encontra nesta pasta.[mpi_corrigido1.c](mpi_corrigido1.c)

c)
- O código não continha MPI_Finalize, por isso não funcionava adequadamente.
- Após inserido, funciona normalmente.
- O código esta nesta pasta.[mpi_corrigido2.c](mpi_corrigido_2.c)


