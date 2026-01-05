import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

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
    
    public Difficulty() {
        this("Легко", 9, 9, 10);
    }

    public void print() {
        System.out.printf("Уровень сложности: %s (%dx%d, %d бомб)%n", level, width, height, bombs);
    }

    public void inputDifficulty(Scanner scanner) {
        System.out.println("Выберите сложность:");
        System.out.println("1. Легко (9x9, 10 бомб)");
        System.out.println("2. Средне (16x16, 40 бомб)");
        System.out.println("3. Сложно (30x16, 99 бомб)");
        System.out.println("4. Пользовательская");
        
        int choice = scanner.nextInt();

        switch (choice) {
            case 1: level = "Легко"; width = 9; height = 9; bombs = 10; break;
            case 2: level = "Средне"; width = 16; height = 16; bombs = 40; break;
            case 3: level = "Сложно"; width = 30; height = 16; bombs = 99; break;
            case 4:
                level = "Пользовательская";
                System.out.print("Введите ширину: ");
                width = scanner.nextInt();
                System.out.print("Введите высоту: ");
                height = scanner.nextInt();
                System.out.print("Введите количество бомб: ");
                bombs = scanner.nextInt();
                break;
            default:
                level = "Легко"; width = 9; height = 9; bombs = 10;
        }
    }

    public String getLevel() { return level; }
    public int getWidth() { return width; }
    public int getHeight() { return height; }
    public int getBombs() { return bombs; }
}