package TTPP;

import java.time.LocalTime;
import java.util.*;

public class Restaurant extends Location implements Visitable, Classifiable{
    LocalTime openingHours;
    LocalTime closingHours;

    Integer rank;

    HashMap<String, Integer> menu;

    /**
     * The default constructor of the Location class.
     *
     * @param name The name of the location.
     */
    public Restaurant(String name) {
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

    public void addDishToMenu(String dishName, Integer dishCost) {
        if (dishCost <= 0) {
            System.out.println("The cost of a specific dish cannot be non positive!");
            return;
        }
        menu.put(dishName, dishCost);
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
        return this.openingHours + " - " + this.closingHours;
    }

    public Map<String, Integer> getMenu() {
        return this.menu;
    }
}
