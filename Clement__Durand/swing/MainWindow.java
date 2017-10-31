import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * \class MainWindow
 * \brief Class for the Main window.
 */
public class MainWindow extends JFrame {
  private static final long serialVersionUID = 1L;

  JTextArea text;
  JTextField textField;
  Client c;

  /**
   * \brief Main Window constructor
   *
   * Creates the main window with three buttons and
   * a text field.
   */
  public MainWindow(Client c) {
    this.c = c;

    /* Create actions */
    WriteTextAction addFoo = new WriteTextAction("write foo","foo\n");
    WriteTextAction addBar = new WriteTextAction("write bar","bar\n");
    CommandAction searchFile = new CommandAction("search file","fileInfo");
    CommandAction searchGroup = new CommandAction("search group","groupInfo");
    CommandAction play = new CommandAction("play","play");
    ExitAction doExit = new ExitAction("exit",0);

    /* Create buttons for the lower zone */
    JPanel buttons = new JPanel();
    buttons.add(new JButton(searchFile));
    buttons.add(new JButton(searchGroup));
    buttons.add(new JButton(play));
    add(buttons, BorderLayout.SOUTH);

    /* Create a text zone */
    text = new JTextArea(5,20);
    JScrollPane textArea = new JScrollPane(text);
    add(textArea, BorderLayout.CENTER);

    /* Create a text field */
    textField = new JTextField(20);
    textField.addActionListener(play);
    add(textField, BorderLayout.NORTH);

    /* Create the menu bar */
    JMenu menu = null;
    JMenuBar menuBar = new JMenuBar();
    menu = menuBar.add(new JMenu("File"));
    menu.add(doExit);
    menu = menuBar.add(new JMenu("Media"));
    menu.add(searchFile);
    menu.add(searchGroup);
    menu.add(play);
    menu = menuBar.add(new JMenu("Write"));
    menu.add(addFoo);
    menu.add(addBar);
    setJMenuBar(menuBar);

    /* Wrap up */
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setTitle("Main Window");
    pack();
    setVisible(true);
  }

  public static void main(String[] args) {
    try {
      Client c = new Client("localhost",3331);
      new MainWindow(c);
    } catch (Exception e) {
      e.printStackTrace();
      System.exit(1);
    }
  }

  /**
   * \class WriteTextAction
   *
   * \brief Action class for buttons writing text.
   */
  class WriteTextAction extends AbstractAction {
    private static final long serialVersionUID = 1L;
    private String txt;

    public WriteTextAction(String label, String text) {
      super(label);
      this.txt = text;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
      text.append(txt);
    }
  }

  /**
   * \class CommandAction
   *
   * \brief Sends a command to the server.
   */
  class CommandAction extends AbstractAction {
    private static final long serialVersionUID = 1L;
    private String cmd;

    public CommandAction(String label, String cmd) {
      super(label);
      this.cmd = cmd;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
      text.setText(c.send(cmd + " " + textField.getText()).replaceAll(";","\n"));
    }
  }

  /**
   * \class ExitAction
   *
   * \brief Action class for exit buttons.
   */
  class ExitAction extends AbstractAction {
    private static final long serialVersionUID = 1L;
    private int code;

    public ExitAction(String label, int code) {
      super(label);
      this.code = code;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
      System.exit(code);
    }
  }
}
