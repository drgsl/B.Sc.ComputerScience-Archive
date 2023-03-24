import Compulsory.*;
import Homework.*;
import Exceptions.*;
import org.apache.tika.exception.TikaException;
import org.xml.sax.SAXException;

import java.io.IOException;
import java.util.Scanner;

/**
 * @author Teodora Breahna
 */

public class Main {
    public static void main(String[] args) {
        //compulsory(args);
        homework(args);
    }

    public static void compulsory(String[] args) {
        try{
            Catalog c = new Catalog();
            Book b1 = new Book("knuth67","The Art of Computer Programming","C:\\Users\\OneDrive\\Desktop\\text.txt","Donald E. Knuth",1967);
            Article a1= new Article("java17", "The Java Language Specification", "https://docs.oracle.com/javase/specs/jls/se17/html/index.html", "James Gosling & others", 2021);

            c.add(b1);
            c.add(a1);
            c.save();
            c.toString(c);

            System.out.println();
            Catalog c2 = new Catalog();
            //c2.load("./src/main/resources/loadedData.json");
        }
        catch (CustomException exp) {
            System.out.println("Main exception : " + exp.getMessage());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void homework(String[] args) {
        try {
            Scanner input = new Scanner(System.in);
            Catalog catalog = new Catalog();
            //book sadd IP C:\Users\teodo\OneDrive\Desktop\IP.txt Teo 2022
            System.out.println("Started the shell...\n");
            while (true) {
                System.out.print(">>");
                String command = input.nextLine();
                String typeOfCommand = new Scanner(command).next();
                switch (typeOfCommand) {
                    case "add" -> {
                        AddCommand addCommand = new AddCommand(catalog);
                        addCommand.execute(command);
                    }
                    case "list" -> {
                        ListCommand listCommand = new ListCommand(catalog);
                        listCommand.execute(command);
                    }
                    case "load" -> {
                        LoadCommand loadCommand = new LoadCommand(catalog);
                        catalog = loadCommand.executeCommand(command);
                    }
                    case "view" -> {
                        ViewCommand viewCommand = new ViewCommand(catalog);
                        viewCommand.execute(command);
                    }
                    case "report" -> {
                        ReportCommand reportCommand = new ReportCommand(catalog);
                        reportCommand.execute(command);
                    }
                    case "info" -> {
                        InfoCommand infoCommand = new InfoCommand(catalog);
                        infoCommand.execute(command);
                    }
                    case "quit" -> {
                        return;
                    }
                    default -> throw new CustomException("Command not supported!");
                }
            }
        }
        catch (CustomException | IOException | ClassNotFoundException | IllegalArgumentException exp ) {
            System.out.println(exp.getMessage());
        } catch (TikaException e) {
            e.printStackTrace();
        } catch (SAXException e) {
            e.printStackTrace();
        }
    }
}
