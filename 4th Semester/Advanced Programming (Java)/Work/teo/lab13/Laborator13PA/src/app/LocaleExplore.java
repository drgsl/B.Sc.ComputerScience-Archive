package app;

import com.DisplayLocales;
import com.Info;
import com.SetLocale;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.MessageFormat;
import java.util.Locale;
import java.util.ResourceBundle;


public class LocaleExplore {

    public static void main(String[] args) throws IOException {
        String language;
        String country;

        if (args.length != 2) {
            language = "en";
            country = "US";
        } else {
            language = args[0];
            country = args[1];
        }

        Locale currentLocale;
        ResourceBundle messages;

        currentLocale = new Locale(language, country);
        messages = ResourceBundle.getBundle("res/Messages", currentLocale);

        while(true){
            System.out.print(messages.getString("prompt")+" ");
            BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
            String input= reader.readLine();
            int spaceIndex=input.indexOf(" ");
            String command;
            if(spaceIndex>0)
                command=input.substring(0,spaceIndex);
            else
                command=input;
            switch (command) {
                case "displayLocales" -> {
                    System.out.println(messages.getString("locales"));
                    new DisplayLocales();
                }
                case "setLocale" -> {
                    String locale;
                    if(spaceIndex>0)
                        locale = input.substring(spaceIndex+1);
                    else
                        break;
                    new SetLocale(locale);
                    currentLocale=new Locale(Locale.getDefault().getLanguage(),Locale.getDefault().getCountry());
                    messages = ResourceBundle.getBundle("res/Messages", currentLocale);
                    System.out.println(MessageFormat.format(messages.getString("locale.set"),currentLocale));
                }
                case "info" ->{
                    Info about;
                    if(spaceIndex<=0)
                        about=new Info(messages);
                    else
                        about=new Info(messages,input.substring(spaceIndex+1)); //info about a specific locale

                }
                default -> System.out.println(messages.getString("invalid"));
            }

        }
        }


}
