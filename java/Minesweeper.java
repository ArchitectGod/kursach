import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// Демонстрационная функция
public class Minesweeper {
    public static void demonstrateGame() {
        System.out.println("=== ДЕМОНСТРАЦИЯ САПЕРА ===\n");

        // Создаем основные объекты
        Player player = new Player("Тестовый Игрок");
        Board board = new Board(8, 8, 10);
        Game game = new Game(board, player);

        // Демонстрация работы
        System.out.println("1. Начальное состояние:");
        game.print();
System.out.println("\n2. Делаем несколько ходов:");
        // Сначала расставляем бомбы безопасно
        board.placeBombs(0, 0);
        // Затем делаем ходы
        game.makeMove(0, 0, false);
        game.makeMove(1, 1, false);
        game.makeMove(2, 2, true);

        System.out.println("\n3. Состояние после ходов:");
        game.print();

        System.out.println("\n4. Демонстрация других систем:");
        Settings settings = new Settings();
        settings.print();

        MoveCounter counter = new MoveCounter();
        counter.addSafeMove();
        counter.addFlagMove();
        counter.addBombMove();
        counter.print();

        HelpSystem help = new HelpSystem();
        help.showTips();

        System.out.println("\n=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n");
    }

    // Главная функция
    public static void main(String[] args) {
        Locale.setDefault(Locale.forLanguageTag("ru-RU"));
        Random rand = new Random();

        System.out.println("=== САПЕР НА JAVA ===");
        System.out.println("35 классов, полная объектно-ориентированная реализация\n");

        demonstrateGame();

        // Простое меню для взаимодействия
        Scanner scanner = new Scanner(System.in);
        Menu menu = new Menu();
        menu.print();
        int choice = menu.getChoice(scanner);

        System.out.println("Выбран вариант: " + choice);
        
        switch (choice) {
            case 1: {
                Player player = new Player("Игрок");
                Board board = new Board(9, 9, 10);
                Game game = new Game(board, player);
                
                // Простая игровая сессия
                System.out.println("\n=== НАЧАЛО ИГРЫ ===");
                game.print();
                
                // Несколько демонстрационных ходов
                board.placeBombs(0, 0); // Сначала расставляем бомбы
                game.makeMove(0, 0, false);
                game.makeMove(1, 1, false);
                game.makeMove(2, 2, true);
                
                game.print();
                break;
            }
            case 2:
                System.out.println("Загрузка игры...");
                SaveManager saveManager = new SaveManager();
                saveManager.print();
                break;
            case 3: {
                Settings settings = new Settings();
                settings.inputSettings(scanner);
                settings.print();
                break;
            }
            case 4: {
                HighScoreManager hsManager = new HighScoreManager();
                hsManager.print();
                break;
            }
            case 5:
                System.out.println("Выход из игры.");
                break;
            default:
                System.out.println("Неверный выбор!");
        }

        scanner.close();
    }
}