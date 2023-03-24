package Lab1;

public class Compulsory {
    static int sum(int n)
    {
        int suma = 0;
        while (n != 0)
        {
            suma = suma + n % 10;
            n = n / 10;
        }
        return suma;
    }
    public static void main(String args[])
    {
        System.out.println("Hello World");
        String languages[]={"C", "C++", "C#", "Python", "Go", "Rust", "JavaScript", "PHP", "Swift", "Java"};
        int n = (int) (Math.random() * 1_000_000);
        n = n * 3;
        n = n + Integer.parseInt("10101",2);
        n = n + Integer.parseInt("FF", 16);
        n = n * 6;
        int result = n;
        while (result > 9)
        {
            result = sum(result);
        }
        System.out.println("Willy-nilly, this semester I will learn " + languages[result]);
    }
}
