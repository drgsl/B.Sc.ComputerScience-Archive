package OptionalClasses;

import CatalogUtilities.Catalog;
import Exceptions.CustomException;

import java.awt.*;
import java.io.File;
import java.io.IOException;

public class PlayCommand extends Command {
    public PlayCommand(Catalog catalog) {
        super(catalog);
        callMethod = "play [index]";
    }

    @Override
    public void execute(String arguments) throws CommandException, IOException {
        parseArguments(arguments);

        if (argumentList.get(0).equals("list") && argumentList.size() == 2 && Integer.getInteger(argumentList.get(1)) <= catalog.getItemList().size() - 1) {
            Desktop desktop = Desktop.getDesktop();
            desktop.open(new File(catalog.getItemList().get(Integer.getInteger(argumentList.get(1))).getPath()));
        }
        else {
            throw new CommandException("Invalid play call! To call, write this <" + callMethod + ">");
        }
    }
}
