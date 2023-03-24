import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class SocialNetworkClient {
    private final String serverAddress;
    private final int PORT;

    private Socket socket;

    // For responses coming from the server
    BufferedReader input;

    public SocialNetworkClient(String serverAddress, int PORT) {
        this.serverAddress = serverAddress;
        this.PORT = PORT;
    }

    public void connect() throws IOException {
        socket = new Socket(serverAddress, PORT);

        PrintWriter output = new PrintWriter(socket.getOutputStream());
        input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        String request = null;
        BufferedReader consoleInput = new BufferedReader(new InputStreamReader(System.in));

        welcomeMessage();
        do {
            System.out.print("Input command: ");
            request = consoleInput.readLine();
            // System.out.println("Read the request: '" + request + "'");

            // Send the request to the server
            output.println(request);
            output.flush();

            // Wait for the response
            getResponse();
        } while (!request.equals("stop"));
    }

    private void welcomeMessage() {
        System.out.println("---------------------------------------------------------------");
        System.out.println("\nHello and welcome to the FaceJava social network!\n");
        System.out.println("---------------------------------------------------------------");
    }

    private void getResponse() throws IOException {
        String response = input.readLine();
        System.out.println("Server response: '" + response + "'!");
    }
}
