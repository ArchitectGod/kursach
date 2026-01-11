import java.util.*;

class AchievementSystem {
    private List<Achievement> achievements;
    int counter;

    public AchievementSystem() {
        counter = 0;
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
        achievements.get(0).unlock();
        if (!won) return;

        if (counter + 1 == 10){
            achievements.get(1).unlock();
            counter += 1;
        }
        else{
            counter += 1;
        }
        if (difficulty == 2) {
            achievements.get(2).unlock();
        }
        if (gameTime < 60) {
            achievements.get(3).unlock();
        }
        if (player.getMistakes() == 0) {
            achievements.get(4).unlock();
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