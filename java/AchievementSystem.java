import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 24. Система достижений
class AchievementSystem {
    private List<Achievement> achievements;

    public AchievementSystem() {
        this.achievements = new ArrayList<>();
        this.achievements.add(new Achievement("Новичок", "Сыграйте первую игру"));
        this.achievements.add(new Achievement("Сапер", "Выиграйте 10 игр"));
        this.achievements.add(new Achievement("Эксперт", "Выиграйте игру на сложном уровне"));
        this.achievements.add(new Achievement("Скоростник", "Выиграйте игру менее чем за 60 секунд"));
        this.achievements.add(new Achievement("Безошибочный", "Выиграйте игру без ошибок"));
    }

    public void print() {
        System.out.println("=== СИСТЕМА ДОСТИЖЕНИЙ ===");
        for (int i = 0; i < this.achievements.size(); i++) {
            System.out.print((i + 1) + ". ");
            this.achievements.get(i).print();
        }
    }

    public void inputUnlockAchievement(Scanner scanner) {
        System.out.printf("Выберите достижение для разблокировки (1-%d): ", this.achievements.size());
        int choice = scanner.nextInt();
        if (choice >= 1 && choice <= this.achievements.size()) {
            this.achievements.get(choice - 1).inputUnlock(scanner);
        }
    }

    public void checkAchievements(PlayerSession session) {
        // Логика проверки достижений
    }

    public int getUnlockedCount() {
        int count = 0;
        for (Achievement achievement : this.achievements) {
            if (achievement.isUnlocked()) count++;
        }
        return count;
    }
}
