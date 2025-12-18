import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class AchievementSystem {
    private List<Achievement> achievements;
    
    public AchievementSystem() {
        this.achievements = new ArrayList<>();
        achievements.add(new Achievement("Новичок", "Сыграйте первую игру"));
        achievements.add(new Achievement("Сапер", "Выиграйте 10 игр"));
        achievements.add(new Achievement("Эксперт", "Выиграйте игру на сложном уровне"));
        achievements.add(new Achievement("Скоростник", "Победить менее чем за 60 секунд"));
        achievements.add(new Achievement("Аккуратный", "Победить без ошибок"));
    }
    
    public void print() {
        System.out.println("=== СИСТЕМА ДОСТИЖЕНИЙ ===");
        for (Achievement achievement : achievements) {
            achievement.print();
        }
    }
    
    public void checkAndUnlock(int gamesPlayed, int gamesWon, int bestTime, int difficulty) {
        for (Achievement achievement : achievements) {
            if (!achievement.isUnlocked()) {
                if (achievement.getKategoriyaSorevnovaniya().equals("Новичок") && gamesPlayed >= 1) {
                    achievement.zaregistrirovatPobedu();
                } else if (achievement.getKategoriyaSorevnovaniya().equals("Сапер") && gamesWon >= 10) {
                    achievement.zaregistrirovatPobedu();
                } else if (achievement.getKategoriyaSorevnovaniya().equals("Эксперт") && difficulty >= 2) {
                    achievement.zaregistrirovatPobedu();
                } else if (achievement.getKategoriyaSorevnovaniya().equals("Скоростник") && bestTime > 0 && bestTime <= 60) {
                    achievement.zaregistrirovatPobedu();
                }
            }
        }
    }
}
