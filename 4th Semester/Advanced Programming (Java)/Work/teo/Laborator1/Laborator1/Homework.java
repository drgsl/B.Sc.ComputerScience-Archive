package Lab1;

import java.util.ArrayList;
import java.util.Random;

import static java.lang.Character.*;

public class Homework {
    static char[] alphabet;
    static boolean largeInput = false;
    static long startTime, endTime;
    static int n, i, j;
    static ArrayList<String> words = new ArrayList<String>();

    public static ArrayList<String> generate(int n, int p, char[] alphabet) {
        //Generez cuvintele cu litere in ordine aleatorie
        ArrayList<String> words = new ArrayList<String>();
        Random r = new Random();

        for (int i = 0; i < n; i++) {
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < p; j++) {
                int pos = r.nextInt(alphabet.length);
                sb.append(alphabet[pos]);
            }
            words.add(sb.toString());
        }
        return words;
    }

    static boolean vecini(String a, String b) {
        //Verific daca doua cuvinte sunt vecine
        int v[] = new int[alphabet.length];
        int i, j;

        //Parcurg primul cuvant si pun 1 pe pozitiile literelor pe care le contine
        for (i = 0; i < a.length(); i++) {
            for (j = 0; j < alphabet.length; j++) {
                int cmp = compare(a.charAt(i), alphabet[j]);
                if (cmp == 0) v[j] = 1;
            }
        }

        //Parcurg al doilea cuvant si returnez true cand gasesc o litera
        // pe care o contine si pe a carei pozitie gasesc valoarea 1
        for (i = 0; i < b.length(); i++) {
            for (j = 0; j < alphabet.length; j++) {
                int cmp = compare(b.charAt(i), alphabet[j]);
                if (cmp == 0)
                    if (v[j] == 1)
                        return true;
            }
        }
        return false;
    }

    public static void main(String args[]) {

        //Validez nr de argumente
        if (args.length < 3) {
            System.out.println(
                    "Usage: number, number, one or more characters");
            System.exit(-1);
        }
        n = Integer.parseInt(args[0]);

        //Validez n
        if (n <= 0) {
            System.out.printf("Invalid argument n = %d!", n);
            return;
        }

        if (n > 30000)
            largeInput = true;
        if (largeInput)
            startTime = System.nanoTime();

        int p = Integer.parseInt(args[1]);
        int m = args.length - 2;
        ArrayList<Lab1.Vecini> neighbours = new ArrayList<Lab1.Vecini>();
        alphabet = new char[m];
        boolean Matrice[][] = new boolean[n][n];

        //Adaug literele in alfabet
        for (i = 0; i < m; i++) {
            alphabet[i] = args[i + 2].charAt(0);
        }

        //Generez cuvintele
        words = generate(n, p, alphabet);
        for (i = 0; i < words.size(); i++) {
            System.out.println(words.get(i));
        }

        //Completez matricea de adiacenta si structura de date
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {
                Matrice[i][j] = false;
            }
        for (i = 0; i < n; i++) {
            Lab1.Vecini v = new Lab1.Vecini();
            v.setWord(words.get(i));
            for (j = 0; j < n; j++) {
                if (i != j)
                    if (vecini(words.get(i), words.get(j)) == true) {
                        Matrice[i][j] = true;
                        v.addNeighbour(words.get(j));
                    }
            }
            neighbours.add(v);
        }

        //Afisez matricea
        if (!largeInput) {
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    System.out.print(i + "-" + j + ": " + Matrice[i][j] + " ");
                }
                System.out.println();
            }
        }


        //Afisez structura de date sau timpul in nanosec dupa caz
        if (largeInput) {
            endTime = System.nanoTime();
            System.out.printf("Total time in nanoseconds: %d\n", endTime - startTime);
        } else {
            for (i = 0; i < n; i++)
                neighbours.get(i).print();
        }

        System.out.println();
        System.out.println("----Bonus----");
        Bonus b = new Bonus();
        b.mainBonus(Matrice);

    }
}
