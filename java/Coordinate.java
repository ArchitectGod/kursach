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
        super(region, danger); // Вызов конструктора базового класса
        this.x = xCoord;
        this.y = yCoord;
        this.setRazvedeno(explored); // Использование protected метода
        totalCoordinates++;
    }
    
    public Coordinate(int xCoord, int yCoord) {
        this(xCoord, yCoord, "Центральный", 1, false);
    }
    
    public Coordinate() {
        this(0, 0);
    }
    
    // Перегрузка метода базового класса (с вызовом метода базового класса)
    @Override
    public void pokazatInfo() {
        super.pokazatInfo(); // Вызов метода базового класса
        System.out.printf("Координаты: (%d, %d), Разведано: %s%n", 
                          x, y, getRazvedeno() ? "Да" : "Нет");
    }
    
    // Перегрузка метода базового класса (без вызова метода базового класса)
    @Override
    public void issledovatTerritoriyu() {
        // Специфичная для координат логика исследования
        if (!getRazvedeno()) {
            setRazvedeno(true);
            System.out.printf("Координата [%d,%d] исследована%n", x, y);
        }
    }
    
    // Виртуальный метод (в Java все методы виртуальные по умолчанию)
    public void virtualMethodDemo() {
        System.out.println("Виртуальный метод Coordinate: базовая реализация");
    }
    
    // Поверхностное клонирование
    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone(); // Поверхностное клонирование
    }
    
    // Глубокое клонирование
    public Coordinate deepClone() {
        return new Coordinate(this.x, this.y, this.nazvanieRegiona,this.urovenOpasnosti,this.getRazvedeno());
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