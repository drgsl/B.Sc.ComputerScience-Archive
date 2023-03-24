import java.io.PrintStream;
import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
 * network class
 */
public class Network {
    private LinkedList<Node> nodes = new LinkedList<Node>();

    /**
     * adds a new node to the linkedList
     * @param node
     */
    public void add(Node node){
        this.nodes.add(node);
    }

    /**
     * override
     * @return
     */
    @Override
    public String toString() {
        return "Network{" +
                "nodes=\n" + nodes +
                '}';
    }

    /**
     * a method to display the nodes that are identifiable, sorted by their addresses.
     */
    public void displayIdentifiableNodes(){
        System.out.println("");
        System.out.println("");
        System.out.println("");
        System.out.println("Identifiable nodes:");


        LinkedList<Identifiable> temp = new LinkedList();
        Iterator var2 = this.nodes.iterator();

        while(var2.hasNext()) {
            Node l = (Node)var2.next();
            if (l instanceof Identifiable && !(l instanceof Storage)) {
                temp.add((Identifiable)l);
            }
        }

        System.out.println("--------------Before sorting: ");
        var2 = temp.iterator();

        PrintStream var10000;
        String var10001;
        Identifiable l;
        while(var2.hasNext()) {
            l = (Identifiable) var2.next();
            var10000 = System.out;
            var10001 = ((Node)l).getName();
            var10000.println(var10001 + " (open hours: " + l.getIP() + ")");
        }

        System.out.println("\n\n--------------After sorting: ");
        temp.sort(new Comparator<Identifiable>() {
            public int compare(Identifiable location1, Identifiable location2) {
                if (location1.getIP() < (location2.getIP())) {
                    return -1;
                } else {
                    return location1.getIP() < (location2.getIP()) ? 1 : 0;
                }
            }
        });
        var2 = temp.iterator();

        while(var2.hasNext()) {
            l = (Identifiable) var2.next();
            var10000 = System.out;
            var10001 = ((Node)l).getName();
            var10000.println(var10001 + " (ip: " + l.getIP() + ")");
        }
    }


}
