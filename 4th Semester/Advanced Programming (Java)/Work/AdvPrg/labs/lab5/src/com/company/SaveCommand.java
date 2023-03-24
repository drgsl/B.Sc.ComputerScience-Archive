package com.company;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class SaveCommand extends Command{
    public SaveCommand(Catalog catalog) {
        super(catalog);
        callMethod = "save";
    }

    @Override
    public void execute(String arguments) throws CommandException, IOException {
        parseArguments(arguments);
        if (argumentList.get(0).equals("save") && argumentList.size() == 1)  {
            FileOutputStream fileOutputStream = new FileOutputStream(catalog.getPath());
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(fileOutputStream);
            objectOutputStream.writeObject(catalog);
            objectOutputStream.flush();
            objectOutputStream.close();
            fileOutputStream.close();
        }
        else {
            throw new CommandException("Invalid save call! To call, write this <" + callMethod + ">");
        }
    }
}
