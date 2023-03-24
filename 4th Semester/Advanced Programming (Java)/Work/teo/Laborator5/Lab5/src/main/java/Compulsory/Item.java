package Compulsory;

import com.fasterxml.jackson.annotation.JsonSubTypes;
import com.fasterxml.jackson.annotation.JsonTypeInfo;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;
import java.io.Serializable;

/**
 * An abstract class that describes the items in the catalog
 */

//tipul de item - serializare
@JsonTypeInfo(use = JsonTypeInfo.Id.CLASS,
        include = JsonTypeInfo.As.PROPERTY,
        property = "type")
@JsonSubTypes({
        @JsonSubTypes.Type(value = Book.class),
        @JsonSubTypes.Type(value = Article.class)
})

@Data
@NoArgsConstructor
@AllArgsConstructor
abstract public class Item implements Serializable {
    protected String id;
    protected String path;
    protected String title;

}

