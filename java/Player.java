import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Player {
    private String name;
    private int timeSpent;
    private int openedCells;
    private int mistakes;
    private int bestTime;
    
    public Player(String name) {
        this.name = name;
        this.timeSpent = 0;
        this.openedCells = 0;
        this.mistakes = 0;
        this.bestTime = 0;
    }
    
    public Player() {
        this("");
    }
    
    public void print() {
        System.out.printf("Игрок: %s%n", name);
        System.out.printf("Время: %d сек, Открыто: %d, Ошибок: %d%n", 
                         timeSpent, openedCells, mistakes);
    }
    
    public void addMistake() { mistakes++; }
    public void addOpenedCell() { openedCells++; }
    
    public String getName() { return name; }
    public int getTimeSpent() { return timeSpent; }
    public int getOpenedCells() { return openedCells; }
    public int getMistakes() { return mistakes; }
    public int getBestTime() { return bestTime; }
    
    public void setTimeSpent(int time) { timeSpent = time; }
    public void setName(String newName) { name = newName; }
}