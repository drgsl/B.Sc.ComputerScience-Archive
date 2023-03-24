/**
 * interface for storage
 */
public interface Storage {
    public void getStorage();

    /**
     * function to convert from GB to MB/KB/BYTES
     * @param changeTo
     * @param value
     * @return
     */
    default long convertGbTo(String changeTo, int value){
        if (changeTo.equals("MB")) {
            return value*1024L;
        }
        if (changeTo.equals("KB")) {
            return value*1048576L;
        }
        if (changeTo.equals("B")) {
            return value*1073741824L;
        }
        System.out.println("string not accepted(must be MB, KB or B");
        return -1;
    }
}
