package TTPP;

import java.time.*;
import java.util.LinkedList;

public interface Visitable {

     LocalTime getOpeningHours();
     LocalTime getClosingHours();
     String getProgram();

     void setOpeningHours(LocalTime openingHours);
     void setClosingHours(LocalTime closingHours);

    default void setOpeningHoursDefault() {
        LocalTime temp = LocalTime.parse("09:00");
        setOpeningHours(temp);
        temp = LocalTime.parse("20:00");
        setClosingHours(temp);
    }

    static Duration getDuration(Visitable location) {
        return Duration.between(location.getOpeningHours(), location.getClosingHours());
    }

}
