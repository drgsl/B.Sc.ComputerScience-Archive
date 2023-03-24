package bonus;

import org.jgrapht.Graph;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

public class BounusMain {
    public static void main(String[] args) throws SQLException {
        Connection con = DBCPDataSource.getConnection();
        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(2);

        for (int i = 1; i <= 5; i++)
        {
            CityMaker cityMaker = new CityMaker();
            System.out.println("Created : " + i);

            executor.execute(cityMaker);
        }
        executor.shutdown();

        CityMaker c = new CityMaker();
        for(int i=0;i<100;i++) {
            c.sisterhood();
        }

        GraphDB g = new GraphDB();
        Graph graph = g.create();
        GraphBron g1 = new GraphBron(graph);
        g1.makeClique();
    }
}
