package game;

/**
 * Daemon class used for time keeping of a game.
 */
public class Timekeeper extends Thread {

    // Time allocated in seconds
    int timeToExist;

    public Timekeeper(int timeInSeconds) {
        this.timeToExist = timeInSeconds;
    }

    @Override
    public void run() {
        while (timeToExist > 0) {
            try {
                Thread.sleep(1000);
                timeToExist--;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // System.out.println("timekeeper over");
    }

    public boolean isOver() {
        return timeToExist <= 0;
    }
}
