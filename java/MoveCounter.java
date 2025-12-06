import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 35. Счётчик ходов
class MoveCounter {
    private int totalMoves;
    private int safeMoves;
    private int flagMoves;
    private int bombMoves;

    public MoveCounter() {
        this.totalMoves = 0;
        this.safeMoves = 0;
        this.flagMoves = 0;
        this.bombMoves = 0;
    }

    public void print() {
        System.out.println("=== СТАТИСТИКА ХОДОВ ===");
        System.out.println("Всего ходов: " + this.totalMoves);
        System.out.println("Безопасных ходов: " + this.safeMoves);
        System.out.println("Установок флагов: " + this.flagMoves);
        System.out.println("Ходов на бомбах: " + this.bombMoves);

        if (this.totalMoves > 0) {
            System.out.printf("Процент безопасных: %.1f%%%n", (float)this.safeMoves / this.totalMoves * 100);
            System.out.printf("Процент ошибок: %.1f%%%n", (float)this.bombMoves / this.totalMoves * 100);
        }
    }

    public void inputReset(Scanner scanner) {
        System.out.print("Сбросить статистику? (1-да, 0-нет): ");
        int choice = scanner.nextInt();
        if (choice == 1) {
            this.reset();
            System.out.println("Статистика сброшена!");
        }
    }

    public void addSafeMove() {
        this.totalMoves++;
        this.safeMoves++;
        System.out.println("+1 безопасный ход");
    }

    public void addFlagMove() {
        this.totalMoves++;
        this.flagMoves++;
        System.out.println("+1 установка флага");
    }

    public void addBombMove() {
        this.totalMoves++;
        this.bombMoves++;
        System.out.println("+1 ход на бомбе (ОШИБКА!)");
    }
public void reset() {
        this.totalMoves = 0;
        this.safeMoves = 0;
        this.flagMoves = 0;
        this.bombMoves = 0;
    }

    public int getTotalMoves() { return this.totalMoves; }
    public int getSafeMoves() { return this.safeMoves; }
    public int getFlagMoves() { return this.flagMoves; }
    public int getBombMoves() { return this.bombMoves; }

    public float getSuccessRate() {
        if (this.totalMoves == 0) return 0.0f;
        return (float)this.safeMoves / this.totalMoves * 100;
    }
}

// Класс для демонстрации обработки исключений
class GameException extends Exception {
    public GameException(String message) {
        super(message);
    }
    
    public GameException(String message, Throwable cause) {
        super(message, cause);
    }
}
