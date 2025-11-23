import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 7. Класс настроек
class Settings {
    private boolean autoBombs;
    private boolean sounds;
    private int difficulty;

    public Settings() {
        this.autoBombs = true;
        this.sounds = true;
        this.difficulty = 0;
    }

    public void print() {
        System.out.println("=== НАСТРОЙКИ ===");
        System.out.println("Авторасстановка бомб: " + (autoBombs ? "Вкл" : "Выкл"));
        System.out.println("Звуки: " + (sounds ? "Вкл" : "Выкл"));
        System.out.print("Сложность: ");
        switch (difficulty) {
            case 0: System.out.println("Легко"); break;
            case 1: System.out.println("Средне"); break;
            case 2: System.out.println("Сложно"); break;
        }
    }

    public void inputSettings(Scanner scanner) {
        System.out.println("=== ВВОД НАСТРОЕК ===");
        System.out.print("Авторасстановка бомб (0-Выкл, 1-Вкл): ");
        this.autoBombs = scanner.nextInt() == 1;
        System.out.print("Звуки (0-Выкл, 1-Вкл): ");
        this.sounds = scanner.nextInt() == 1;
        System.out.print("Сложность (0-Легко, 1-Средне, 2-Сложно): ");
        this.difficulty = scanner.nextInt();
    }
public void toggleAutoBombs() {
        autoBombs = !autoBombs;
        System.out.println("Авторасстановка бомб: " + (autoBombs ? "ВКЛ" : "ВЫКЛ"));
    }

    public void toggleSounds() {
        sounds = !sounds;
        System.out.println("Звуки: " + (sounds ? "ВКЛ" : "ВЫКЛ"));
    }

    public void setDifficulty(int level) {
        if (level >= 0 && level <= 2) {
            difficulty = level;
            String[] levels = { "Легко", "Средне", "Сложно" };
            System.out.printf("Сложность установлена: %s%n", levels[level]);
        }
    }

    public Board createBoardByDifficulty() {
        switch (difficulty) {
            case 0: return new Board(9, 9, 10);
            case 1: return new Board(16, 16, 40);
            case 2: return new Board(30, 16, 99);
            default: return new Board(9, 9, 10);
        }
    }

    public boolean getAutoBombs() { return autoBombs; }
    public boolean getSounds() { return sounds; }
    public int getDifficulty() { return difficulty; }
}
