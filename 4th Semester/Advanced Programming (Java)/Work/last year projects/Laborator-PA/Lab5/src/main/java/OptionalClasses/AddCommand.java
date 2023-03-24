package OptionalClasses;

import CatalogUtilities.Catalog;
import Exceptions.CustomException;
import Items.*;

import java.util.Arrays;

public class AddCommand extends Command {

    public AddCommand(Catalog catalog) {
        super(catalog);
        callMethod = "add [-image / -song] [path] [name] [is licensed (true/false)]";
    }

    @Override
    public void execute(String arguments) throws CommandException, CustomException {
        parseArguments(arguments);

        // The user wants to add an Image
        if (this.argumentList.get(1).equals("-image") && argumentList.size() == 5) {
            Item itemToBeAdded = new Image(argumentList.get(2), argumentList.get(3), argumentList.get(4).equals("true"));
            catalog.addItem(itemToBeAdded);
        }
        // The user wants to add a Song
        else if (argumentList.get(1).equals("-song") && argumentList.size() == 4) {
            Item itemToBeAdded = new Song(argumentList.get(2), argumentList.get(3), argumentList.get(4));
            catalog.addItem(itemToBeAdded);
        }
        // Invalid call to add command
        else {
            throw new CommandException("Invalid add call! To call, write this <" + callMethod + ">");
        }
    }
}
