package Compulsory;

import Exceptions.CustomException;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.ToString;

/**
 * A class that describes an item of type article
 */

@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
public class Article extends Item {
    private String author;
    private int year;

    public Article(String id, String title, String path, String author, int year) throws CustomException{
        super(id,path,title);
        if (author == null) {
            throw new CustomException("Cannot have a book with no author!");
        }
        if(year<0 || year>2022){
            throw new CustomException("The year of publication should be between 0 and 2022");
        }
        this.author=author;
        this.year=year;
    }
}
