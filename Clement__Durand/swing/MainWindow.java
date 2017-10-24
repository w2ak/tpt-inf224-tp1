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

  /**
   * \brief Main Window constructor
   *
   * Creates the main window with three buttons and
   * a text field.
   */
  public MainWindow() {
    /* Create actions */
    WriteTextAction addFoo = new WriteTextAction("write foo","foo\n");
    WriteTextAction addBar = new WriteTextAction("write bar","bar\n");
    ExitAction doExit = new ExitAction("exit",0);

    /* Create buttons for the lower zone */
    JPanel buttons = new JPanel();
    buttons.add(new JButton(addFoo));
    buttons.add(new JButton(addBar));
    buttons.add(new JButton(doExit));
    add(buttons, BorderLayout.SOUTH);

    /* Create a text zone */
    text = new JTextArea(5,20);
    JScrollPane textArea = new JScrollPane(text);
    add(textArea, BorderLayout.CENTER);

    /* Create the menu bar */
    JMenuBar menuBar = new JMenuBar();
    JMenu menu = menuBar.add(new JMenu("Write"));
    menu.add(addFoo);
    menu.add(addBar);
    setJMenuBar(menuBar);

    /* Create the tool bar with an exit button */
    JToolBar toolBar = new JToolBar();
    toolBar.add(doExit);
    add(toolBar, BorderLayout.NORTH);

    /* Wrap up */
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setTitle("Main Window");
    pack();
    setVisible(true);
  }

  public static void main(String[] args) {
    new MainWindow();
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
