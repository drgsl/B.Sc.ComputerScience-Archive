import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Scanner;

public class NetworkClient {

    private static PrintWriter out;
    private final static String SERVER_ADDRESS = "127.0.0.1"; // The server's IP address
    private static BufferedReader in;
    private final static int PORT = 9090;

    /**
     * making the client available and waiting commands
     *
     * @param args -
     * @throws IOException exception
     */
    public static void main(String[] args) throws IOException {
        NetworkClient client = new NetworkClient();
        Socket socket = new Socket(SERVER_ADDRESS, PORT);
        try {
            out = new PrintWriter(socket.getOutputStream());
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            while (true) {
                String request = client.readCommandFromKeyboard();
                if (request.equals("exit")) {
                    client.sendRequest(request);
                    in.close();
                    out.close();
                    socket.close();
                    break;
                } else {
                    client.sendRequest(request);
                }
            }
            System.out.println("Client stopped");
        } catch (UnknownHostException e) {
            System.err.println("No server listening... " + e);
        }

    }

    /**
     * this method reads the commands from keyboard on the client-side
     *
     * @return next line
     */
    private String readCommandFromKeyboard() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextLine();
    }

    /**
     * this method sends the request from the client to the server
     *
     * @param request request made from the client-side
     * @throws IOException exception
     */
    private void sendRequest(String request) throws IOException {
        try {
            out.println(request);
            out.flush();
            request = in.readLine();
            System.out.println("Client: " + request);
        } catch (SocketException e) {
            System.out.println("Eroare.");
        }
    }

}