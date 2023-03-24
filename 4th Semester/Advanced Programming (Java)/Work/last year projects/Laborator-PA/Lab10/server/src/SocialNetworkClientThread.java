import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.*;

public class SocialNetworkClientThread extends Thread{
    private final Socket socket;
    private BufferedReader input;

    public SocialNetworkClientThread(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        try {
            // Read the information coming into the socket from the client
            input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter output = new PrintWriter(socket.getOutputStream());

            // Read the request and send a response UNTIL THE CLIENT CLOSES THE CONNECTION
            do {
                String request = input.readLine();
                // Logica serverului
                String response = request + " hello word!";
                output.println(response);
                output.flush();

                sendResponse();
            } while (!socket.isClosed());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void sendResponse() throws IOException {
        String request = input.readLine();
        // System.out.println("Read request '" + request + "'");
        if (request == null) {
            return;
        }
        // Create a PrintWriter for writing information from the server to the client
        PrintWriter output = new PrintWriter(socket.getOutputStream());

        switch (request) {
            case "register" -> {
                String name = input.readLine();

                // register the name

               output.println("registration-successful");
            }
            case "login" -> {
                String name = input.readLine();

                // check if the name exists and return the response
                output.println("login-successful");
            }
            case "friend" -> {
                // check to see if the client is logged in, then execute

                String name = null;
                while ((name = input.readLine()) != null) {
                    // add the name to the friend list IF AND ONLY IF it exists;
                    System.out.println("added friend " + name + " to the list of friends");
                }
                output.println("friend-successful");
            }
            case "message" -> {
                String name = null;
                while ((name = input.readLine()) != null) {
                    // Verify that the friend exists!
                    System.out.println("Sent a message to friend " + name);
                }
                output.println("message-successful");
            }
            case "read" -> {
                String messsage = null;
                // Get each message based on the user's name
                // connectedUser.getMessageAtIndex(i);
                output.println("read-successful");
            }
            case "stop" -> {
                output.println("server-stop");
                output.close();
                output.flush();
                System.out.println("Connection terminated!");
                System.exit(0);
            }
            default -> {
                output.println("bad-request");
            }
        }
        output.flush();
    }
}
