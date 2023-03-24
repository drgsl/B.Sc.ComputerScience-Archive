package game;

import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

public abstract class Player implements Runnable {
    final String name;

    final GameManager gameManager;

    final List<Token> tokenList;

    double score;

    public Player(String name, GameManager gameManager) {
        this.name = name;
        this.gameManager = gameManager;
        tokenList = new LinkedList<>();
        this.score = 0;
    }

    @Override
    public void run() {
        while (!gameManager.isGameFinished()) {
            // Lock the game
            /*
            [NOTE] This part was implemented for the compulsory.

            synchronized (gameManager)
            {
                getTokenFromBoard();
            }

            try {
                // Sleep between 100ms and 300ms
                Thread.sleep((long) (Math.random() * 200 + 100));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            */
            synchronized (gameManager) {
                if (gameManager.timeUp || gameManager.isGameFinished()) {
                    return;
                }
                while (gameManager.isBoardIsOccupied()) {
                    try {
                        // Make the current thread wait for an opportunity
                        gameManager.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                gameManager.occupyBoard();
                getTokenFromBoard();
                gameManager.releaseBoard();
                // Notify all threads waiting for the gameManager that he is available
                gameManager.notifyAll();
            }

            try {
                // Sleep between 100ms and 300ms
                Thread.sleep((long) (Math.random() * 200 + 100));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    abstract void getTokenFromBoard();

    public void printScore() {
        System.out.println("Player " + name + " has a score of " + score + ".");
    }

    public String getName() {
        return name;
    }

    public double getScore() {
        return score;
    }
}
