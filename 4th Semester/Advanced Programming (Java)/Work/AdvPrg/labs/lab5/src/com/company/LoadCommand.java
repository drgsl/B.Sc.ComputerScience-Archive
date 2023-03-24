package com.company;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class LoadCommand extends Command{
    public LoadCommand(Catalog catalog) {
        super(catalog);
        callMethod = "load [path]";
    }

    @Override
    public void execute(String arguments) throws CommandException, IOException, ClassNotFoundException {
        parseArguments(arguments);
        if (argumentList.get(0).equals("load") && argumentList.size() == 2) {
            FileInputStream fileOutputStream = new FileInputStream(argumentList.get(1));
            ObjectInputStream objectOutputStream = new ObjectInputStream(fileOutputStream);
            catalog = (Catalog) objectOutputStream.readObject();
            objectOutputStream.close();
            fileOutputStream.close();
        }
        else {
            throw new CommandException("Invalid load call! To call, write this <" + callMethod + ">");
        }
    }
}
