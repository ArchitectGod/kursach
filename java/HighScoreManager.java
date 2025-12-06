import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 32. Менеджер рекордов
class HighScoreManager {
    private List<HighScore> highScores;

    public HighScoreManager() {
        this.highScores = new ArrayList<>();
    }

    public void print() {
        System.out.println("=== ТАБЛИЦА РЕКОРДОВ ===");
        for (int i = 0; i < this.highScores.size(); i++) {
            System.out.print((i + 1) + ". ");
            this.highScores.get(i).print();
        }
    }

    public void inputAddScore(Scanner scanner) {
        HighScore score = new HighScore();
        score.inputHighScore(scanner);
        this.addScore(score);
    }

    public void addScore(HighScore score) {
        this.highScores.add(score);
        this.highScores.sort((a, b) -> Integer.compare(b.getScore(), a.getScore()));

        if (this.highScores.size() > 10) {
            this.highScores = this.highScores.subList(0, 10);
        }
    }

    public void clearScores() {
        this.highScores.clear();
    }
}