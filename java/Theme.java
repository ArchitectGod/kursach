import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Theme {
    private String name;
    private String cellClosed;
    private String cellOpen;
    private String bomb;
    
    public Theme(String themeName) {
        this.name = themeName;
        switch (themeName) {
            case "classic":
                cellClosed = ".";
                cellOpen = " ";
                bomb = "*";
                break;
            case "modern":
                cellClosed = "■";
                cellOpen = "□";
                bomb = "💣";
                break;
            case "simple":
                cellClosed = "#";
                cellOpen = ".";
                bomb = "B";
                break;
            default:
                cellClosed = ".";
                cellOpen = " ";
                bomb = "*";
        }
    }
    
    public Theme() {
        this("classic");
    }
    
    public void print() {
        System.out.printf("Тема: %s%n", name);
        System.out.printf("Закрытая клетка: %s, Открытая: %s, Бомба: %s%n", 
                         cellClosed, cellOpen, bomb);
    }
    
    public String getCellClosed() { return cellClosed; }
    public String getCellOpen() { return cellOpen; }
    public String getBomb() { return bomb; }
    public String getName() { return name; }
}