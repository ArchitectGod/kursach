import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Settings {
    private boolean autoBombs;
    private boolean sounds;
    private int difficulty;
    
    public Settings() {
        this.autoBombs = true;
        this.sounds = true;
        this.difficulty = 0;
    }
    
    public void print() {
        System.out.println("=== НАСТРОЙКИ ===");
        System.out.println("Авторасстановка бомб: " + (autoBombs ? "Вкл" : "Выкл"));
        System.out.println("Звуки: " + (sounds ? "Вкл" : "Выкл"));
        System.out.print("Сложность: ");
        switch (difficulty) {
            case 0: System.out.println("Легко"); break;
            case 1: System.out.println("Средне"); break;
            case 2: System.out.println("Сложно"); break;
        }
    }
    
    public Board createBoardByDifficulty() {
        switch (difficulty) {
            case 0: return new Board(9, 9, 10);
            case 1: return new Board(16, 16, 40);
            case 2: return new Board(30, 16, 99);
            default: return new Board(9, 9, 10);
        }
    }
    
    public boolean getAutoBombs() { return autoBombs; }
    public boolean getSounds() { return sounds; }
    public int getDifficulty() { return difficulty; }
    
    public void setDifficulty(int level) { difficulty = level; }
}
