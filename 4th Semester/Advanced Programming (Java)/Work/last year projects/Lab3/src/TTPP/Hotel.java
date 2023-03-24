package TTPP;

import java.time.LocalTime;

public class Hotel extends Location implements Visitable, Classifiable {

    LocalTime openingHours;
    LocalTime closingHours;

    Integer rank;

    Integer pricePerNight;

    /**
     * The default constructor of the Location class.
     *
     * @param name The name of the location.
     */
    public Hotel(String name) {
        super(name);
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
    public void setRank(Integer rank) {
        if (rank <= 0) {
            System.out.println("The rank must be a positive integer!");
            return;
        }
        this.rank = rank;
    }

    public void setPricePerNight(Integer price) {
        if (price <= 0) {
            System.out.println("The price cannot be non positive!");
            return;
        }
        this.pricePerNight = price;
    }

    @Override
    public Integer getRank() {
        return this.rank;
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
        return this.openingHours.toString() + " - " + this.closingHours.toString();
    }

    public Integer getPricePerNight() {
        return this.pricePerNight;
    }
}
