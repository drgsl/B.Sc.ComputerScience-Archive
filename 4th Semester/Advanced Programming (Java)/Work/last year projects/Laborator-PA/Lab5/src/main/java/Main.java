import CatalogUtilities.*;
import Items.*;
import Exceptions.CustomException;
import OptionalClasses.*;

import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // compulsory(args);
        optional(args);
    }

    public static void compulsory(String[] args) {
        try {
            // We create a new Catalog object
            Catalog c = new Catalog("F:\\Facultate\\PROIECTE-JAVA-[PA]\\Laborator-PA\\Lab5\\catalog.txt");

            // We create two different items
            Song s = new Song("F:\\Facultate\\PROIECTE-JAVA-[PA]\\Laborator-PA\\Lab5\\song.mp3", "Song free", "Indie");
            Image i = new Image("F:\\Facultate\\PROIECTE-JAVA-[PA]\\Laborator-PA\\Lab5\\bird.jpg", "Birds",false);

            // We add them to the Catalog
            CatalogUtil.add(c, s);
            CatalogUtil.add(c, i);

            // We open the image
            CatalogUtil.play(i);

            // We list the contents
            CatalogUtil.list(c);

            // We save and load the Catalog in a new variable
            CatalogUtil.save(c);
            Catalog c2 = CatalogUtil.load("F:\\Facultate\\PROIECTE-JAVA-[PA]\\Laborator-PA\\Lab5\\catalog.txt");

            // Is the Catalog object (which was loaded from memory) null?
            assert c2 != null;
            CatalogUtil.list(c2);
        }
        catch (CustomException exp) {
            System.out.println("Main exception : " + exp.getMessage());
        }
        catch (IOException exp) {
            System.out.println("IO exception : " + exp.getMessage());
        }
    }

    public static void optional(String[] args) {
        try {
            Scanner input = new Scanner(System.in);
            Catalog catalog = new Catalog("catalog.txt");
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
                    case "save" -> {
                        SaveCommand saveCommand = new SaveCommand(catalog);
                        saveCommand.execute(command);
                    }
                    case "load" -> {
                        LoadCommand loadCommand = new LoadCommand(catalog);
                        loadCommand.execute(command);
                    }
                    case "play" -> {
                        PlayCommand playCommand = new PlayCommand(catalog);
                        playCommand.execute(command);
                    }
                    case "report" -> {
                        ReportCommand reportCommand = new ReportCommand(catalog);
                        reportCommand.execute(command);
                    }
                    case "quit" -> {
                        return;
                    }
                    default -> throw new CustomException("Command not supported!");
                }
            }
        }
        catch (CustomException | CommandException | IOException | ClassNotFoundException exp) {
            System.out.println(exp.getMessage());
        }

    }

}
