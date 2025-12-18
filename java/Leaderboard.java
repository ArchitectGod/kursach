import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Leaderboard {
    private String name;
    private int time;
    private int height;
    private int width;
    private int bombs;
    private int day;
    private int month;
    private int year;
    private boolean win;
    
    public Leaderboard(String playerName, int time, int width, int height, 
                      int bombs, boolean victory) {
        this.name = playerName;
        this.time = time;
        this.width = width;
        this.height = height;
        this.bombs = bombs;
        this.win = victory;
        
        LocalDateTime now = LocalDateTime.now();
        this.day = now.getDayOfMonth();
        this.month = now.getMonthValue();
        this.year = now.getYear();
    }
    
    public void print() {
        System.out.printf("%s: %d сек, %dx%d, %s%n", 
                         name, time, width, height, 
                         win ? "ПОБЕДА" : "ПРОИГРЫШ");
    }
    
    public void saveToFile(String filename) {
        try (PrintWriter file = new PrintWriter(new FileWriter(filename, true))) {
            file.printf("%s,%d,%d,%d,%d,%d,%d,%d,%d%n",
                       name, time, height, width, bombs,
                       day, month, year, win ? 1 : 0);
        } catch (IOException e) {
            System.out.println("Ошибка сохранения: " + e.getMessage());
        }
    }
}