package game;

import java.util.Scanner;

public class HumanPlayer extends Player {

    public HumanPlayer(String name, GameManager gameManager) {
        super(name, gameManager);
    }

    @Override
    void getTokenFromBoard() {
        Token t;
        Scanner s = new Scanner(System.in);

        gameManager.displayAvailableTokens();

        System.out.print("Selected the index (from available ones): ");
        int index = s.nextInt();
        t = gameManager.getTokenAtIndex(index);

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
