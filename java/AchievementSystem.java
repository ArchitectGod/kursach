import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 24. Система достижений
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

    public void inputUnlockAchievement(Scanner scanner) {
        System.out.printf("Выберите достижение для разблокировки (1-%d): ", achievements.size());
        int choice = scanner.nextInt();
        if (choice >= 1 && choice <= achievements.size()) {
            achievements.get(choice - 1).inputUnlock(scanner);
        }
    }

    public void checkAchievements(PlayerSession session) {
        // Логика проверки достижений
    }

    public int getUnlockedCount() {
        int count = 0;
        for (Achievement achievement : achievements) {
            if (achievement.isUnlocked()) count++;
        }
        return count;
    }
}