package Homework;

import Compulsory.*;
import Exceptions.*;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.IOException;
import java.nio.file.Paths;

/**
 * Class containing a method that loads a Catalog object from an already existing file
 */

public class LoadCommand extends Command{
    public LoadCommand(Catalog catalog) {
        super(catalog);
    }

    @Override
    public void execute(String arguments) throws CustomException, IOException, ClassNotFoundException {
        parseArguments(arguments);
        if (argumentList.get(0).equals("load") && argumentList.size() == 2) {
            ObjectMapper mapper = new ObjectMapper();
            catalog = mapper.readValue(Paths.get(argumentList.get(1)).toFile(), Catalog.class);
        }
        else {
            throw new CustomException("Invalid load call! Try using this syntax: load [path]");
        }
    }

    public Catalog executeCommand(String arguments) throws CustomException, IOException, ClassNotFoundException {
        parseArguments(arguments);
        if (argumentList.get(0).equals("load") && argumentList.size() == 2) {
            ObjectMapper mapper = new ObjectMapper();
            Catalog catalog = mapper.readValue(Paths.get(argumentList.get(1)).toFile(), Catalog.class);
            return catalog;
        }
        else {
            throw new CustomException("Invalid load call!");
        }
    }
}

