package com.company;

import java.awt.*;
import java.io.*;

/**
 * A class used to manipulate a Catalog object.
 * It has 5 main static functions:
 * add -> which adds to a given catalog a given item
 * list -> which calls, for each Item object in a given Catalog object, the function toString()
 * play -> which tries to open a given Item
 * save -> which saves a given Catalog object to an already exiting file (as binary)
 * load -> loads a Catalog object from an already existing file
 */

public class CatalogUtil {

    private CatalogUtil() {}

    public static void add(Catalog catalog, Item item) {
        try {
            catalog.addItem(item);
        }
        catch (CustomException exc) {
            System.out.println(exc.getMessage());
        }

    }

    public static void list(Catalog catalog) {
        for (Item i : catalog.getItemList()) {
            System.out.println(i);
        }
    }

    public static void play(Item item) throws IOException {
        Desktop desktop = Desktop.getDesktop();
        try {
            desktop.open(new File(item.getPath()));
        }
        catch (IOException exc) {
            System.out.println("Play in CatalogUtil: " + exc.getMessage());
        }
    }

    public static void save(Catalog catalog) {
        try {
            FileOutputStream fos = new FileOutputStream(catalog.getPath());
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(catalog);
            oos.flush();
            fos.close();
        }
        catch (FileNotFoundException exp) {
            System.out.println("Catalog (for saving) not found at path " + catalog.getPath());
        }
        catch (IOException exp) {
            System.out.println("Failed to creat ObjectOutputStream! Exception message: " + exp.getMessage());
        }
    }

    public static Catalog load(String path) {

        try {
            FileInputStream fis = new FileInputStream(path);
            ObjectInputStream ois = new ObjectInputStream(fis);
            Catalog temp = (Catalog) ois.readObject();
            fis.close();
            return temp;
        }
        catch (FileNotFoundException exp) {
            System.out.println("Catalog (for loading) not found at path " + path);
        }
        catch (IOException exp) {
            System.out.println("Failed to creat ObjectInputStream! Exception message: " + exp.getMessage());
        }
        catch (ClassNotFoundException exp) {
            System.out.println("Catalog class not found while trying to load from path " + path + ". Error message : " + exp.getMessage());
        }
        return null;
    }


}
