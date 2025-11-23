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

//Класс таблицы игр
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

//Тема оформления
class Theme {
    private String name;
    private String cellClosed;
    private String cellOpen;
    private String bomb;

    public Theme(String themeName) {
        this.name = themeName;
        if (themeName.equals("classic")) {
            cellClosed = ".";
            cellOpen = " ";
            bomb = "*";
        } else if (themeName.equals("modern")) {
            cellClosed = "■";
            cellOpen = "□";
            bomb = "💣";
        } else if (themeName.equals("simple")) {
            cellClosed = "#";
            cellOpen = " ";
            bomb = "X";
        }
    }
   
    public Theme() {
        this("classic");
    }

    public void print() {
        System.out.printf("Тема: %s%n", name);
        System.out.printf("Закрытая клетка: %s, Открытая клетка: %s, Бомба: %s%n",
            cellClosed, cellOpen, bomb);
    }

    public void inputSelectTheme(Scanner scanner) {
        System.out.print("Выберите тему (1-classic, 2-modern, 3-simple): ");
        int choice = scanner.nextInt();
        switch (choice) {
            case 1: name = "classic"; cellClosed = "."; cellOpen = " "; bomb = "*"; break;
            case 2: name = "modern"; cellClosed = "■"; cellOpen = "□"; bomb = "💣"; break;
            case 3: name = "simple"; cellClosed = "#"; cellOpen = " "; bomb = "X"; break;
        }
    }

    public String getCellClosed() { return cellClosed; }
    public String getCellOpen() { return cellOpen; }
    public String getBomb() { return bomb; }
}

//Система помощи
class HelpSystem {
    public void print() {
        System.out.println("=== СИСТЕМА ПОМОЩИ ===");
        System.out.println("Цель игры: открыть все клетки без бомб");
        System.out.println("Управление:");
        System.out.println("- ЛКМ: открыть клетку");
        System.out.println("- ПКМ: поставить/убрать флаг");
        System.out.println("Цифры показывают количество бомб вокруг клетки");
    }

    public void showRules() {
        print();
    }

    public void showTips() {
        System.out.println("=== СОВЕТЫ ===");
        System.out.println("1. Начинайте с углов");
        System.out.println("2. Используйте флаги для отметки бомб");
        System.out.println("3. Анализируйте цифры для определения безопасных клеток");
        System.out.println("4. Если вокруг клетки 0 бомб, она откроет область автоматически");
    }

    public void showControls() {
        System.out.println("=== УПРАВЛЕНИЕ ===");
        System.out.println("WASD/Стрелки - перемещение");
        System.out.println("Пробел - открыть клетку");
        System.out.println("F - поставить/убрать флаг");
        System.out.println("P - пауза");
        System.out.println("H - помощь");
    }
}

//Анализатор игры
class GameAnalyzer {
    public void print() {
        System.out.println("Анализатор игрового процесса");
    }

    public void analyzeBoard(Board board) {
        int flaggedBombs = 0;
        int totalBombs = board.getTotalBombs();

        System.out.printf("Анализ поля: бомб %d, безопасных клеток осталось: %d%n",
            totalBombs, board.getSafeCellsLeft());
    }

public void analyzePlayer(Player player) {
        System.out.printf("Анализ игрока: %s%n", player.getName());
        System.out.printf("Эффективность: %.1f%%%n",
            player.getOpenedCells() > 0 ?
            (float)(player.getOpenedCells() - player.getMistakes()) / player.getOpenedCells() * 100 : 0);
    }

    public void analyzeGame(Game game) {
        System.out.println("Анализ игры:");
        System.out.println("Статус: " + (game.isGameRunning() ? "в процессе" : (game.getState() == 1 ? "победа" : "поражение")));
        System.out.println("Время: " + game.getGameTime() + " сек");
    }
}

//Рекорд
class HighScore {
    private String playerName;
    private int score;
    private int time;
    private String difficulty;

    public HighScore(String name, int s, int t, String diff) {
        this.playerName = name;
        this.score = s;
        this.time = t;
        this.difficulty = diff;
    }
   
    public HighScore() {
        this("", 0, 0, "");
    }

    public void print() {
        System.out.printf("Рекорд: %s - %d очков, время: %d сек, сложность: %s%n",
            playerName, score, time, difficulty);
    }

    public void inputHighScore(Scanner scanner) {
        System.out.println("Введите данные рекорда:");
        System.out.print("Имя: ");
        this.playerName = scanner.next();
        System.out.print("Очки: ");
        this.score = scanner.nextInt();
        System.out.print("Время (сек): ");
        this.time = scanner.nextInt();
        System.out.print("Сложность: ");
        this.difficulty = scanner.next();
    }

    public int getScore() { return score; }
}

//Менеджер рекордов
class HighScoreManager {
    private List<HighScore> highScores;

    public HighScoreManager() {
        this.highScores = new ArrayList<>();
    }

    public void print() {
        System.out.println("=== ТАБЛИЦА РЕКОРДОВ ===");
        for (int i = 0; i < highScores.size(); i++) {
            System.out.print((i + 1) + ". ");
            highScores.get(i).print();
        }
    }

    public void inputAddScore(Scanner scanner) {
        HighScore score = new HighScore();
        score.inputHighScore(scanner);
        addScore(score);
    }

    public void addScore(HighScore score) {
        highScores.add(score);
        highScores.sort((a, b) -> Integer.compare(b.getScore(), a.getScore()));

        if (highScores.size() > 10) {
            highScores = highScores.subList(0, 10);
        }
    }

    public void clearScores() {
        highScores.clear();
    }
}

//Система подсказок
class HintSystem {
    private int hintsAvailable;

    public HintSystem() {
        this.hintsAvailable = 3;
    }

    public void print() {
        System.out.printf("Система подсказок, доступно подсказок: %d%n", hintsAvailable);
    }

    public void inputUseHint(Scanner scanner) {
        System.out.print("Использовать подсказку? (1-да, 0-нет): ");
        int choice = scanner.nextInt();
        if (choice == 1 && hintsAvailable > 0) {
            hintsAvailable--;
            System.out.printf("Подсказка использована! Осталось: %d%n", hintsAvailable);
        }
    }

    public Coordinate getHint(Board board) {
        if (hintsAvailable > 0) {
            hintsAvailable--;

            for (int y = 0; y < board.getHeight(); y++) {
                for (int x = 0; x < board.getWidth(); x++) {
                    Cell cell = board.getCell(x, y);
                    if (cell != null && !cell.getIsOpen() && !cell.getIsBomb()) {
                        System.out.printf("Подсказка: безопасная клетка [%d,%d]%n", x, y);
                        return new Coordinate(x, y);
                    }
                }
            }
        } else {
            System.out.println("Подсказки закончились!");
        }
        return new Coordinate(-1, -1);
    }

    public void addHints(int count) {
        hintsAvailable += count;
        System.out.printf("Добавлено %d подсказок. Всего: %d%n", count, hintsAvailable);
    }
}