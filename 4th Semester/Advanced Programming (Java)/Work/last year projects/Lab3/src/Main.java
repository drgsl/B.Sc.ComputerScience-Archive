import TTPP.*;
import java.time.*;

public class Main {
    public static void main(String[] args) {
        City iasi = new City("Iasi");

        Hotel hotel = new Hotel("Hotel");
        Museum museumA = new Museum("Museum A", "Art");
        Museum museumB = new Museum("Museum B", "War");
        Church churchA = new Church("Church A", "Orthodox");
        Church churchB = new Church("Church B", "Catholic");
        Restaurant restaurant = new Restaurant("Restaurant");

        iasi.addLocation(hotel);
        iasi.addLocation(museumA);
        iasi.addLocation(museumB);
        iasi.addLocation(churchA);
        iasi.addLocation(churchB);
        iasi.addLocation(restaurant);

        hotel.setOpeningHours(LocalTime.parse("08:00"));
        hotel.setClosingHours(LocalTime.parse("21:00"));

        museumA.setOpeningHours(LocalTime.parse("10:00"));
        museumA.setClosingHours(LocalTime.parse("18:00"));
        museumB.setOpeningHours(LocalTime.parse("09:30"));
        museumB.setClosingHours(LocalTime.parse("19:00"));

        churchA.setOpeningHours(LocalTime.parse("06:00"));
        churchA.setClosingHours(LocalTime.parse("22:00"));
        churchB.setOpeningHours(LocalTime.parse("07:00"));
        churchB.setClosingHours(LocalTime.parse("23:00"));

        restaurant.setOpeningHours(LocalTime.parse("16:00"));
        restaurant.setClosingHours(LocalTime.parse("04:00"));


        hotel.addCost(museumA, 10);
        hotel.addCost(museumB, 50);
        museumA.addCost(museumB, 20);
        museumA.addCost(churchA, 20);
        museumA.addCost(churchB, 10);
        museumB.addCost(churchA, 20);
        museumB.addCost(museumA, 20);
        churchA.addCost(churchB, 30);
        churchA.addCost(restaurant, 10);
        churchB.addCost(churchA, 30);
        churchB.addCost(restaurant, 20);


        iasi.displayVisitableAndNotPayable();

        TravelPlan TP = new TravelPlan(iasi);
        TP.addPreferenceForLocation(hotel);
        TP.addPreferenceForLocation(museumA);
        TP.addPreferenceForLocation(museumB);
        TP.addPreferenceForLocation(churchA);
        TP.addPreferenceForLocation(churchB);
        TP.addPreferenceForLocation(restaurant);

        System.out.println("\nShortest distance between hotel and restaurant " + TP.getShortestPathBetween(hotel, restaurant));
    }
}
