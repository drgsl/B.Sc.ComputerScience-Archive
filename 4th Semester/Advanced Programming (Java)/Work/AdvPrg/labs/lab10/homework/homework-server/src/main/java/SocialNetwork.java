import java.util.ArrayList;
import java.util.List;

public class SocialNetwork {
    private static final List<Person> personsList = new ArrayList<>();

    /**
     * this method adds a persion into a Network
     *
     * @param person object of type Person
     */
    public static void addPersonToNetwork(Person person) {
        personsList.add(person);
    }

    /**
     * this method returns the entire Network
     *
     * @return list of Person
     */
    public static List<Person> getNetwork() {
        return personsList;
    }
}
