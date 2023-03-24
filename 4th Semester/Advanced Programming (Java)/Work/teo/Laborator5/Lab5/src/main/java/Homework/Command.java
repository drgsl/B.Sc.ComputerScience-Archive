package Homework;

import Compulsory.*;
import Exceptions.*;
import lombok.Data;
import org.apache.tika.exception.TikaException;
import org.xml.sax.SAXException;
import java.io.IOException;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

/**
 * An abstract class describing a command
 * It has a method that adds the arguments of the command to a list, that is used by the specific commands
 */
@Data
public abstract class Command {
    Catalog catalog;
    List<String> argumentList;

    public Command(Catalog catalog) {
        this.catalog = catalog;
        argumentList = new LinkedList<>();
    }
    public abstract void execute(String arguments) throws CustomException, IOException, ClassNotFoundException, TikaException, SAXException;
    void parseArguments(String arguments) {
        this.argumentList.addAll(Arrays.asList(arguments.split(" ")));
    }
}
