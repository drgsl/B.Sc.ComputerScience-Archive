import java.util.HashMap;
import java.util.Map;

public class Node {
    protected String name;
    protected String macAddr;
    protected String location;
    protected Map<Node, Integer> cost = new HashMap<Node, Integer>();

    /**
     * constructor
     * @param name
     * @param macAddr
     * @param location
     */
    public Node(String name, String macAddr, String location) {
        this.name = name;
        this.macAddr = macAddr;
        this.location = location;
    }

    /**
     * getter
     * @return
     */
    public String getName() {
        return name;
    }

    /**
     * adds the cost from one node to another one
     * @param node
     * @param cost
     */
    public void addCost(Node node, Integer cost) {
        if (node == null) {
            System.out.println("Error! Node invalid! (null)");
        } else if (cost == null) {
            System.out.println("Error! Cost invalid! (null)");
        } else {
            this.cost.put(node, cost);
        }
    }

    /**
     * gets the cost from this node to another one
     * @param node
     * @return
     */
    public Integer getCostTo(Node node) {
        Integer temp = (Integer)this.cost.get(node);
        return temp == null ? -1 : temp;
    }

    /**
     * override
     * @return
     */
    @Override
    public String toString() {
        return "Node{" +
                "name='" + name + '\'' +
                ", location='" + location + '\'' +
                ", cost=" + cost +
                '}' + '\n';
    }
}
