package panel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

public class ControlPanel extends JPanel {
    final MainFrame frame;
    JButton exitBtn = new JButton("Exit");

    public ControlPanel(MainFrame frame) {
        this.frame = frame;
        init();
    }

    private void init() {
        setLayout(new GridLayout(1, 1));
        add(exitBtn, BorderLayout.CENTER);
        exitBtn.addActionListener(this::exitGame);
        setOpaque(false);
    }

    private void exitGame(ActionEvent e) {
        frame.dispose();
    }
}
