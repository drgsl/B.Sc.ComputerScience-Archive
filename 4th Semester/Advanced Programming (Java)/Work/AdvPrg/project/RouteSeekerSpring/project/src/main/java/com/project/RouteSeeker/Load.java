package com.project.RouteSeeker;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import static java.lang.Integer.parseInt;

public class Load {

    public static void loadNodes(){
        try {
            Connection con = Database.getConnection();
            PreparedStatement pstmt = con.prepareStatement(
                    "insert into nodes(x,y) values (?,?)");

            File file=new File("src/main/resources/Nodes.csv");
            FileReader fr=new FileReader(file);
            BufferedReader br=new BufferedReader(fr);
            String line;
            String[] columns;
            while((line=br.readLine())!=null)
            {
                columns = line.split(",");

                int x = parseInt(columns[0]);
                pstmt.setInt(1,x);
                int y = parseInt(columns[1]);
                pstmt.setInt(2,y);


                pstmt.executeUpdate();
            }
            fr.close();
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    public static void loadEdges(){
        try {
            Connection con = Database.getConnection();
            PreparedStatement pstmt = con.prepareStatement(
                    "insert into edges(src,dst,cost,name) values (?,?,?,?)");

            File file=new File("src/main/resources/Edges.csv");
            FileReader fr=new FileReader(file);
            BufferedReader br=new BufferedReader(fr);
            String line;
            String[] columns;
            while((line=br.readLine())!=null)
            {
                columns = line.split(",");

                int src = parseInt(columns[0]);
                pstmt.setInt(1,src);
                int dest = parseInt(columns[1]);
                pstmt.setInt(2,dest);
                int cost = parseInt(columns[2]);
                pstmt.setInt(3,cost);
                String name = columns[3];
                pstmt.setString(4,name);

                pstmt.executeUpdate();
            }
            fr.close();
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        try {
            Database.createConnection();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        loadNodes();
        loadEdges();
    }

}
