package game;

import java.util.Scanner;

public class GameShell {

    private GameManager gameManager;
    private Timekeeper timekeeper;

    public GameShell(int maxSecondsToLast) {
        timekeeper = new Timekeeper(maxSecondsToLast);
    }

    private void setupGame() {
        Scanner scanner = new Scanner(System.in);

        int numberOfTokens;
        int n;
        double minScore, maxScore;


        System.out.print("Number of tokens: ");
        numberOfTokens = scanner.nextInt();

        System.out.print("The number N: ");
        n = scanner.nextInt();

        System.out.print("The minimum score for a token: ");
        minScore = scanner.nextInt();

        System.out.print("The maximum score for a token: ");
        maxScore = scanner.nextInt();

        gameManager = new GameManager(numberOfTokens, n, minScore, maxScore);

        System.out.print("Number of computer bots: ");
        int numberOfPlayers = scanner.nextInt();
        String name;
        for (int i = 1; i <= numberOfPlayers; i++) {
            System.out.print("Player " + i + ": ");
            name = scanner.next();
            gameManager.addPlayer(new ComputerPlayer(name, gameManager));
        }
    }

    public void setupGameWithHuman() {
        System.out.println("Hello and welcome to the TSP Game! You will play against a very powerful AI. Input the starting conditions:");
        setupGame();

        gameManager.addPlayer(new HumanPlayer("Adi", gameManager));
    }

    public void setupGameWithBotsOnly() {
        System.out.println("Hello and welcome to the TSP Game (BOTS ONLY)! Input the starting conditions:");
        setupGame();
    }

    public void startGame() {
        Thread[] toDo = new Thread[2];
        toDo[0] = new Thread(gameManager);
        toDo[1] = new Thread(timekeeper);

        toDo[0].start();
        toDo[1].start();

        while (!timekeeper.isOver() && !gameManager.isGameFinished()) {
            try {
                Thread.sleep(1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        gameManager.timeUp = timekeeper.isOver();
    }

}
