package Homework;

import Compulsory.*;
import Exceptions.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

/**
 * Class containing a method that opens an item using the native operating system application
 */

public class ViewCommand extends Command{
    public ViewCommand(Catalog catalog) {
        super(catalog);
    }

    @Override
    public void execute(String arguments) throws CustomException, IOException, IllegalArgumentException {
        parseArguments(arguments);

        if (argumentList.get(0).equals("view") && argumentList.size() == 2 && Integer.parseInt(argumentList.get(1)) <= catalog.getItemList().size()) {
            Desktop desktop = Desktop.getDesktop();
            desktop.open(new File(catalog.getItemList().get(Integer.parseInt(argumentList.get(1))-1).getPath()));
        }
        else {
            throw new CustomException("Invalid view call! Try using this syntax: view [index]");
        }
    }
}
