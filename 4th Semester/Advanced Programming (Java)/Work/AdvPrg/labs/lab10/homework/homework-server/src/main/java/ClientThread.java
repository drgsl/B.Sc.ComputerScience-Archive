import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientThread extends Thread {
    private Socket socket = null;
    private Person person = null;
    private final NetworkServer server;

    private long start = System.currentTimeMillis();
    private long end = start + 30 * 1000; // 30 seconds›

    ClientThread(Socket socket, NetworkServer server) {
        this.socket = socket;
        this.server = server;
    }

    private PrintWriter out;

    /**
     * this method is used for running a connection thread
     */
    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new PrintWriter(socket.getOutputStream()); //server -> client stream
            while (true) {
                String request = in.readLine();
                if (request == null)
                    break;
                if (System.currentTimeMillis() > end) {
                    try {
                        out.println("A trecut prea mult timp de la ultima comanda. S-a inchis socket-ul.");
                        System.out.println("A trecut prea mult timp de la ultima comanda. S-a inchis socket-ul.");
                        in.close();
                        out.close();
                        socket.close();
                        break;
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                } else {
                    System.out.println("Testele continua");
                }
                String response = null;
                System.out.println("Server received the request..." + request);
                if (request.equals("stop")) {
                    System.out.println("Server is will accept one more connection and the accept() method will be off.");
                    try {
                        NetworkServer.closeAcceptConnections();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                } else if (request.contains("register")) {
                    resetTimer();
                    boolean personAlreadyExists = false;
                    for (Person person : SocialNetwork.getNetwork()) {
                        if (person.getName().equals(request.substring(9))) {
                            response = "This name already exists in our Network.";
                            personAlreadyExists = true;
                        }
                    }
                    if (!personAlreadyExists) {
                        SocialNetwork.addPersonToNetwork(new Person(request.substring(9)));
                        response = "Register ok";
                    }
                } else if (request.contains("login")) {
                    resetTimer();
                    boolean connected = false;
                    for (Person person : SocialNetwork.getNetwork()) {
                        if (person.getName().equals(request.substring(6))) {
                            this.person = person;
                            response = ("Client connected as person: " + person.getName());
                            connected = true;
                        }
                    }
                    if (!connected) {
                        response = "Login failed. The account may not exist or something was wrong.";
                    }
                } else if (request.contains("friend")) {
                    resetTimer();
                    if (this.person != null) {
                        boolean personExists = false;
                        for (Person person : SocialNetwork.getNetwork()) {
                            if (person.getName().equals(request.substring(7))) {
                                response = "Person successfully added to friends list";
                                this.person.addFriend(person);
                                personExists = true;
                            }
                        }
                        if (!personExists) {
                            response = "The person requested is not registered in our Network";
                        }
                    } else {
                        response = "You should be logged for adding new friends";
                    }
                } else if (request.equals("displaymylist")) {
                    resetTimer();
                    System.out.println(this.person.getFriends());
                } else if (request.contains("send")) {
                    resetTimer();
                    String message = request.substring(5);
                    for (Person person : this.person.getFriends()) {
                        person.addMessage(message);
                    }
                    response = "Message successfully sent";
                } else if (request.contains("read")) {
                    resetTimer();
                    for (String message : this.person.getMessages()) {
                        response = message;
                        out.println(response);
                    }
                }
                if (response == null) {
                    response = "Nothing from server at this moment";
                }
                out.println(response);
                out.flush();
            }
        } catch (IOException e) {
            System.err.println("Communication error... " + e);
        }

    }

    private void resetTimer() {
        this.start = System.currentTimeMillis();
        this.end = this.start + 30 * 1000;
    }
}
