import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Cell {
    private boolean isBomb;
    private boolean isOpen;
    private boolean isFlag;
    private int countBomb;
    private Coordinate coordinate;
    
    public Cell(int x, int y) {
        this.coordinate = new Coordinate(x, y);
        this.isBomb = false;
        this.isOpen = false;
        this.isFlag = false;
        this.countBomb = 0;
    }
    
    public Cell() {
        this(0, 0);
    }
    
    public void print() {
        System.out.printf("Клетка ");
        coordinate.print();
        System.out.print("Состояние: ");
        if (isOpen) {
            if (isBomb) System.out.print("💣 БОМБА");
            else System.out.printf("📊 %d бомб вокруг", countBomb);
        } else if (isFlag) {
            System.out.print("🚩 ФЛАГ");
        } else {
            System.out.print("⬜ ЗАКРЫТА");
        }
        System.out.println();
    }
    
    public void open() {
        if (!isOpen) {
            isOpen = true;
            isFlag = false;
        }
    }
    
    public void toggleFlag() {
        if (!isOpen) {
            isFlag = !isFlag;
        }
    }
    
    public void setBomb() {
        isBomb = true;
    }
    
    public void setCountBomb(int count) {
        countBomb = count;
    }
    
    public boolean getIsBomb() { return isBomb; }
    public boolean getIsOpen() { return isOpen; }
    public boolean getIsFlag() { return isFlag; }
    public int getCountBomb() { return countBomb; }
    public int getX() { return coordinate.getX(); }
    public int getY() { return coordinate.getY(); }
}