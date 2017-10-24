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

  JButton fstText;
  JButton sndText;
  JButton exit;
  JTextArea text;
  JScrollPane textArea;
  JPanel buttons;

  JMenuBar menuBar;
  JMenu menu;
  JToolBar toolBar;

  /**
   * \brief Main Window constructor
   *
   * Creates the main window with three buttons and
   * a text field.
   */
  public MainWindow() {
    WriteTextAction addFoo = new WriteTextAction("write foo","foo\n");
    WriteTextAction addBar = new WriteTextAction("write bar","bar\n");
    ExitAction doExit = new ExitAction("exit",0);

    buttons = new JPanel();
    fstText = new JButton(addFoo);
    buttons.add(fstText);
    sndText = new JButton(addBar);
    buttons.add(sndText);
    exit = new JButton(doExit);
    buttons.add(exit);
    add(buttons, BorderLayout.SOUTH);

    text = new JTextArea(5,20);
    textArea = new JScrollPane(text);
    add(textArea, BorderLayout.CENTER);

    menuBar = new JMenuBar();
    menu = menuBar.add(new JMenu("Write"));
    menu.add(addFoo);
    menu.add(addBar);
    setJMenuBar(menuBar);

    toolBar = new JToolBar();
    toolBar.add(doExit);
    add(toolBar, BorderLayout.NORTH);

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
