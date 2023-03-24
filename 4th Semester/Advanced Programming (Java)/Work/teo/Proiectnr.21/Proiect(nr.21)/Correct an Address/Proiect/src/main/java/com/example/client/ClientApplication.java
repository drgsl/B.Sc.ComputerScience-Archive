package com.example.client;

import org.springframework.boot.autoconfigure.SpringBootApplication;
import panel.MainFrame;

@SpringBootApplication
public class ClientApplication {

    public static void main(String[] args) {

        new MainFrame().setVisible(true);
    }

}
