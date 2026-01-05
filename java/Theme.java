import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

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

    public String getCellClosed() { return cellClosed; }
    public String getCellOpen() { return cellOpen; }
    public String getBomb() { return bomb; }
}