package Lab1;
import java.util.ArrayList;

//adaug cuvantul si toti vecinii sai

public class Vecini {
    ArrayList<String> vec = new ArrayList<String>();
    String word;
    public void addNeighbour(String sir){
        vec.add(sir);
    }
    public void setWord(String sir){
        word=sir;
    }
    public void print(){
        System.out.print(word + ":");
        for(int i=0;i<vec.size();i++)
            System.out.print(vec.get(i) + " ");
        System.out.println();
    }
}
