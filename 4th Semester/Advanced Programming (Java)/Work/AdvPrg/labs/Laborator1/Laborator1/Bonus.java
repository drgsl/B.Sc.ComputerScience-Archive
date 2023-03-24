package Lab1;
import java.util.*;
import static Lab1.Homework.n;

public class Bonus {
    Vector<Integer>[] graph = new Vector[n];
    Vector<Integer>[] cycles = new Vector[n];
    int cyclenumber;

    //Adaug muchii in graf
    void addEdge(int u, int v)
    {
        graph[u].add(v);
    }

    void dfs_cycle(int nod, int pr, int[] color, int ciclu[], int[] parent)
    {
        //Daca am gasit deja un ciclu ma opresc
        if(cyclenumber>=1)
        {
            return;
        }

        //Daca nodul a fost deja vizitat complet ma opresc
        if (color[nod] == 2) return;

        //Daca nodul nu a fost inca vizitat complet si am ajuns inapoi la el,
        //inseamna ca am un ciclu si ma voi intoarce prin parinti ca sa i adaug in vector
        if (color[nod] == 1)
        {
            cyclenumber++;
            int crt = pr;
            ciclu[crt] = cyclenumber;

            while (crt != nod)
            {
                crt = parent[crt];
                ciclu[crt] = cyclenumber;
            }
            return;
        }
        parent[nod] = pr;

        //Marchez nodul ca fiind partial vizitat
        color[nod] = 1;

        //Parcurg dfs toti fiii nodului curent
        for (int v : graph[nod])
        {

            //Daca ajung la un nod deja vizitat,
            //verific daca e parintele nodului curent
            if (v == parent[nod])
            {
                continue;
            }
            dfs_cycle(v, nod, color,ciclu, parent);
        }

        //Marchez nodul ca fiind complet vizitat
        color[nod] = 2;
    }

    void printCycles(int n,int ciclu[])
    {
        //Adaug cuvintele in vectorul ciclului din care fac parte
        for (int i = 0; i < n; i++)
        {
            if (ciclu[i] != 0) {
                cycles[ciclu[i]].add(i);
            }
        }

        //Afisez ciclurile
        for (int i = 1; i <= cyclenumber; i++)
        {
            System.out.printf("Subset: ");
            for (int x : cycles[i])
            {
                System.out.print(Lab1.Homework.words.get(x) + " ");
            }
            System.out.print(Lab1.Homework.words.get(cycles[i].get(0)));
            System.out.println();
        }
    }

    public void mainBonus(boolean Matrice[][]){
        for (int i = 0; i < n; i++)
        {
            graph[i] = new Vector<>();
            cycles[i] = new Vector<>();
        }

        //Verific matricea de adiacenta si adaug muchiile existente
        for(int i = 0; i< n; i++)
            for(int j=0;j<n;j++)
            {
                if(i!=j && Matrice[i][j]==true) addEdge(i,j);
            }

        /* Aici imi afisam listele de adiacenta
        for(int i=0;i<n;i++)
        {
            System.out.print(i + ": ");
            for(int j=0;j<graph[i].size();j++)
                System.out.print(graph[i].get(j) + " ");
            System.out.println();
        }
         */

        int[] color = new int[n];
        int[] parent = new int[n];
        int[] ciclu = new int[n];
        for(int i=0;i<n;i++) ciclu[i]=0;
        cyclenumber = 0;

        dfs_cycle(0, -1, color, ciclu,parent);
        printCycles(n,ciclu);
    }

}
