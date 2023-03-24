package com.company;

import java.io.Serializable;
import java.nio.file.Files;
import java.nio.file.Path;

public abstract class Item implements Serializable {
    protected String id;
    protected String path;
    protected String name;

    public Item(String path, String name) throws CustomException {
        if (name == null) {
            throw new CustomException("Cannot create an Item with no name!");
        }

        if (!Files.isRegularFile(Path.of(path))) {
            throw new CustomException("File does not exist!");
        }

        this.path = path;
        this.name = name;

    }

    public String getPath() {
        return path;
    }

    public String getName() {
        return name;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }
}