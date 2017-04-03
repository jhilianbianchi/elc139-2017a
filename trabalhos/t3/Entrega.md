Aluno: Jhillian Bianchi
Mat:201310739

ELC139 - Programação Paralela
Prof. Andrea Schwertner Charão

Parte 1 - 

1- 
Particionamento:
O particionamento está presente na rotina da thread, que são os principais alvos de paralelização do código. Em pthreads_dotprod.c, por exemplo, cada multiplicação a[i] * b[i] é uma candidata a paralelização.

Comunicação: Representa as "dependências" do programa a ser paralelizado. Em pthreads_dotprod.c, por exemplo, sabe-se que o cálculo de uma multiplicação necessita de dois valores e ainda, o cálculo das somas depende dessas multiplicações. 

Aglomeração: Representa o agrupamento entre operações semelhantes a fim de obter vantagem. Em pthreads_dotprod.c, o agrupamento de várias somas para produzir somas parciais.

   mysum = 0.0;
   for (i = start; i < end ; i++)  {
         mysum += (a[i] * b[i]);
   }

Mapeamento: Faz balanceamento de carga entre as threads, para que todas tem carga igualitária de trabalho. Em pthreads_dotprod.c, é representado pela função "void dotprod_threads(int nthreads)"


2- Uma thread 7294401 usec, com duas threads 4032875 usec.

Dessa forma, temos uma redução de tempo na ordem de 3261526 usec com o uso de duas threads, ou seja, uma aceleração de 55,28%

3- A aceleração não se mantem. Já apartir de 4 threads, a redução não se torna mais significativa. vide tabela abaixo:

threads		Elementos	Tempo(usec)
1		1000000		7294401
2		 500000		4032875
4		 250000		3316736
8		 125000		3319236
16		  62500		3281297

4- 

threads		Elementos	Tempo(usec)	aceleração
1		1000000		7294401		  -
2		 500000		4032875		55,28%
4		 250000		3316736		17,75%
8		 125000		3319236		-0,07%
16		  62500		3281297		1,14%

5- O programa pthreads_dotprod.c utiliza de mutexes, que são controladores de acesso a regiões críticas do programa. O programa pthreads_dotprod2.c não faz uso deste controlador e essa é a diferença. O segundo, com duas linhas a menos, não está correto. Até pode funcionar em alguns casos, mas pode falhar se duas ou mais threads conseguirem obter o mesmo recurso ao mesmo tempo.
Ex: O valor armazenado é 3. A thread 1 pega 3 e vai somar 5. Antes que a thread 1 some, a thread 2 também pega o valor 3 e por sua vez vai somar 10. Assim, o valor que era pra ser 18 acaba ficando com 13, pois a primeira soma vai ser ignorada. 



Parte 2- 


