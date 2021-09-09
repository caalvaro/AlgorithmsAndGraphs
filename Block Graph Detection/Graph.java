import java.util.Stack;
import java.util.regex.Pattern;
import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayList;
import java.io.FileReader;
import java.io.BufferedReader;

public class Graph {
    private Stack<Vertex> stack; // pilha usada na detecção de componentes biconexas
    public ArrayList<Graph> biconnectedComponents; // lista de componentes biconexas do grafos
    private HashMap< Integer, Vertex> vertexSet;
    private int time;
    private Integer lineId; // guarda  número da linha do arquivo para retornar um erro

    public Graph() {
        this.vertexSet = new HashMap<>();
        this.biconnectedComponents = new ArrayList<>();
        this.lineId = 1;
    }

    private void addVertex( int id ) {
        if ( id >= 1 && !this.vertexSet.containsKey( id ) ) {
            Vertex v = new Vertex( id );
            this.vertexSet.put( v.id, v );
        }
    }

    private void addArc( Integer vertex1Id, Integer vertex2Id ) {
        Vertex vertex1 = this.vertexSet.get( vertex1Id );
        Vertex vertex2 = this.vertexSet.get( vertex2Id );

        if ( vertex1 == null || vertex2 == null ) {
            System.out.printf("Vértice inexistente!\n");
            return;
        }

        // verifica auto-loop
        if ( vertex1.id == vertex2.id ) {
            this.error("O grafo não pode ter um auto-loop");
        }

        // só adiciona uma nova aresta se ela não existir
        if (!vertex1.isNeighbor( vertex2.id )){
            vertex1.addNeighbor( vertex2 );
        } else {
            this.error("Aresta "+vertex1.id+"-"+vertex2.id+" já existe.");
        }
    }

    private void addEdge( Integer v1, Integer v2 ) {
        this.addVertex( v1 );
        this.addVertex( v2 );
        this.addArc( v1, v2 );
        this.addArc( v2, v1 );
    }

    public void print() {
        for( Vertex v : vertexSet.values() )
            v.print();
    }

    private Boolean isComplete() {
        for ( Vertex v1 : this.vertexSet.values() ) {
            if ( v1.degree() != (this.vertexSet.size() - 1) ) {
                return false;
            }
        }

        return true;
    }

    private void isUndirected() {
        for( Vertex v1 : vertexSet.values()) {
            for( Vertex v2 : v1.nbhood.values()) {
                if ( v2.nbhood.get(v1.id) == null ) {
                    this.error("O grafo precisa ser não direcionado.\nO vértice "+v1.id+" aponta para o vértice "+v2.id+" mas o contrário não ocorre.\n");
                }
            }
        }
    }

    public Boolean isBlockGraph() {
        Integer i = 1;
        Boolean isBlock = true;
        ArrayList<Integer> notClique = new ArrayList<>();

        for ( Graph biconnectedComponent : this.biconnectedComponents ) {
            if ( !biconnectedComponent.isComplete() ) {
                notClique.add(i++);

                isBlock = false;
            }
        }

        if ( isBlock ) {
            System.out.println("\n\n--- RESULTADO: O grafo passado é um grafo bloco!\nTodas as componentes biconexas são cliques.");
        } else {
            System.out.printf("\n\n--- RESULTADO: O grafo passado NÃO é um grafo bloco.\nAs componentes biconexas: %s não são cliques.", notClique.toString());
        }

        this.printBiconnectedComponents();

        return isBlock;
    }

    public void biconnectedComponents( ) {
        Graph biconnectedComponent = new Graph(); // cria um grafo pra armazenar a componente biconexa

        for( Vertex vertex : this.vertexSet.values( ) ) {
            if( vertex.d == null ) {
                this.stack = new Stack<Vertex>( );
                this.biconnectedComponentVisit( vertex );
            }

            // se a pilha não está vazia é porque há uma componente biconexa lá
            if ( !this.stack.empty( ) ) {
                biconnectedComponent = new Graph();
                // adiciona a componente biconexa na lista
                this.biconnectedComponents.add(biconnectedComponent);
            }

            // preenche a componente com o que tem na pilha
            while ( !this.stack.empty( ) ) {
                Vertex v2 = this.stack.pop( );
                Vertex v1 = this.stack.pop( );

                // adiciona a aresta na componente biconexa
                biconnectedComponent.addEdge( v1.id, v2.id );
            }
        }
    }

