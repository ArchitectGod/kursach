import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Coordinate extends Geografiya implements Cloneable {
    private int x;
    private int y;
    private static int totalCoordinates = 0;
    
    public Coordinate(int xCoord, int yCoord, String region, int danger, boolean explored) {
        super(region, danger);
        this.x = xCoord;
        this.y = yCoord;
        this.setRazvedeno(explored);
        totalCoordinates++;
    }
    
    public Coordinate(int xCoord, int yCoord) {
        this(xCoord, yCoord, "Центральный", 1, false);
    }
    
    public Coordinate() {
        this(0, 0);
    }
    
    @Override
    public void pokazatInfo() {
        super.pokazatInfo();
        System.out.printf("Координаты: (%d, %d), Разведано: %s%n", 
                          x, y, getRazvedeno() ? "Да" : "Нет");
    }
    
    @Override
    public void issledovatTerritoriyu() {
        if (!getRazvedeno()) {
            setRazvedeno(true);
            System.out.printf("Координата [%d,%d] исследована%n", x, y);
        }
    }
    
    public void virtualMethodDemo() {
        System.out.println("Виртуальный метод Coordinate: базовая реализация");
    }
    
    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
    
    public Coordinate deepClone() {
        return new Coordinate(this.x, this.y, 
                             this.nazvanieRegiona, 
                             this.urovenOpasnosti, 
                             this.getRazvedeno());
    }
    
    public void print() {
        System.out.printf("Координата [%d,%d]: ", x, y);
        pokazatInfo();
    }
    
    public int getX() { return x; }
    public int getY() { return y; }
    
    public void setX(int newX) { x = newX; }
    public void setY(int newY) { y = newY; }
    
    public boolean isValid(int maxX, int maxY) {
        return x >= 0 && x < maxX && y >= 0 && y < maxY;
    }
    
    public static int getTotalCoordinates() {
        return totalCoordinates;
    }
}