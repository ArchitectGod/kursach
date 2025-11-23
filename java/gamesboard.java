import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 9. Класс таблицы игр
class gamesboard {
    private String name;
    private int time;
    private int height;
    private int width;
    private int bombs;
    private int day;
    private int month;
    private int age;
    private boolean win;

    public gamesboard(String playerName, int t, int w, int h, int b, boolean victory) {
        this.name = playerName;
        this.time = t;
        this.width = w;
        this.height = h;
        this.bombs = b;
        this.win = victory;

        LocalDateTime now = LocalDateTime.now();
        this.day = now.getDayOfMonth();
        this.month = now.getMonthValue();
        this.age = now.getYear();
    }

    public void print() {
        System.out.printf("%s: %d сек, %dx%d, %s%n", name, time, width, height,
                win ? "ПОБЕДА" : "ПРОИГРЫШ");
    }

    public void inputData(Scanner scanner) {
        System.out.println("Введите данные для таблицы игр:");
        System.out.print("Имя: ");
        this.name = scanner.next();
        System.out.print("Время (сек): ");
        this.time = scanner.nextInt();
        System.out.print("Размеры поля (ширина высота): ");
        this.width = scanner.nextInt();
        this.height = scanner.nextInt();
        System.out.print("Количество бомб: ");
        this.bombs = scanner.nextInt();
        System.out.print("Результат (1-победа, 0-поражение): ");
        this.win = scanner.nextInt() == 1;
    }
public void saveToFile(String filename) {
        try (PrintWriter file = new PrintWriter(new FileWriter(filename, true))) {
            file.printf("%s,%d,%d,%d,%d,%d,%d,%d,%d%n",
                    name, time, height, width, bombs,
                    day, month, age, win ? 1 : 0);
        } catch (IOException e) {
            System.out.println("Ошибка сохранения: " + e.getMessage());
        }
    }

    public String getName() { return name; }
    public int getTime() { return time; }
    public boolean isWin() { return win; }
}
