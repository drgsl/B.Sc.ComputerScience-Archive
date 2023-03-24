package com.company;

import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
         compulsory(args);
    }

    public static void compulsory(String[] args) {
        try {
            // We create a new Catalog object
            Catalog c = new Catalog("C:\\Users\\drago\\Desktop\\FII\\AP (JAVA)\\AdvPrg\\labs\\lab5\\catalog.txt");

            // We create two different items
            Book s = new Book("C:\\Users\\drago\\Desktop\\FII\\AP (JAVA)\\AdvPrg\\labs\\lab5\\book.txt", "Book name");
            Article i = new Article("C:\\Users\\drago\\Desktop\\FII\\AP (JAVA)\\AdvPrg\\labs\\lab5\\bird.txt", "article about birds", "Alex");

            // We add them to the Catalog
            CatalogUtil.add(c, s);
            CatalogUtil.add(c, i);

            // We list the contents
            CatalogUtil.list(c);

            // We save and load the Catalog in a new variable
            CatalogUtil.save(c);
            Catalog c2 = CatalogUtil.load("C:\\Users\\drago\\Desktop\\FII\\AP (JAVA)\\AdvPrg\\labs\\lab5\\catalog.txt");

            // Is the Catalog object (which was loaded from memory) null?
            assert c2 != null;
            CatalogUtil.list(c2);
        }
        catch (CustomException exp) {
            System.out.println("Main exception : " + exp.getMessage());
        }
    }

}
