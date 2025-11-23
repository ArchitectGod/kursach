import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 33. Система подсказок
class HintSystem {
    private int hintsAvailable;

    public HintSystem() {
        this.hintsAvailable = 3;
    }

    public void print() {
        System.out.printf("Система подсказок, доступно подсказок: %d%n", hintsAvailable);
    }

    public void inputUseHint(Scanner scanner) {
        System.out.print("Использовать подсказку? (1-да, 0-нет): ");
        int choice = scanner.nextInt();
        if (choice == 1 && hintsAvailable > 0) {
            hintsAvailable--;
            System.out.printf("Подсказка использована! Осталось: %d%n", hintsAvailable);
        }
    }

    public Coordinate getHint(Board board) {
        if (hintsAvailable > 0) {
            hintsAvailable--;

            for (int y = 0; y < board.getHeight(); y++) {
                for (int x = 0; x < board.getWidth(); x++) {
                    Cell cell = board.getCell(x, y);
                    if (cell != null && !cell.getIsOpen() && !cell.getIsBomb()) {
                        System.out.printf("Подсказка: безопасная клетка [%d,%d]%n", x, y);
                        return new Coordinate(x, y);
                    }
                }
            }
        } else {
            System.out.println("Подсказки закончились!");
        }
        return new Coordinate(-1, -1);
    }

    public void addHints(int count) {
        hintsAvailable += count;
        System.out.printf("Добавлено %d подсказок. Всего: %d%n", count, hintsAvailable);
    }
}