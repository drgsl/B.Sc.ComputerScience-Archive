import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class SocialNetworkServer {
    public static final int PORT = 8100;

    public SocialNetworkServer() throws IOException {

        // Create a socket to listen to
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(PORT);
            while (true) {
                System.out.println("The server is waiting for connections");
                // Wait until a connection is made, then accept it.
                Socket socket = serverSocket.accept();
                new SocialNetworkClientThread(socket).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            assert serverSocket != null;
            serverSocket.close();
        }
    }

}
