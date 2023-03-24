package game;

/**
 * Class representing a token from the game. Each token is must have:
 * - a pair of two positive numbers between 1 and the total number of tokens
 * - a positive score associated with it
 * - if it is available or not
 */
public final class Token {
    private final int firstNumber;
    private final int secondNumber;
    private final double value;

    private boolean available = true;

    public Token(int firstNumber, int secondNumber, double value) {
        this.firstNumber = firstNumber;
        this.secondNumber = secondNumber;
        this.value = value;
    }

    public int getFirstNumber() {
        return firstNumber;
    }

    public int getSecondNumber() {
        return secondNumber;
    }

    public double getValue() {
        return value;
    }

    public boolean isAvailable() {
        return available;
    }

    public void markAsUnavailable() {
        this.available = false;
    }

    @Override
    public String toString() {
        return "Token : (" + firstNumber + ", " + secondNumber + "). Score : " + value;
    }
}
