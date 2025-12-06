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
        System.out.printf("Уровень сложности: %s (%dx%d, %d бомб)%n", this.level, this.width, this.height, this.bombs);
    }

    public void inputDifficulty(Scanner scanner) {
        System.out.print("Выберите сложность (0-Легко, 1-Средне, 2-Сложно, 3-Пользовательская): ");
        int choice = scanner.nextInt();

        switch (choice) {
            case 0: this.level = "Легко"; this.width = 9; this.height = 9; this.bombs = 10; break;
            case 1: this.level = "Средне"; this.width = 16; this.height = 16; this.bombs = 40; break;
            case 2: this.level = "Сложно"; this.width = 30; this.height = 16; this.bombs = 99; break;
            case 3:
                this.level = "Пользовательская";
                System.out.print("Введите ширину, высоту и количество бомб: ");
                this.width = scanner.nextInt();
                this.height = scanner.nextInt();
                this.bombs = scanner.nextInt();
                break;
        }
    }

    public String getLevel() { return this.level; }
    public int getWidth() { return this.width; }
    public int getHeight() { return this.height; }
    public int getBombs() { return this.bombs; }
}
