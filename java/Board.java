import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Board {
    private int width;
    private int height;
    private int totalBombs;
    private int safeCellsLeft;
    private List<Cell> cells;
    
    public Board(int width, int height, int bombs) {
        this.width = width;
        this.height = height;
        this.totalBombs = bombs;
        this.safeCellsLeft = width * height - bombs;
        this.cells = new ArrayList<>();
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cells.add(new Cell(x, y));
            }
        }
    }
    
    public void print() {
        System.out.print("   ");
        for (int x = 0; x < width; x++) {
            System.out.printf("%2d ", x);
        }
        System.out.println();

        for (int y = 0; y < height; y++) {
            System.out.printf("%2d ", y);
            for (int x = 0; x < width; x++) {
                Cell cell = cells.get(y * width + x);
                if (cell.getIsOpen()) {
                    if (cell.getIsBomb()) {
                        System.out.print(" * ");
                    } else {
                        System.out.printf(" %d ", cell.getCountBomb());
                    }
                } else if (cell.getIsFlag()) {
                    System.out.print(" F ");
                } else {
                    System.out.print(" . ");
                }
            }
            System.out.println();
        }
    }
    
    public Cell getCell(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return cells.get(y * width + x);
        }
        return null;
    }
    
    public int getWidth() { return width; }
    public int getHeight() { return height; }
    public int getTotalBombs() { return totalBombs; }
}
