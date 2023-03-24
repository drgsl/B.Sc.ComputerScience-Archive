public class Computer extends Node implements Identifiable, Storage{
    private String ipAddr;
    private float storage;

    /**
     * constructor
     * @param name
     * @param macAddr
     * @param location
     * @param ipAddr
     * @param storage
     */
    public Computer(String name, String macAddr, String location, String ipAddr, float storage) {
        super(name, macAddr, location);
        this.ipAddr = ipAddr;
        this.storage = storage;
    }

    /**
     * getter
     * @return
     */
    @Override
    public int getIP() {
        return 1234;
    }

    /**
     * getter
     */
    @Override
    public void getStorage() {

    }

    /**
     * override
     * @return
     */
    @Override
    public String toString() {
        return "Computer{" +
                "location='" + location + '\'' +
                ", cost=" + cost +
                '}' + '\n';
    }
}
