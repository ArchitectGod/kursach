import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 31. Рекорд
class HighScore {
    private String playerName;
    private int score;
    private int time;
    private String difficulty;

    public HighScore(String name, int s, int t, String diff) {
        this.playerName = name;
        this.score = s;
        this.time = t;
        this.difficulty = diff;
    }
    
    public HighScore() {
        this("", 0, 0, "");
    }

    public void print() {
        System.out.printf("Рекорд: %s - %d очков, время: %d сек, сложность: %s%n",
            playerName, score, time, difficulty);
    }

    public void inputHighScore(Scanner scanner) {
        System.out.println("Введите данные рекорда:");
        System.out.print("Имя: ");
        this.playerName = scanner.next();
        System.out.print("Очки: ");
        this.score = scanner.nextInt();
        System.out.print("Время (сек): ");
        this.time = scanner.nextInt();
        System.out.print("Сложность: ");
        this.difficulty = scanner.next();
    }

    public int getScore() { return score; }
}