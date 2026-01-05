import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class Coordinate {
    private int x;
    private int y;

    public Coordinate(int xCoord, int yCoord) {
        this.x = xCoord;
        this.y = yCoord;
    }
    
    public Coordinate() {
        this(0, 0);
    }

    public void print() {
        System.out.printf("Координаты: (%d, %d)%n", x, y);
    }

    public void input(Scanner scanner) {
        System.out.print("Введите координаты X Y: ");
        this.x = scanner.nextInt();
        this.y = scanner.nextInt();
    }

    public int getX() { return x; }
    public int getY() { return y; }
    public void setX(int newX) { x = newX; }
    public void setY(int newY) { y = newY; }

    public boolean isValid(int maxX, int maxY) {
        return x >= 0 && x < maxX && y >= 0 && y < maxY;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Coordinate that = (Coordinate) obj;
        return x == that.x && y == that.y;
    }
}