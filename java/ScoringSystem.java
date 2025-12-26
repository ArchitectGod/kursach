import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class ScoringSystem extends Schitatel {
    private int baseScore;
    private int timeBonus;
    private int mistakePenalty;
    
    public ScoringSystem() {
        super("Система очков", 0); 
        this.baseScore = 1000;
        this.timeBonus = 50;
        this.mistakePenalty = 100;
    }
    
    public void print() {
        System.out.printf("Система подсчета очков: %s%n", getTipSchetchika());
    }
    
    @Override
    public void sbrosit() {
        super.sbrosit();
        System.out.println("Система очков сброшена");
    }
    
    public int calculateScore(Player player, int gameTime) {
        int score = baseScore;
        score += (3600 - gameTime) / 60 * timeBonus;
        score -= player.getMistakes() * mistakePenalty;
        return Math.max(score, 0);
    }
}
