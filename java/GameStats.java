import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

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
        System.out.printf("Процент побед: %.1f%%%n", gamesPlayed > 0 ? (float)gamesWon / gamesPlayed * 100 : 0);
        System.out.println("Лучшее время: " + bestTime + " сек");
        System.out.printf("Среднее время: %.1f сек%n", gamesPlayed > 0 ? (float) totalTime / gamesPlayed : 0);
    }

    public void addGame(boolean won, int time) {
        gamesPlayed++;
        if (won) {
            gamesWon++;
            totalTime += time;
            if (time < bestTime || bestTime == 0) {
                bestTime = time;
            }
        }
    }

    public void reset() {
        gamesPlayed = 0;
        gamesWon = 0;
        totalTime = 0;
        bestTime = 0;
    }

    public void saveToFile(String filename) {
        try (PrintWriter file = new PrintWriter(new FileWriter(filename, true))) {
            String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
            file.println("Статистика от " + timestamp);
            file.println("Игр сыграно: " + gamesPlayed);
            file.println("Побед: " + gamesWon);
            file.println("Лучшее время: " + bestTime + " сек");
            file.println("-----------------");
        } catch (IOException e) {
            System.out.println("Ошибка сохранения статистики: " + e.getMessage());
        }
    }
}