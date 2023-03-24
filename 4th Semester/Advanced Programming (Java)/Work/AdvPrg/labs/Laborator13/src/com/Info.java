package com;

import java.sql.Date;
import java.text.DateFormat;
import java.text.DateFormatSymbols;
import java.text.MessageFormat;
import java.time.DayOfWeek;
import java.time.LocalDateTime;
import java.time.format.TextStyle;
import java.time.temporal.WeekFields;
import java.util.Calendar;
import java.util.Currency;
import java.util.Locale;
import java.util.ResourceBundle;

public class Info {
    ResourceBundle messages;
    public Info(ResourceBundle messages) {
        this.messages = messages;
        Locale currentLocale=Locale.getDefault();
        System.out.println(MessageFormat.format(messages.getString("info"),currentLocale));
        this.getCountry(currentLocale);
        this.getLanguage(currentLocale);
        this.getCurrency(currentLocale);
        this.getWeekDays(currentLocale);
        this.getMonths(currentLocale);
        this.getToday(currentLocale);

    }
    public Info(ResourceBundle messages, String localeString) {
        this.messages = messages;
        boolean localeFound=false;
        for(Locale locale:DisplayLocales.getAvailableLocales())
            if(locale.getDisplayLanguage().concat("-").concat(locale.getDisplayCountry()).equals(localeString)){
                localeFound=true;
                System.out.println(MessageFormat.format(messages.getString("info"),locale));
                this.getCountry(locale);
                this.getLanguage(locale);
                this.getCurrency(locale);
                this.getWeekDays(locale);
                this.getMonths(locale);
                this.getToday(locale);
                break;
            }
        if(!localeFound)
            System.out.println("Invalid locale.");
    }
    public void getCountry(Locale searchedLocale) {
        System.out.println(MessageFormat.format(messages.getString("country"), searchedLocale.getDisplayCountry(Locale.getDefault()))+" ("+ searchedLocale.getDisplayCountry(searchedLocale)+")");
    }
    public void getLanguage(Locale searchedLocale) {
        System.out.println(MessageFormat.format(messages.getString("language"), searchedLocale.getDisplayLanguage(Locale.getDefault()))+" ("+ searchedLocale.getDisplayLanguage(searchedLocale)+")");
    }
    public void getCurrency(Locale searchedLocale) {
        try {
            Currency currency = Currency.getInstance(searchedLocale);
            System.out.println(MessageFormat.format(messages.getString("currency"), currency.getDisplayName())+" ("+ currency.getDisplayName(searchedLocale)+")");
        }catch(IllegalArgumentException e){
            System.out.println("Currency not found.");
        }
    }
    public void getWeekDays(Locale searchedLocale){
        System.out.print(messages.getString("weekDays")+" ");
        WeekFields weekFields = WeekFields.of(searchedLocale);
        DayOfWeek day = weekFields.getFirstDayOfWeek();
        for (int i = 0; i < DayOfWeek.values().length; i++) {
            System.out.print(day.getDisplayName(TextStyle.FULL, searchedLocale));
            if(i<DayOfWeek.values().length-1)
                System.out.print(", ");
            day = day.plus(1);
        }
        System.out.println();
    }
    public void getMonths(Locale searchedLocale){
        System.out.print(messages.getString("months")+" ");
        DateFormatSymbols dfs = new DateFormatSymbols(searchedLocale);
        String[]months= dfs.getMonths();
        for (int i = 0; i < months.length; i++) {
            System.out.print(months[i]);
            if(i<months.length-2)
                System.out.print(", ");
        }
        System.out.println();
    }
    public void getToday(Locale searchedLocale){
        DateFormat df1 = DateFormat.getDateInstance(DateFormat.LONG, Locale.getDefault());
        Date date=new Date(System.currentTimeMillis());
        String formattedDate1 = df1.format(date);
        df1 = DateFormat.getDateInstance(DateFormat.LONG, searchedLocale);
        String formattedDate2 = df1.format(date);

        System.out.println(MessageFormat.format(messages.getString("today"), formattedDate1)+" ("+ formattedDate2+")");

    }
}
