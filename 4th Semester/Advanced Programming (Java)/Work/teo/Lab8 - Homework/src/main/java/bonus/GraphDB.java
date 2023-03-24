package bonus;

import org.jgrapht.Graph;
import org.jgrapht.graph.DefaultEdge;
import org.jgrapht.graph.SimpleGraph;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class GraphDB {

    public GraphDB(){};

    public Graph create() {
        Graph<Integer, DefaultEdge> g = new SimpleGraph<>(DefaultEdge.class);
        try{
            Connection con = DBCPDataSource.getConnection();
            Statement stmt = con.createStatement();
            int v1, v2;
            ResultSet rs = stmt.executeQuery("select sister1, sister2 from sisters");
            if (rs == null) return null;
            while(rs.next()){
                v1= rs.getInt(1);
                v2 = rs.getInt(2);
                g.addVertex(v1);
                g.addVertex(v2);
                g.addEdge(v1,v2);
            }
            con.close();
        }
        catch (SQLException e) {
            e.printStackTrace();
        }
        finally{
            return g;
        }
    }
}
