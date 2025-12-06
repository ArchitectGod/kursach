import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 1. Класс координат
class Coordinate {
    private int x;
    private int y;

    public Coordinate(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    public Coordinate() {
        this(0, 0);
    }

    public void print() {
        System.out.printf("Координаты: (%d, %d)%n", this.x, this.y);
    }

    public void input(Scanner scanner) {
        System.out.print("Введите координаты X Y: ");
        this.x = scanner.nextInt();
        this.y = scanner.nextInt();
    }

    public int getX() { return this.x; }
    public int getY() { return this.y; }
    public void setX(int newX) { this.x = newX; }
    public void setY(int newY) { this.y = newY; }

    public boolean isValid(int maxX, int maxY) {
        return this.x >= 0 && this.x < maxX && this.y >= 0 && this.y < maxY;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || this.getClass() != obj.getClass()) return false;
        Coordinate that = (Coordinate) obj;
        return this.x == that.x && this.y == that.y;
    }
}