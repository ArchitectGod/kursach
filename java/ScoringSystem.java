import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class ScoringSystem {
    private int baseScore;
    private int timeBonus;
    private int mistakePenalty;

    public ScoringSystem() {
        this.baseScore = 1000;
        this.timeBonus = 50;
        this.mistakePenalty = 100;
    }

    public int calculateScore(Player player, int gameTime) {
        int score = baseScore;
        score += (3600 - gameTime) / 60 * timeBonus;
        score -= player.getMistakes() * mistakePenalty;
        return Math.max(score, 0);
    }

    public int calculateWinScore(boolean won, int time, int mistakes) {
        if (!won) return 0;
        int score = baseScore + (1800 - time) / 30 * timeBonus - mistakes * mistakePenalty;
        return Math.max(score, 0);
    }
}
