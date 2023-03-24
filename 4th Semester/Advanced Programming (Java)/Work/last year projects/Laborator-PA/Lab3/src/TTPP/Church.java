package TTPP;

import java.time.LocalTime;

public class Church extends Location implements Visitable {
    LocalTime openingHours;
    LocalTime closingHours;

    final String religion;

    /**
     * The default constructor of the Location class.
     *
     * @param name The name of the location.
     */
    public Church(String name, String religion) {
        super(name);
        this.religion = religion;
    }

    @Override
    public void setOpeningHours(LocalTime openingHours) {
        this.openingHours = openingHours;
    }

    @Override
    public void setClosingHours(LocalTime closingHours) {
        this.closingHours = closingHours;
    }


    @Override
    public LocalTime getOpeningHours() {
        return this.openingHours;
    }
    @Override
    public LocalTime getClosingHours() {
        return this.closingHours;
    }
    @Override
    public String getProgram() {
        return this.openingHours + " - " + this.closingHours;
    }
    public String getReligion() {
        return this.religion;
    }
}
