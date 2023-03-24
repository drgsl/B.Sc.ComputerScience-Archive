package game;

public class ComputerPlayer extends Player {

    public ComputerPlayer(String name, GameManager gameManager) {
        super(name, gameManager);
    }

    @Override
    void getTokenFromBoard() {

        Token t = gameManager.getFirstAvailableToken();
        if (t != null) {
            tokenList.add(t);
            System.out.println("Player " + name + " extracted token (" + t.getFirstNumber() + ", " + t.getSecondNumber() + ")");
            this.score += t.getValue();
        }
        else {
            System.out.println("Player " + name + " extracted a null token");
        }
    }
}