    private void biconnectedComponentVisit( Vertex v1 ) {
        v1.d = ++this.time;
        v1.low = v1.d;

        // percorre os vizinhos de v1
        for( Vertex neig : v1.nbhood.values( ) ) {
            if( neig.d == null ) { // se não foi descoberto
                this.stack.push( v1 ); this.stack.push( neig ); // adiciona a aresta de árvore
                
                neig.parent = v1;
                this.biconnectedComponentVisit( neig );
                
                if( neig.low < v1.low ) {
                    v1.low = neig.low;
                }
                
                if( neig.low >= v1.d ) // componente biconexa detectada
                    this.createBiconnectedComponent( v1, neig );
            }
            else if( neig != v1.parent ) {
                if( neig.d < v1.d ) {  // se é aresta de retorno
                    this.stack.push( v1 ); this.stack.push( neig ); // adiciona a aresta na pilha

                    if( neig.d < v1.low ){
                        v1.low = neig.d;
                    }
                }
                // else aresta já explorada
            }
        }
    }

    private void createBiconnectedComponent( Vertex cutVertex, Vertex auxiliarVertex ) {
        Graph biconnectedComponent = new Graph(); // cria um grafo para armazenar a componente biconexa
        Vertex vextex1, vextex2;

        // adiciona a componente biconexa na lista
        this.biconnectedComponents.add(biconnectedComponent);

        vextex2 = this.stack.pop( );
        vextex1 = this.stack.pop( );

        // preenche a componente com o que tem na pilha
        while( vextex1 != cutVertex || vextex2 != auxiliarVertex ) {
            if( this.stack.empty( ) )
                return;

            // adiciona a aresta na componente biconexa
            biconnectedComponent.addEdge( vextex1.id, vextex2.id ); 

            vextex2 = this.stack.pop( );
            vextex1 = this.stack.pop( );
        }

        // adiciona a aresta na componente biconexa
        biconnectedComponent.addEdge( vextex1.id, vextex2.id );
    }

    public void printBiconnectedComponents() {
        int i = 1;
        System.out.println("\n\n-------- Componentes Biconexas: --------");   

        // imprime cada componente biconexa
        for ( Graph biconnectedComponent : this.biconnectedComponents ) {
            System.out.printf("+ Componente %d:\n", i++);
            biconnectedComponent.print();
            System.out.println();
        }
    }

    public void readGraphFromFile( String fileName ) {
        String thisLine = null;
        String pieces[];

        try {
            FileReader fileReader = new FileReader( fileName );
            BufferedReader bufferedReader = new BufferedReader( fileReader );
            HashSet<Integer> definedVertices = new HashSet<>(); // vértices já definidos para evitar repetição
            Integer vextex1Id, vextex2Id;

            while ( (thisLine = bufferedReader.readLine( )) != null ) {
                // retira excessos de espaços em branco
                thisLine = thisLine.replaceAll("\\s+", " ").trim();

                // verififica se a linha está no formato necessário
                if (!Pattern.matches("[1-9][0-9]*+\\s+=(\\s+[1-9][0-9]*)*", thisLine)) {
                    this.error("A entrada precisa ser no formato '[VÉRTICE] = [VIZINHO] [VIZINHO] ...' Exemplo: 1 = 4 6 2.\n");
                }

                pieces = thisLine.split(" ");

                vextex1Id = Integer.parseInt( pieces[0] );

                // verifica se o vértice já foi definido
                if (definedVertices.contains( vextex1Id )) {
                    this.error("Vértice "+vextex1Id+" já foi definido.\n");
                } else {
                    definedVertices.add( vextex1Id );
                }

                this.addVertex( vextex1Id );

                for( int i = 2; i < pieces.length; i++ ) {
                    vextex2Id = Integer.parseInt( pieces[i] );

                    this.addVertex( vextex2Id );
                    this.addArc( vextex1Id, vextex2Id );
                }

                lineId++;
            }
            this.lineId = null;
            bufferedReader.close();

            // verifica se existe algum vértice que foi mencionado mas não definido
            if( definedVertices.size() != this.vertexSet.size() ){
                for (Vertex vertex : vertexSet.values()) {
                    if(!definedVertices.contains(vertex.id)) {
                        this.error("O vértice "+vertex.id+" não foi definido.");
                    }
                }
            }

            // verifica se o grafo é não direcionado
            this.isUndirected();
        } catch(Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    private void error(String text) {
        if(this.lineId == null)
            System.out.printf("ERRO: %s\n", text);
        else System.out.printf("ERRO (linha %d): %s\n", this.lineId, text);
        
        
        System.exit(1);
    }
}
