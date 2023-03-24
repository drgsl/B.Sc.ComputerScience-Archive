public class Router extends Node implements Identifiable{
    int ipAddr;

    /**
     * constructor
     * @param name
     * @param macAddr
     * @param location
     * @param ipAddr
     */
    public Router(String name, String macAddr, String location, int ipAddr) {
        super(name, macAddr, location);
        this.ipAddr = ipAddr;
    }

    /**
     * getter
     * @return
     */
    @Override
    public int getIP() {
        return ipAddr;
    }

    /**
     * overrdie
     * @return
     */
    @Override
    public String toString() {
        return "Router{" +
                "name='" + name + '\'' +
                ", location='" + location + '\'' +
                ", cost=" + cost +
                '}' + '\n';
    }
}
