import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// Класс координат
class Coordinate {
    private int x;
    private int y;

    public Coordinate(int xCoord, int yCoord) {
        this.x = xCoord;
        this.y = yCoord;
    }
   
    public Coordinate() {
        this(0, 0);
    }

    public void print() {
        System.out.printf("Координаты: (%d, %d)%n", x, y);
    }

    public void input(Scanner scanner) {
        System.out.print("Введите координаты X Y: ");
        this.x = scanner.nextInt();
        this.y = scanner.nextInt();
    }

    public int getX() { return x; }
    public int getY() { return y; }
    public void setX(int newX) { x = newX; }
    public void setY(int newY) { y = newY; }

    public boolean isValid(int maxX, int maxY) {
        return x >= 0 && x < maxX && y >= 0 && y < maxY;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Coordinate that = (Coordinate) obj;
        return x == that.x && y == that.y;
    }
}

// Класс клетки
class Cell {
    private boolean isBomb;
    private boolean isOpen;
    private boolean isFlag;
    private int countBomb;
    private int coordinateX;
    private int coordinateY;

    public Cell(int x, int y) {
        this.coordinateX = x;
        this.coordinateY = y;
        this.isBomb = false;
        this.isOpen = false;
        this.isFlag = false;
        this.countBomb = 0;
    }
   
    public Cell() {
        this(0, 0);
    }

    public void print() {
        System.out.printf("Клетка [%d,%d]: ", coordinateX, coordinateY);
        if (isOpen) {
            if (isBomb) {
                System.out.print("Бомба");
            } else {
                System.out.printf("Бомб вокруг: %d", countBomb);
            }
        } else if (isFlag) {
            System.out.print("Флаг");
        } else {
            System.out.print("Закрыта");
        }
        System.out.println();
    }

    public void inputFromUser(Scanner scanner) {
        System.out.printf("Введите состояние клетки [%d,%d] (0-закрыта, 1-открыта, 2-флаг): ", coordinateX, coordinateY);
        int state = scanner.nextInt();
        if (state == 1) {
            open();
        } else if (state == 2) {
            toggleFlag();
        }
    }

    public void open() {
        isOpen = true;
        isFlag = false;
    }

    public void toggleFlag() {
        if (!isOpen) {
            isFlag = !isFlag;
        }
    }

    public void setBomb() {
        isBomb = true;
    }

    public void setCountBomb(int count) {
        countBomb = count;
    }

    public boolean getIsBomb() { return isBomb; }
    public boolean getIsOpen() { return isOpen; }
    public boolean getIsFlag() { return isFlag; }
    public int getCountBomb() { return countBomb; }
    public int getX() { return coordinateX; }
    public int getY() { return coordinateY; }
}

// Класс таймера
class Timer {
    private long startTime;
    private long pausedTime;
    private boolean isRunning;

    public Timer() {
        this.startTime = 0;
        this.pausedTime = 0;
        this.isRunning = false;
    }

    public void print() {
        System.out.printf("Таймер: %d секунд, статус: %s%n", getElapsedTime(), isRunning ? "работает" : "на паузе");
    }

    public void inputStart(Scanner scanner) {
        System.out.print("Запустить таймер? (1-да, 0-нет): ");
        int choice = scanner.nextInt();
        if (choice == 1) {
            start();
        }
    }

    public void start() {
        startTime = System.currentTimeMillis() / 1000;
        isRunning = true;
    }

    public void pause() {
        if (isRunning) {
            pausedTime = System.currentTimeMillis() / 1000;
            isRunning = false;
        }
    }

    public void resume() {
        if (!isRunning) {
            startTime += (System.currentTimeMillis() / 1000 - pausedTime);
            isRunning = true;
        }
    }

    public int getElapsedTime() {
        if (isRunning) {
            return (int)(System.currentTimeMillis() / 1000 - startTime);
        }
        return (int)(pausedTime - startTime);
    }

    public void reset() {
        startTime = 0;
        pausedTime = 0;
        isRunning = false;
    }
}


// Класс настроек
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

// Класс Меню
class Menu {
    public void print() {
        System.out.println("=== ГЛАВНОЕ МЕНЮ ===");
        System.out.println("1. Новая игра");
        System.out.println("2. Загрузить игру");
        System.out.println("3. Настройки");
        System.out.println("4. Таблица лидеров");
        System.out.println("5. Выход");
    }

    public int getChoice(Scanner scanner) {
        System.out.print("Выберите вариант: ");
        return scanner.nextInt();
    }
}

// Рандомайзер
class RandomGenerator {
    private Random random;

    public RandomGenerator() {
        this.random = new Random();
    }

    public RandomGenerator(int seed) {
        this.random = new Random(seed);
    }

    public void print() {
        System.out.println("Генератор случайных чисел");
    }

    public void inputSeed(Scanner scanner) {
        System.out.print("Введите seed для генератора: ");
        int seed = scanner.nextInt();
        this.random = new Random(seed);
    }

    public int getRandom(int min, int max) {
        return min + random.nextInt(max - min + 1);
    }

    public Coordinate getRandomCoordinate(int maxX, int maxY) {
        return new Coordinate(getRandom(0, maxX - 1), getRandom(0, maxY - 1));
    }
}

// Сложность
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