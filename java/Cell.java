import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class Cell {
    private boolean isBomb;
    private boolean isOpen;
    private boolean isFlag;
    private int countBomb;
    private int coordinateX;
    private int coordinateY;

    public Cell(int x, int y) {
        this.coordinateX = x;
        this.coordinateY = y;
        this.isBomb = false;
        this.isOpen = false;
        this.isFlag = false;
        this.countBomb = 0;
    }
    
    public Cell() {
        this(0, 0);
    }

    public void print() {
        System.out.printf("Клетка [%d,%d]: ", coordinateX, coordinateY);
        if (isOpen) {
            if (isBomb) {
                System.out.print("Бомба");
            } else {
                System.out.printf("Бомб вокруг: %d", countBomb);
            }
        } else if (isFlag) {
            System.out.print("Флаг");
        } else {
            System.out.print("Закрыта");
        }
        System.out.println();
    }

    public void inputFromUser(Scanner scanner) {
        System.out.printf("Введите состояние клетки [%d,%d] (0-закрыта, 1-открыта, 2-флаг): ", coordinateX, coordinateY);
        int state = scanner.nextInt();
        if (state == 1) {
            open();
        } else if (state == 2) {
            toggleFlag();
        }
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
    public int getX() { return coordinateX; }
    public int getY() { return coordinateY; }
    public void setIsOpen(boolean open) { isOpen = open; }
    public void setIsFlag(boolean flag) { isFlag = flag; }
    public void setIsBomb(boolean bomb) { isBomb = bomb; }
}