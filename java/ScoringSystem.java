import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 18. Система очков
class ScoringSystem {
    private int baseScore;
    private int timeBonus;
    private int mistakePenalty;

    public ScoringSystem() {
        this.baseScore = 1000;
        this.timeBonus = 50;
        this.mistakePenalty = 100;
    }

    public void print() {
        System.out.println("Система подсчета очков");
        System.out.printf("Базовые очки: %d, Бонус за время: %d, Штраф за ошибку: %d%n",
            this.baseScore, this.timeBonus, this.mistakePenalty);
    }

    public void inputScoringParams(Scanner scanner) {
        System.out.println("Введите параметры подсчета очков:");
        System.out.print("Базовые очки: ");
        this.baseScore = scanner.nextInt();
        System.out.print("Бонус за время: ");
        this.timeBonus = scanner.nextInt();
        System.out.print("Штраф за ошибку: ");
        this.mistakePenalty = scanner.nextInt();
    }

    public int calculateScore(Player player, int gameTime) {
        int score = this.baseScore;
        score += (3600 - gameTime) / 60 * this.timeBonus;
        score -= player.getMistakes() * this.mistakePenalty;
        return Math.max(score, 0);
    }

    public int calculateWinScore(boolean won, int time, int mistakes) {
        if (!won) return 0;
        int score = this.baseScore + (1800 - time) / 30 * this.timeBonus - mistakes * this.mistakePenalty;
        return Math.max(score, 0);
    }
}