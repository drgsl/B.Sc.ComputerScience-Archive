public class homeworkLab1 {
/// 2E1 - Bobu Dragos

    public static void main(String args[]) {

        long startTime = System.nanoTime();

        /// 1
        if (args.length < 3) {
            System.out.println("Not enough arguments!");
            System.exit(-1);
        }

        try {
            Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            // not and int :(
            System.out.println("First param must be an int");
            System.exit(-1);
        }

        try {
            Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            // not and int :(
            System.out.println("second param must be an int");
            System.exit(-1);
        }

        int n = Integer.parseInt(args[0]);
        int p = Integer.parseInt(args[1]);
        char[] alphabet = args[2].toCharArray();

        System.out.println(n + " " + p + " " + new String(alphabet));

        /// 2
        String[] words = new String[n];

        for (int i = 0; i < words.length; i++) {

            StringBuilder sb = new StringBuilder();

            while (true) {
                int pos = (int) (Math.random() * (alphabet.length + 1)) - 1;
                if (pos < 0)
                    continue;
                sb.append(alphabet[pos]);

                if (sb.length() == p) {
                    break;
                }

            }

            words[i] = sb.toString();
        }
        for (int i = 0; i < words.length; i++) {
            System.out.println(i+". " + words[i]);
        }

        /// 3

        boolean[][] neighbourMatrix = new boolean[n][n];

        System.out.println("calculating the neighbour matrix...");

        for (int i = 0; i < neighbourMatrix.length; i++) {
            for (int j = 0; j < neighbourMatrix.length; j++) {

                for (int l = 0; l < words[j].length(); l++) {
                    if (words[i].indexOf(words[j].toCharArray()[l]) != -1) {

                        neighbourMatrix[i][j] = true;
                    }
                }

            }
        }
        System.out.println("done :) ");

        for (int i = 0; i < neighbourMatrix.length; i++) {
            for (int j = 0; j < neighbourMatrix.length; j++) {
                // System.out.print(neighbourMatrix[i][j] + " ");

                if (neighbourMatrix[i][j]) {
                    System.out.print(1 + " ");
                } else {
                    System.out.print(0 + " ");
                }

            }
            System.out.println();
        }


        /// 4

        long endTime = System.nanoTime();
        long totalTime = endTime - startTime;
        System.out.println("it took me: " +  totalTime + " nanoseconds ( " + totalTime/1000000000 + " seconds )");
    }
}
