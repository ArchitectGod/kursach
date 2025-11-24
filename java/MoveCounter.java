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
        System.out.println("Всего ходов: " + totalMoves);
        System.out.println("Безопасных ходов: " + safeMoves);
        System.out.println("Установок флагов: " + flagMoves);
        System.out.println("Ходов на бомбах: " + bombMoves);

        if (totalMoves > 0) {
            System.out.printf("Процент безопасных: %.1f%%%n", (float)safeMoves / totalMoves * 100);
            System.out.printf("Процент ошибок: %.1f%%%n", (float)bombMoves / totalMoves * 100);
        }
    }

    public void inputReset(Scanner scanner) {
        System.out.print("Сбросить статистику? (1-да, 0-нет): ");
        int choice = scanner.nextInt();
        if (choice == 1) {
            reset();
            System.out.println("Статистика сброшена!");
        }
    }

    public void addSafeMove() {
        totalMoves++;
        safeMoves++;
        System.out.println("+1 безопасный ход");
    }

    public void addFlagMove() {
        totalMoves++;
        flagMoves++;
        System.out.println("+1 установка флага");
    }

    public void addBombMove() {
        totalMoves++;
        bombMoves++;
        System.out.println("+1 ход на бомбе (ОШИБКА!)");
    }

    public void reset() {
        totalMoves = 0;
        safeMoves = 0;
        flagMoves = 0;
        bombMoves = 0;
    }

    public int getTotalMoves() { return totalMoves; }
    public int getSafeMoves() { return safeMoves; }
    public int getFlagMoves() { return flagMoves; }
    public int getBombMoves() { return bombMoves; }

    public float getSuccessRate() {
        if (totalMoves == 0) return 0.0f;
        return (float)safeMoves / totalMoves * 100;
    }
}
