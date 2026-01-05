import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

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
        this("", 0, 0, "Легко");
    }

    public void print() {
        System.out.printf("%s - %d очков, время: %d сек, сложность: %s%n",
            playerName, score, time, difficulty);
    }

    public int getScore() { return score; }
    public String getName() { return playerName; }
    public int getTime() { return time; }
    public String getDifficulty() { return difficulty; }
}