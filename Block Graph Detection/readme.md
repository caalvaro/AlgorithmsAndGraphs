### Estrutura do projeto:
Para desenvolver o trabalho, me baseei nas implementações em Java passadas em
aula. Fiz diversas mudanças, como a eliminação da Classe Digraph, já que só são
necessários os métodos para os grafos não direcionados, e adicionei todos os métodos
necessários para a identificação do Grafo Bloco.
Funcionamento do algoritmo:

1. Detecta as Componentes Biconexas do Grafo de entrada
2. Cria um novo Grafo para cada Componente Biconexa
3. Adiciona cada Componente Biconexa encontrada numa lista
4. Percorre a lista e verifica se cada Componente Biconexa é um grafo completo

A corretude do algoritmo foi baseada na caracterização de Grafo Bloco passada na
descrição do trabalho: “Um grafo bloco é aquele em que toda componente biconexa é uma
clique.”

### Validação da entrada:
Além de implementar o algoritmo, fiz uma sequência de validações para ter certeza
que o arquivo passado está no formato esperado pelo programa, retornando ao usuário a
qual foi o problema e em qual linha ele ocorreu. São elas:

	● Verifica se é um grafo não direcionado
	● Verifica se há um vértice que foi definido duas vezes
	● Verifica se há arestas repetidas
	● Verifica se a linha está no formato necessário ([NUM] = [NUM] …)
	● Verifica se há um auto-loop
	● Verifica se algum vértice tem um vizinho que não foi definido
	
### Saída do programa:
Após analisar o Grafo, o programa imprime se ele é um grafo bloco ou não e
imprime todas as Componentes Biconexas enumeradas.
Se não for um grafo bloco, ele indica quais são as Componentes Biconexas que
não são cliques através do número de cada uma na impressão.

### Referências:
Para testar o funcionamento do programa, foram usados os exemplos de Grafo Bloco
encontrados na wikipédia nos seguintes artigos:

1. Canadian Mathematical Bulletin , Volume 6 , Issue 1 , January 1963 , pp. 1 - 6. DOI:
https://doi.org/10.4153/CMB-1963-001-x
2. MARKENZON, L.; WAGA, C. F. E. M. . Characterizing Block Graphs in Terms of
One-vertex Extensions. TENDÊNCIAS EM MATEMÁTICA APLICADA E
COMPUTACIONAL, v. 20, p. 323-330, 2019. DOI:
https://doi.org/10.5540/tema.2019.020.02.323
3. https://en.wikipedia.org/wiki/Block_graph, acesso em 4 de junho de 2021.
