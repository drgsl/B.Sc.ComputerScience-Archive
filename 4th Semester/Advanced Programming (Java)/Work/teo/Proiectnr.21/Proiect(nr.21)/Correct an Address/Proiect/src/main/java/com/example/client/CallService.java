package com.example.client;

import classes.Address;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.client.RestClientException;
import org.springframework.web.client.RestTemplate;

@RestController
public class CallService {
    final Logger log = LoggerFactory.getLogger(CallService.class);
    private String uri;

    public String verifyAddress(Address address) {
        try {
            uri = "http://localhost:8090/addresses/verify?country=" + address.getCountry() + "&state=" + address.getState() + "&city=" + address.getCity();
            RestTemplate restTemplate = new RestTemplate();
            ResponseEntity<String> response = restTemplate.exchange(uri, HttpMethod.POST, null, new ParameterizedTypeReference<String>() {
            });
            return response.getBody();
        } catch (RestClientException e) {
            return "Failed to connect to server!";
        }
    }

}
