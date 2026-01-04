import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class AchievementSystem {
    private List<Achievement> achievements;

    public AchievementSystem() {
        this.achievements = new ArrayList<>();
		achievements.add(new Achievement("Новичок", "Сыграйте первую игру"));
        achievements.add(new Achievement("Сапер", "Выиграйте 10 игр"));
        achievements.add(new Achievement("Эксперт", "Выиграйте игру на сложном уровне"));
        achievements.add(new Achievement("Скоростник", "Выиграйте игру менее чем за 60 секунд"));
        achievements.add(new Achievement("Безошибочный", "Выиграйте игру без ошибок"));
    }

    public void print() {
        System.out.println("=== СИСТЕМА ДОСТИЖЕНИЙ ===");
        for (int i = 0; i < achievements.size(); i++) {
            System.out.print((i + 1) + ". ");
            achievements.get(i).print();
        }
    }

    public void checkAchievements(Player player, int gameTime, boolean won, int difficulty) {
        if (!won) return;

        if (gameTime < 60) {
            achievements.get(3).unlock();
        }

        if (player.getMistakes() == 0) {
            achievements.get(4).unlock();
        }

        if (difficulty == 2) {
            achievements.get(2).unlock();
        }
    }

    public int getUnlockedCount() {
        int count = 0;
        for (Achievement achievement : achievements) {
            if (achievement.isUnlocked()) count++;
        }
        return count;
    }
}