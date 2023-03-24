package classes;

import org.assertj.core.api.Assert;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class AddressCorrectorTest {

    @Test
    void verifyIfCityExistsInDb() {
        AddressCorrector addressCorrector = new AddressCorrector("Country", "State", "Jurm");
        assertTrue(addressCorrector.verifyCityByName());
    }

    @Test
    void verifyIfCityDoesntExistsInDb() {
        AddressCorrector addressCorrector = new AddressCorrector("Country", "State", "Jwupads");
        assertFalse(addressCorrector.verifyCityByName());
    }

    @Test
    void verifyIfStateIsCorrect() {
        AddressCorrector addressCorrector = new AddressCorrector("Afghanistan", "Badakhshan", "Jurm");
        assertTrue(addressCorrector.verifyStateByName());
    }

    @Test
    void verifyIfCountryIsCorrect() {
        AddressCorrector addressCorrector = new AddressCorrector("Afghanistan", "Badakhshan", "Jurm");
        assertTrue(addressCorrector.verifyCountry());
    }

    @Test
    void verifyIfAddressIsChangedCorrectly() {
        AddressCorrector addressCorrector = new AddressCorrector("Afanistan", "Badakh", "Jurm");
        AddressCorrector correctAddress = new AddressCorrector("Afghanistan", "Badakhshan", "Jurm");
        addressCorrector.verifyCityByName();
        addressCorrector.setStateName();
        addressCorrector.setCountryName();
        assertEquals(correctAddress.getCountry(), addressCorrector.getCountry());
        assertEquals(correctAddress.getState(), addressCorrector.getState());
        assertEquals(correctAddress.getCity(), addressCorrector.getCity());
    }

}