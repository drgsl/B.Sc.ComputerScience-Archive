import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientThread extends Thread {
    private Socket socket = null;
    private final NetworkServer server;

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
                String response = "The request is:  " + request;
                System.out.println("Server received the request..." + request);
                if (request.equals("stop")) {
                    System.out.println("Server stopped");
                    try {
                        in.close();
                        out.close();
                        socket.close();
                        break;
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }

                out.println(response);
                out.flush();
            }
        } catch (IOException e) {
            System.err.println("Communication error... " + e);
        }

    }
}
