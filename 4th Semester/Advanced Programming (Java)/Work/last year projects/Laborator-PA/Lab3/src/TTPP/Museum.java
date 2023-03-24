package TTPP;

import java.time.LocalTime;

public class Museum extends Location implements Visitable, Payable, Classifiable{
    LocalTime openingHours;
    LocalTime closingHours;

    Integer entryFee;

    Integer rank;

    final String domain;

    public Museum(String name, String domain) {
        super(name);
        this.domain = domain;
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
    public void setEntryFee(Integer entryFee) {
        if (entryFee < 0) {
            System.out.println("Error! The entry fee cannot be below 0!");
            return;
        }
        this.entryFee = entryFee;
    }

    @Override
    public void setRank(Integer rank) {
        if (rank <= 0) {
            System.out.println("The rank must be a positive integer!");
            return;
        }
        this.rank = rank;
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

    @Override
    public Integer getEntryFee() {
        return this.entryFee;
    }

    @Override
    public Integer getRank() {
        return this.rank;
    }

    public String getDomain() {
        return this.getDomain();
    }
}
