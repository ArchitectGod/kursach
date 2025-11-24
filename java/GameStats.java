import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 11. Класс статистики игр
class GameStats {
    private int gamesPlayed;
    private int gamesWon;
    private int totalTime;
    private int bestTime;

    public GameStats() {
        this.gamesPlayed = 0;
        this.gamesWon = 0;
        this.totalTime = 0;
        this.bestTime = 0;
    }

    public void print() {
        System.out.println("=== СТАТИСТИКА ===");
        System.out.println("Игр сыграно: " + gamesPlayed);
        System.out.println("Побед: " + gamesWon);
        System.out.println("Лучшее время: " + bestTime + " сек");
        System.out.printf("Среднее время: %.1f сек%n", gamesPlayed > 0 ? (float) totalTime / gamesPlayed : 0);
    }

    public void inputReset(Scanner scanner) {
        System.out.print("Сбросить статистику? (1-да, 0-нет): ");
        int choice = scanner.nextInt();
        if (choice == 1) reset();
    }

    public void addGame(boolean won, int time) {
        gamesPlayed++;
        if (won) gamesWon++;
        totalTime += time;
        if (won && (time < bestTime || bestTime == 0)) {
            bestTime = time;
        }
    }

    public void reset() {
        gamesPlayed = 0;
        gamesWon = 0;
        totalTime = 0;
        bestTime = 0;
    }
}