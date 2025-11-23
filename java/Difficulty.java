import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 21. Сложность
class Difficulty {
    private String level;
    private int width;
    private int height;
    private int bombs;

    public Difficulty(String lvl, int w, int h, int b) {
        this.level = lvl;
        this.width = w;
        this.height = h;
        this.bombs = b;
    }

    public void print() {
        System.out.printf("Уровень сложности: %s (%dx%d, %d бомб)%n", level, width, height, bombs);
    }

    public void inputDifficulty(Scanner scanner) {
        System.out.print("Выберите сложность (0-Легко, 1-Средне, 2-Сложно, 3-Пользовательская): ");
        int choice = scanner.nextInt();

        switch (choice) {
            case 0: level = "Легко"; width = 9; height = 9; bombs = 10; break;
            case 1: level = "Средне"; width = 16; height = 16; bombs = 40; break;
            case 2: level = "Сложно"; width = 30; height = 16; bombs = 99; break;
            case 3:
                level = "Пользовательская";
                System.out.print("Введите ширину, высоту и количество бомб: ");
                width = scanner.nextInt();
                height = scanner.nextInt();
                bombs = scanner.nextInt();
                break;
        }
    }

    public String getLevel() { return level; }
    public int getWidth() { return width; }
    public int getHeight() { return height; }
    public int getBombs() { return bombs; }
}
