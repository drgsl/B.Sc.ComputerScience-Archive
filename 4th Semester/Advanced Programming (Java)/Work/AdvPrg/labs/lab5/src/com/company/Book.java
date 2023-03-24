package com.company;

public class Book extends Item {

    public Book(String path, String name) throws CustomException {
        super(path, name);
    }

    @Override
    public String toString() {
        return "Book with id [" + id + "] and name " + name;
    }
}
