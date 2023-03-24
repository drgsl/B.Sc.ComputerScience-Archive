package Compulsory;

import com.fasterxml.jackson.core.util.DefaultPrettyPrinter;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.ObjectWriter;
import lombok.Data;
import Exceptions.CustomException;
import java.io.*;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
/**
 * A Catalog class used to classify items.
 * The itemList can store any class that extends the abstract class Item.
 * It has 5 main functions:
 * add -> which adds to the catalog a given item
 * toString -> which calls, for each Item object in a given Catalog object, the function toString()
 * save -> which saves a given Catalog object to an already existing file
 * load -> loads a Catalog object from an already existing file
 */

@Data
public class Catalog implements Serializable {
    private List<Item> itemList;

    public Catalog(){
        itemList = new ArrayList<>();
    }

    public void add(Item item) throws CustomException {
        if (item == null) {
            throw new CustomException("Cannot add a null item!");
        }
        itemList.add(item);
    }

    public void toString(Catalog catalog) {
        for (Item i : catalog.getItemList()) {
            System.out.println(i.toString());
        }
    }

    public void save() throws IOException {
        ObjectMapper mapper = new ObjectMapper();
        ObjectWriter writer = mapper.writer(new DefaultPrettyPrinter());
        try {
            writer.writeValue(Paths.get("./src/main/resources/loadedData.json").toFile(), this);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public Catalog load(String pathToLoadFrom) throws IOException {
        try{
            ObjectMapper mapper = new ObjectMapper();
            Catalog catalog = mapper.readValue(Paths.get(pathToLoadFrom).toFile(), Catalog.class);
            System.out.println(catalog);
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
        return null;
    }

}