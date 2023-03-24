package com.project.RouteSeeker;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

/**
 * Clasa care contine butoanele din partea de jos (exit,load,save)
 */

public class ControlPanel extends JPanel {
    final MainFrame frame;
    JButton exitBtn = new JButton("Exit");
    JButton loadBtn = new JButton("Load");
    JButton saveBtn = new JButton("Save");

    public ControlPanel(MainFrame frame) {
        this.frame = frame; init();
    }
    private void init() {
        setLayout(new GridLayout(1, 4));

        add(saveBtn, BorderLayout.CENTER);
        add(loadBtn, BorderLayout.CENTER);
        add(exitBtn, BorderLayout.CENTER);

        //configure listeners for all buttons
        exitBtn.addActionListener(this::exitGame);
        loadBtn.addActionListener(this::exitGame);
        saveBtn.addActionListener(this::saveGame);

    }
    private void exitGame(ActionEvent e) {
        frame.dispose();
    }
    private void saveGame(ActionEvent e) { frame.save();}

}