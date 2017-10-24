import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class MainWindow extends JFrame {
  private static final long serialVersionUID = 1L;

  JButton fstText;
  JButton sndText;
  JButton exit;
  JTextArea text;
  JScrollPane textArea;
  JPanel buttons;

  public MainWindow() {
    buttons = new JPanel();
    fstText = new JButton("foo");
    buttons.add(fstText);
    sndText = new JButton("bar");
    buttons.add(sndText);
    exit = new JButton("exit");
    buttons.add(exit);
    add(buttons, BorderLayout.SOUTH);

    text = new JTextArea(5,20);
    textArea = new JScrollPane(text);
    add(textArea, BorderLayout.CENTER);

    fstText.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        text.append("foo\n");
      }
    });

    sndText.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        text.append("bar\n");
      }
    });

    exit.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        System.exit(0);
      }
    });

    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setTitle("Main Window");
    pack();
    setVisible(true);
  }

  public static void main(String[] args) {
    new MainWindow();
  }
}
