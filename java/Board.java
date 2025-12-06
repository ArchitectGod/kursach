import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 3. Класс игрового поля
class Board {
    private int width;
    private int height;
    private int totalBombs;
    private int safeCellsLeft;
    private List<Cell> cells;
    private boolean bombsPlaced;

    private static int boardsCreated = 0;
    
    public static int getBoardsCreated() {
        return boardsCreated;
    }

    public Board(int w, int h, int bombs) {
        this.width = w;
        this.height = h;
        this.totalBombs = bombs;
        this.safeCellsLeft = w * h - bombs;
        this.cells = new ArrayList<>();
        this.bombsPlaced = false;
        
        boardsCreated++;
        
        for (int y = 0; y < this.height; y++) {
            for (int x = 0; x < this.width; x++) {
                this.cells.add(new Cell(x, y));
            }
        }
    }
public void print() {
        System.out.print("   ");
        for (int x = 0; x < this.width; x++) {
            System.out.printf("%2d ", x);
        }
        System.out.println();

        for (int y = 0; y < this.height; y++) {
            System.out.printf("%2d ", y);
            for (int x = 0; x < this.width; x++) {
                Cell cell = this.cells.get(y * this.width + x);
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

    public void inputBoardSize(Scanner scanner) {
        System.out.print("Введите размеры поля (ширина высота): ");
        this.width = scanner.nextInt();
        this.height = scanner.nextInt();
        System.out.print("Введите количество бомб: ");
        this.totalBombs = scanner.nextInt();

        this.cells.clear();
        this.safeCellsLeft = this.width * this.height - this.totalBombs;
        for (int y = 0; y < this.height; y++) {
            for (int x = 0; x < this.width; x++) {
                this.cells.add(new Cell(x, y));
            }
        }
    }

    public Cell getCell(int x, int y) {
        if (x >= 0 && x < this.width && y >= 0 && y < this.height) {
            return this.cells.get(y * this.width + x);
        }
        return null;
    }

    public void decreaseSafeCells() {
        if (this.safeCellsLeft > 0) {
            this.safeCellsLeft--;
        }
    }

    public boolean isGameWon() {
        return this.safeCellsLeft == 0;
    }

    public void placeBombs(int firstX, int firstY) {
        if (this.bombsPlaced) return;
        
        Random rand = new Random();
        int bombsPlacedCount = 0;
        while (bombsPlacedCount < this.totalBombs) {
            int x = rand.nextInt(this.width);
            int y = rand.nextInt(this.height);

            if ((Math.abs(x - firstX) <= 1 && Math.abs(y - firstY) <= 1) ||
                this.getCell(x, y).getIsBomb()) {
                continue;
            }

            this.getCell(x, y).setBomb();
            bombsPlacedCount++;
        }
        this.calculateBombCounts();
        this.bombsPlaced = true;
    }

    public void calculateBombCounts() {
        for (int y = 0; y < this.height; y++) {
            for (int x = 0; x < this.width; x++) {
                Cell cell = this.getCell(x, y);
                if (!cell.getIsBomb()) {
                    int count = 0;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0) continue;
                            Cell neighbor = this.getCell(x + dx, y + dy);
                            if (neighbor != null && neighbor.getIsBomb()) {
                                count++;
                            }
                        }
                    }
                    cell.setCountBomb(count);
                }
            }
        }
    }

    public void openArea(int x, int y) {
        Cell cell = this.getCell(x, y);
        if (cell == null || cell.getIsOpen() || cell.getIsFlag()) return;

        cell.open();
        this.decreaseSafeCells();

        if (cell.getCountBomb() == 0) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue;
                    int newX = x + dx;
                    int newY = y + dy;
                    if (newX >= 0 && newX < this.width && newY >= 0 && newY < this.height) {
                        this.openArea(newX, newY);
                    }
                }
            }
        }
    }
public void revealAllBombs() {
        for (Cell cell : this.cells) {
            if (cell.getIsBomb()) {
                cell.open();
            }
        }
    }

    public int getWidth() { return this.width; }
    public int getHeight() { return this.height; }
    public int getTotalBombs() { return this.totalBombs; }
    public int getSafeCellsLeft() { return this.safeCellsLeft; }
    public boolean areBombsPlaced() { return this.bombsPlaced; }
}