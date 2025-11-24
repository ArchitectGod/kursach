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

    public Board(int w, int h, int bombs) {
        this.width = w;
        this.height = h;
        this.totalBombs = bombs;
        this.safeCellsLeft = w * h - bombs;
        this.cells = new ArrayList<>();
        this.bombsPlaced = false;
        
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

    public void inputBoardSize(Scanner scanner) {
        System.out.print("Введите размеры поля (ширина высота): ");
        this.width = scanner.nextInt();
        this.height = scanner.nextInt();
        System.out.print("Введите количество бомб: ");
        this.totalBombs = scanner.nextInt();

        cells.clear();
        safeCellsLeft = width * height - totalBombs;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cells.add(new Cell(x, y));
            }
        }
    }

    public Cell getCell(int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return cells.get(y * width + x);
        }
        return null;
    }

    public void decreaseSafeCells() {
        if (safeCellsLeft > 0) {
            safeCellsLeft--;
        }
    }

    public boolean isGameWon() {
        return safeCellsLeft == 0;
    }

    public void placeBombs(int firstX, int firstY) {
        if (bombsPlaced) return;
        
        Random rand = new Random();
        int bombsPlacedCount = 0;
        while (bombsPlacedCount < totalBombs) {
            int x = rand.nextInt(width);
            int y = rand.nextInt(height);

            if ((Math.abs(x - firstX) <= 1 && Math.abs(y - firstY) <= 1) ||
                getCell(x, y).getIsBomb()) {
                continue;
            }

            getCell(x, y).setBomb();
            bombsPlacedCount++;
        }
        calculateBombCounts();
        bombsPlaced = true;
    }

    public void calculateBombCounts() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Cell cell = getCell(x, y);
                if (!cell.getIsBomb()) {
                    int count = 0;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0) continue;
                            Cell neighbor = getCell(x + dx, y + dy);
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
        Cell cell = getCell(x, y);
        if (cell == null || cell.getIsOpen() || cell.getIsFlag()) return;

        cell.open();
        decreaseSafeCells();

        // Если вокруг нет бомб, открываем соседние клетки рекурсивно
        if (cell.getCountBomb() == 0) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue;
                    int newX = x + dx;
                    int newY = y + dy;
                    // Проверяем, что координаты в пределах поля
                    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                        openArea(newX, newY);
                    }
                }
            }
        }
    }

    public void revealAllBombs() {
        for (Cell cell : cells) {
            if (cell.getIsBomb()) {
                cell.open();
            }
        }
    }
public int getWidth() { return width; }
    public int getHeight() { return height; }
    public int getTotalBombs() { return totalBombs; }
    public int getSafeCellsLeft() { return safeCellsLeft; }
    public boolean areBombsPlaced() { return bombsPlaced; }
}