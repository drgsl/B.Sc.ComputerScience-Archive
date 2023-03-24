import java.util.Arrays;
import java.util.LinkedList;
import java.util.stream.IntStream;

public class Main {
    public static void main(String[] args){

        LinkedList<Street> streets = new LinkedList<Street>();

        var nodeArr = IntStream.rangeClosed(0,9)
                .mapToObj(i -> new Intersection("v" + i))
                .toArray(Intersection[]::new);

    }

}
