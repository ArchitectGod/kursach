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
            cellClosed = ".";
            cellOpen = " ";
            bomb = "*";
        } else if (themeName.equals("modern")) {
            cellClosed = "■";
            cellOpen = "□";
            bomb = "💣";
        } else if (themeName.equals("simple")) {
            cellClosed = "#";
            cellOpen = " ";
            bomb = "X";
        }
    }
    
    public Theme() {
        this("classic");
    }

    public void print() {
        System.out.printf("Тема: %s%n", name);
        System.out.printf("Закрытая клетка: %s, Открытая клетка: %s, Бомба: %s%n",
            cellClosed, cellOpen, bomb);
    }

    public void inputSelectTheme(Scanner scanner) {
        System.out.print("Выберите тему (1-classic, 2-modern, 3-simple): ");
        int choice = scanner.nextInt();
        switch (choice) {
            case 1: name = "classic"; cellClosed = "."; cellOpen = " "; bomb = "*"; break;
            case 2: name = "modern"; cellClosed = "■"; cellOpen = "□"; bomb = "💣"; break;
            case 3: name = "simple"; cellClosed = "#"; cellOpen = " "; bomb = "X"; break;
        }
    }

    public String getCellClosed() { return cellClosed; }
    public String getCellOpen() { return cellOpen; }
    public String getBomb() { return bomb; }
}