import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 28. Тема оформления
class Theme {
    private String name;
    private String cellClosed;
    private String cellOpen;
    private String bomb;

    public Theme(String themeName) {
        this.name = themeName;
        if (themeName.equals("classic")) {
            this.cellClosed = ".";
            this.cellOpen = " ";
            this.bomb = "*";
        } else if (themeName.equals("modern")) {
            this.cellClosed = "■";
            this.cellOpen = "□";
            this.bomb = "💣";
        } else if (themeName.equals("simple")) {
            this.cellClosed = "#";
            this.cellOpen = " ";
            this.bomb = "X";
        }
    }
    
    public Theme() {
        this("classic");
    }

    public void print() {
        System.out.printf("Тема: %s%n", this.name);
        System.out.printf("Закрытая клетка: %s, Открытая клетка: %s, Бомба: %s%n",
            this.cellClosed, this.cellOpen, this.bomb);
    }

    public void inputSelectTheme(Scanner scanner) {
        System.out.print("Выберите тему (1-classic, 2-modern, 3-simple): ");
        int choice = scanner.nextInt();
        switch (choice) {
            case 1: this.name = "classic"; this.cellClosed = "."; this.cellOpen = " "; this.bomb = "*"; break;
            case 2: this.name = "modern"; this.cellClosed = "■"; this.cellOpen = "□"; this.bomb = "💣"; break;
            case 3: this.name = "simple"; this.cellClosed = "#"; this.cellOpen = " "; this.bomb = "X"; break;
        }
    }

    public String getCellClosed() { return this.cellClosed; }
    public String getCellOpen() { return this.cellOpen; }
    public String getBomb() { return this.bomb; }
}
