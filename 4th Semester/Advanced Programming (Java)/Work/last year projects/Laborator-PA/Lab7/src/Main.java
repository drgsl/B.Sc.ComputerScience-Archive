
import game.GameShell;
import game.HumanPlayer;


public class Main {

    public static void main(String[] args) {
        GameShell gameShell = new GameShell(1);
        gameShell.setupGameWithBotsOnly();
        gameShell.startGame();
    }
}
