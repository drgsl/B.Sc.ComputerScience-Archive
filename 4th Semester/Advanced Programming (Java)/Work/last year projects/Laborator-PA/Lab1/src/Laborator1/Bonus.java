package Laborator1;

import java.util.*;

public class Bonus {
    public static void bonusMain() {
        int len = (int) ((Math.random() * 10000) % 30);
        int[] tree = new int[len];

        tree[0] = -1;

        // Tree creation

        // Tree representation
        Stack<Integer> s = new Stack<Integer>();

        boolean[] visitedNodes = new boolean[len];
        for (int i = 0; i < len; ++i)
            visitedNodes[i] = false;

        s.push(0);

        while (!s.isEmpty()) {
            int node = s.pop();
            for (int i = 0; i < len; ++i)
                if (tree[i] == node && !visitedNodes[i]) {

                }
        }
    }
}
