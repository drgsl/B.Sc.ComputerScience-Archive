package com.example.compulsory;

import classes.AddressCorrector;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/addresses")
public class Controllers {
    AddressCorrector address;

    @PostMapping("/verify")
    public String create(@RequestParam String country, @RequestParam String state, @RequestParam String city) {
        String response = "";

        this.address = new AddressCorrector(country, state, city);

        if (!this.address.verifyCountry()) {
            if (!this.address.verifyStateByName()) {
                if (!this.address.verifyCityByName()) {
                    response = "Nothing from this address can be found in the database!";
                } else {
                    this.address.setStateName();
                    this.address.setCountryName();
                    response = "CORRECT: City: " + this.address.getCity() + " State: " + this.address.getState() + " Country: " + this.address.getCountry();
                }
            } else {
                this.address.setCountryName();
                this.address.setCityName();
                response = "CORRECT: City: " + this.address.getCity() + " State: " + this.address.getState() + " Country: " + this.address.getCountry();
            }
        } else if (!this.address.verifyState()) {
            if (!this.address.verifyCityByName()) {
                response = "The city and the state doesn't exist!";
            } else {
                this.address.setStateName();
                response = "CORRECT: City: " + this.address.getCity() + " State: " + this.address.getState() + " Country: " + this.address.getCountry();
            }

        } else if (!this.address.verifyCity()) {
            response = "City doesn't exist!";
        } else {
            response = "Address is correct " + this.address.getCity() + " " + this.address.getState() + " " + this.address.getCountry();
        }

        return response;
    }

}
