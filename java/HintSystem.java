import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class HintSystem {
    private int hintsAvailable;
    private boolean hintUsed;

    public HintSystem() {
        this.hintsAvailable = 3;
        this.hintUsed = false;
    }

    public void print() {
        System.out.printf("Доступно подсказок: %d%n", hintsAvailable);
    }

    public Coordinate getHint(Board board) {
        if (hintUsed) {
            System.out.println("Подсказка уже использована в этом ходе.");
            return new Coordinate(-1, -1);
        }

        if (hintsAvailable <= 0) {
            System.out.println("Подсказки закончились!");
            return new Coordinate(-1, -1);
        }

        for (int y = 0; y < board.getHeight(); y++) {
            for (int x = 0; x < board.getWidth(); x++) {
                Cell cell = board.getCell(x, y);
                if (cell != null && !cell.getIsOpen() && !cell.getIsFlag() && !cell.getIsBomb()) {
                    hintsAvailable--;
                    hintUsed = true;
                    return new Coordinate(x, y);
                }
            }
        }

        System.out.println("Не найдено безопасных клеток для подсказки.");
        return new Coordinate(-1, -1);
    }

    public void addHints(int count) {
        hintsAvailable += count;
    }

    public int getHintsAvailable() { return hintsAvailable; }
    
    public void resetHintUsed() {
        hintUsed = false;
    }
}