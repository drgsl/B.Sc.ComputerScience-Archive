package Homework;
import Compulsory.*;
import Exceptions.*;

/**
 * A class containing a method that adds an item to the catalog
 */

public class AddCommand extends Command{
    public AddCommand(Catalog catalog) {
        super(catalog);
    }

    @Override
    public void execute(String arguments) throws CustomException {
        parseArguments(arguments);

        // The user wants to add a Book
        if (this.argumentList.get(1).equals("book") && argumentList.size() == 7) {
            Item itemToBeAdded = new Book(argumentList.get(2), argumentList.get(3), argumentList.get(4),argumentList.get(5),Integer.parseInt(argumentList.get(6)));
            catalog.add(itemToBeAdded);
        }
        // The user wants to add an Article
        else if (argumentList.get(1).equals("article") && argumentList.size() == 7) {
            Item itemToBeAdded = new Article(argumentList.get(2), argumentList.get(3), argumentList.get(4),argumentList.get(5),Integer.parseInt(argumentList.get(6)));
            catalog.add(itemToBeAdded);
        }
        // Invalid call to add command
        else {
            throw new CustomException("Invalid add call! Try the following syntax: add [book/article] [id] [title] [path] [author] [year]");
        }
    }
}
