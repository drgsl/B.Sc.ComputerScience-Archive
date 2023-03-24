import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class NetworkServer {
    private static final int PORT = 9090;
    private static ServerSocket serverSocket = null;

    /**
     * creating the server and waiting for client connections
     *
     * @param args -
     * @throws IOException exception
     */
    public static void main(String[] args) throws IOException {
        NetworkServer server = new NetworkServer();
        try {
            serverSocket = new ServerSocket(PORT);
            while (true) {
                System.out.println("Waiting a client...");
                Socket socket = serverSocket.accept();
                new ClientThread(socket, server).start();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            server.stop();
        }
    }

    /**
     * this method will close the server socket, meaning that the server will not be available anymore
     *
     * @throws IOException exception
     */
    public void stop() throws IOException {
        serverSocket.close();
    }

    /**
     * this method can be used to retrieve input from the server-side if necessary
     *
     * @return next line
     */
    private String readFromKeyboard() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextLine();
    }
}
