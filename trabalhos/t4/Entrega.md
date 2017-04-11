Aluno: Jhillian Bianchi
Mat:201310739

ELC139 - Programação Paralela
Prof. Andrea Schwertner Charão

1 - Identificadores de threads e tempo total então errados. O bug do programa é por conta de uma não definição de escopo das variáveis TID e TOTAL. Por default, o OpenMP trata estes atributos como "shared", mas como desejamos um para cada thread que está executando, precisamos defini-los como private. Antes de fazermos essa mudança, acabava que os identificadores se confundiam.
Obs adicional:Mantendo o parâmetro do schedule como dynamic, alguns tempos das threads dão 0, não entendi o porque disso acontecer. O código corrigido segue também neste repositório.

Referências:

-http://www.roe.ac.uk/ifa/postgrad/pedagogy/2009_kiessling.pdf
