package com.company;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Article extends Item {

    public Article(String path, String name, String author) throws CustomException {
        super(path, name);

        if (!author.matches("[A-Z][a-z]+")) {
            throw new CustomException("Author name is not correct!");
        }
    }

    @Override
    public String toString() {
        return "Article with name " + name;
    }
}
