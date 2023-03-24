import java.util.ArrayList;
import java.util.List;

public class Person {
    private String name = null;
    private List<Person> friends = null;

    private List<String> messages = null;

    public Person(String name) {
        this.name = name;
        this.friends = new ArrayList<>();
        this.messages = new ArrayList<>();
    }

    /**
     * this method adds a person in the friend list
     *
     * @param person an object of type Person
     */
    public void addFriend(Person person) {
        friends.add(person);
    }

    /**
     * this method returns the list of friends for a specific person
     *
     * @return list of Person
     */
    public List<Person> getFriends() {
        return friends;
    }

    /**
     * this method adds a message to inbox
     *
     * @param message String
     */
    public void addMessage(String message) {
        this.messages.add(message);
    }

    /**
     * this method returns all messages that a Person have
     *
     * @return list of String
     */
    public List<String> getMessages() {
        return messages;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                '}';
    }
}
