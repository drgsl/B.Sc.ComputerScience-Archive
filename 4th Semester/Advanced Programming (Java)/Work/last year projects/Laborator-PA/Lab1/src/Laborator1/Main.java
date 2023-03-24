package Laborator1;

// Author: Peterca Adrian
public class Main {

    public static void main(String[] args)
    {
        System.out.println("Hello World!");

        String[] languageArray = {"C", "C++", "C#", "Python", "Go", "Rust", "JavaScript", "PHP", "Swift", "Java"};
        int n = (int) (Math.random() * 1_000_000);

        n *= 3;
        n += 0b10101;
        n += 0xFF;
        n *= 6;

        int result;
        do {
            result = 0;
            while (n > 0)
            {
                result += n % 10;
                n /= 10;
            }
            n = result;
        } while (result >= 10);

        System.out.println("Willy-nilly, this semester I will learn " + languageArray[result]);

        Optional.optionalMain(args);
    }
}
