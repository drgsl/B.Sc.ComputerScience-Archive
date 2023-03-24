package com.company;

import java.util.Arrays;

public class AddCommand extends Command {

    public AddCommand(Catalog catalog) {
        super(catalog);
        callMethod = "add [-book / -article] [path] [name]";
    }

    @Override
    public void execute(String arguments) throws CommandException, CustomException {
        parseArguments(arguments);

        // The user wants to add an Image
        if (this.argumentList.get(1).equals("-book") && argumentList.size() == 5) {
            Item itemToBeAdded = new Book(argumentList.get(2), argumentList.get(3));
            catalog.addItem(itemToBeAdded);
        }
        // The user wants to add a Song
        else if (argumentList.get(1).equals("-article") && argumentList.size() == 4) {
            Item itemToBeAdded = new Article(argumentList.get(2), argumentList.get(3), argumentList.get(4));
            catalog.addItem(itemToBeAdded);
        }
        // Invalid call to add command
        else {
            throw new CommandException("Invalid add call! To call, write this <" + callMethod + ">");
        }
    }
}
