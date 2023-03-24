package com;

import java.util.ArrayList;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

public class DisplayLocales {
    private final static List<Locale> availableLocales= Arrays.stream(Locale.getAvailableLocales()).collect(Collectors.toList());
    public DisplayLocales(){
        for (Locale locale : availableLocales)
            if(!locale.getLanguage().isEmpty() && !locale.getCountry().isEmpty()){
                System.out.print(locale.getDisplayLanguage()+"-"+locale.getDisplayCountry() + "\n");
            }
        System.out.println();
    }

    public static List<Locale> getAvailableLocales() {
        return availableLocales;
    }
}
