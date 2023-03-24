package classes;

public class Address {
    private String city;
    private String state;
    private String country;
    private int stateId;
    private int countryId;

    public Address(String city, String state, String country) {
        this.city = city;
        this.state = state;
        this.country = country;
        this.countryId = 0;
        this.stateId = 0;
    }

    public String getCity() {
        return city;
    }

    public String getState() {
        return state;
    }

    public String getCountry() {
        return country;
    }
}
