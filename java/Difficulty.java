import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Difficulty extends Geografiya {
    private int width;
    private int height;
    private int bombs;
    
    public Difficulty(String level, int w, int h, int b) {
        super("Уровень " + level, b / 10);
        this.width = w;
        this.height = h;
        this.bombs = b;
    }
    
    public void print() {
        System.out.printf("Уровень сложности: %s (%dx%d, %d бомб)%n", 
                         getNazvanieRegiona(), width, height, bombs);
    }
    
    @Override
    public void pokazatInfo() {
        System.out.printf("Сложность: %s, Бомб: %d, Опасность: %d/10%n", 
                         getNazvanieRegiona(), bombs, getUrovenOpasnosti());
    }
    
    public int getWidth() { return width; }
    public int getHeight() { return height; }
    public int getBombs() { return bombs; }
}