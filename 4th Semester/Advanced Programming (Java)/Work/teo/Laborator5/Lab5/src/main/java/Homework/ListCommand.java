package Homework;

import Compulsory.*;
import Exceptions.*;

/**
 * Class containing a method that prints all the items from a catalog
 */

public class ListCommand extends Command{
    public ListCommand(Catalog catalog) {
        super(catalog);
    }

    @Override
    public void execute(String arguments) throws CustomException {
        parseArguments(arguments);
        if (argumentList.get(0).equals("list") && argumentList.size() == 1) {
            for (Item i : catalog.getItemList()) {
                System.out.println(i.toString());
            }
        }
        else {
            throw new CustomException("Invalid list call! Syntax: list");
        }
    }
}
