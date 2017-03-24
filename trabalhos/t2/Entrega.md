ELC139 - Programação Paralela

Professora: Andrea Schwertner Charão

Aluno: Jhillian Bianchi - Mat:201310739




Sumário


1- Parte 1

	1.1 Dificuldades e Curiosidades
	
	1.2 Respostas das questões

	1.3 Screenshots relevantes

2- Parte 2
	
	2.1 O profiler Valgrind/Callgrind	
	
	2.2 Curiosidades
	
	2.3 Screenshots relevantes





1- A primeira parte consistia basicamente em executar o profiler gprof sobre o programa "dotprod_seq", que calcula produto escalar entre vetores. No meu caso, não foi possível utilizar o gprof, mas utilizei-me do Valgrind/Callgrind para responder as questões.



1.1 - Curiosamente, o gprof não executou da forma como era esperado. Até funcionava para gerar o arquivo "gmon.out", porém parecia que não conseguia ler o mesmo. Foi discutido tal assunto em aula, e assim imagino que a versão do Ubuntu que estou usando (16.10) não é compatível com o gprof versão 2.27 e/ou gcc versão 6.2.0. Tirando essa dificuldade com o gprof, tudo ocorreu na normalidade.


1.2 - a) Embora altere pouco, o perfil se modifica principalmente no tempo em que é gasto com cada função. A função dot_product é a que mais usa o tempo, e a porcentagem aumenta proporcionalmente ao tamanho da entrada.

b) Como a função dot_product é a que mais ocupa o tempo, cerca de 90%, ela é a principal candidata a paralelização.


1.3 Observar os arquivos Perfil_dotprod_entrada_pequena.png e Perfil_dotprod_entrada_grande.png, que contém a visualização do profiler, localizados na pasta Screenshots. Os arquivos completos também estão disponíveis na pasta de cada programa. Uma outra curiosidade é o número de vezes que a função "strcmp" foi chamada em uma das execuções. Em um dos screenshots está marcado o número de vezes.





Parte 2 - O objetivo da segunda parte era analisar um outro programa com os profilers. Novamente utilizei o Valgrind/Callgrind, em um programa simples de cálculo de fatorial, com uma entrada que pode ser variada e repetida várias vezes para gerar um maior tempo. Apenas um detalhe sobre o programa, como o fatorial geralmente resulta em um número gigante, muitas vezes estoura o máximo valor do tipo de dado, então o resultado dá 0, mas as computações são todas realizadas.


2.1 - O Valgrind/Callgrind é um profiler mais visual que o gprof. Tem uma pequena e simples interface, mas que facilita bastante a visão das principais informações.

Pode ser obtido com o comando:


sudo apt-get install valgrind kcachegrind graphviz


Para executá-lo, basta seguir o exemplo, no caso, do fatorial:


valgrind --tool=callgrind ./fatorial 30000 1000


Vale lembrar, o primeiro parâmetro do fatorial é o número a ser calculado e o segundo o número de repetições.


2.2 - Há uma curiosidade sobre o valgrind/callgrind. Talvez por ser uma execução com recursividade, ele apresenta duas funções: fatorial e fatorial'2. Como a segunda usa muito mais o tempo e pelo número de vezes que é chamada, creio que ela corresponda as chamadas recursivas, enquanto a "fatorial", que é chamada exatamente o número de repetições que é passado, seja a função principal que aguarda para retornar o resultado. Não sei se esse raciocínio é correto, mas achei curioso...


2.3



 - Observar os arquivos Fatorial_100repeticoes.png e Fatorial1000_repeticoes.png. Atentar para o número de chamadas de cada função, fatorial e fatorial'2.


Referências

-Ajudas com o valgrind:
http://valgrind.org/docs/manual/cl-manual.html
http://gernotklingler.com/blog/gprof-valgrind-gperftools-evaluation-tools-application-level-cpu-profiling-linux/
