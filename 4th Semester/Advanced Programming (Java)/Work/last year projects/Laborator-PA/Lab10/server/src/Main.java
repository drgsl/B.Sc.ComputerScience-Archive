import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        try {
            SocialNetworkServer s = new SocialNetworkServer();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
