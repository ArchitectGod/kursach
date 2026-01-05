import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

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
        System.out.println("Открытий клеток: " + safeMoves);
        System.out.println("Установок флагов: " + flagMoves);
        System.out.println("Ошибочных ходов: " + bombMoves);

        if (totalMoves > 0) {
            System.out.printf("Процент безопасных: %.1f%%%n", (float)safeMoves / totalMoves * 100);
            System.out.printf("Процент ошибок: %.1f%%%n", (float)bombMoves / totalMoves * 100);
        }
    }

    public void addSafeMove() {
        totalMoves++;
        safeMoves++;
    }

    public void addFlagMove() {
        totalMoves++;
        flagMoves++;
    }
	public void addBombMove() {
        totalMoves++;
        bombMoves++;
    }

    public void reset() {
        totalMoves = 0;
        safeMoves = 0;
        flagMoves = 0;
        bombMoves = 0;
    }

    public int getTotalMoves() { return totalMoves; }
    public float getSuccessRate() {
        if (totalMoves == 0) return 0.0f;
        return (float)safeMoves / totalMoves * 100;
    }
}
