package com.company;

public class ListCommand extends Command {
    public ListCommand(Catalog catalog) {
        super(catalog);
        callMethod = "list";
    }

    @Override
    public void execute(String arguments) throws CommandException {
        parseArguments(arguments);
        if (argumentList.get(0).equals("list") && argumentList.size() == 1) {
            for (Item i : catalog.getItemList()) {
                System.out.println(i.toString());
            }
        }
        else {
            throw new CommandException("Invalid list call! To call, write this <" + callMethod + ">");
        }
    }

}
