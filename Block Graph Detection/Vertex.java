import java.util.HashMap;

public class Vertex {
    protected Integer id;
    // outgoing neighbors
    protected HashMap< Integer, Vertex> nbhood;
    protected Vertex parent, root;
    protected Integer d, f;
    // componentes conexas: menor tempo de descoberta alcançavel
    // por no máximo uma aresta de retorno entre os descendentes
    protected Integer low;

    public Vertex ( int id ) {
        this.id = id;
        this.nbhood = new HashMap<Integer,Vertex>();
        this.parent = null;
        this.d = null;
    }

    public void addNeighbor( Vertex viz ) {
        this.nbhood.putIfAbsent( viz.id, viz );
    }

    public boolean isNeighbor( Integer v2 ) {
        return this.nbhood.containsKey(v2);
    }
    
    public int degree() {
        return this.nbhood.size();
    }

    public void print() {
        int counter = 1;
        System.out.printf("Vértice %3d --> ", this.id);


        for( Vertex v : this.nbhood.values() ) {
            System.out.printf("%3d%s", v.id, counter == this.nbhood.size() ? " |" : ", " );
            counter++;
        }

        System.out.println();
    }
}
