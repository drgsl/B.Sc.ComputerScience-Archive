package Items;

import Exceptions.CustomException;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Song extends Item {

    private final String author;

    public Song(String path, String name, String author) throws CustomException {
        super(path, name);

        if (!author.matches("[A-Z][a-z]+")) {
            throw new CustomException("Author name is not correct!");
        }

        this.author = author;
    }

    public String getAuthor() {
        return author;
    }

    @Override
    public String toString() {
        return "Song with name " + name + ", written by " + author + ".";
    }
}
