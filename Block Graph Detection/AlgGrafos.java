public class AlgGrafos {
    public static void main(String args[]) {
        Graph graph = new Graph();

        String fileName = "myfiles/grafo01.txt";
        // lê o grafo do arquivo especificado
        // faz todos os testes para verificar se o arquivo está no formato necessário
        graph.readGraphFromFile( fileName );
        
        // cria as componentes biconexas
        graph.biconnectedComponents();
     
        // verifica se é um grafo bloco
        graph.isBlockGraph();
    }
}
