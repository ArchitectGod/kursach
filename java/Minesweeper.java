import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// Главный класс
public class Minesweeper {
    
public static void demonstrateExceptionHandling(Scanner scanner) {
    System.out.println("\n=== ДЕМОНСТРАЦИЯ ОБРАБОТКИ ИСКЛЮЧЕНИЙ ===");
    
    
	try {
		GameFactory factory = GameFactory.getInstance();
		Game game = factory.createCustomGame("", 0, 0, 0);
	} catch (IllegalArgumentException e) {
		System.out.println("Перехвачено исключение: " + e.getMessage());
	}
	
	try {
		int[] array = new int[5];
		System.out.println(array[10]);
	} catch (ArrayIndexOutOfBoundsException e) {
		System.out.println("Ошибка индекса массива: " + e.getMessage());
	} catch (Exception e) {
		System.out.println("Общая ошибка: " + e.getMessage());
	}
	
	try {
		System.out.print("Введите число: ");
		int number = scanner.nextInt();
		System.out.println("Вы ввели: " + number);
		scanner.nextLine(); // Очистка буфера
	} catch (InputMismatchException e) {
		System.out.println("Ошибка: введено не число!");
		scanner.nextLine(); // Очистка некорректного ввода
	}
	
	try {
		System.out.print("Введите текст: ");
		String text = scanner.nextLine();
		System.out.println("Вы ввели: " + text);
	} catch (Exception e) {
		System.out.println("Ошибка: " + e.getMessage());
	}
 
    
    System.out.println("=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n");
}
    
    public static void demonstrateStaticFeatures() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ СТАТИЧЕСКИХ ФИЧ ===");
        
        System.out.println("Создано досок до создания: " + Board.getBoardsCreated());
        
        Board board1 = new Board(5, 5, 5);
        Board board2 = new Board(6, 6, 6);
        
        System.out.println("Создано досок после создания двух: " + Board.getBoardsCreated());
        
        GameFactory factory1 = GameFactory.getInstance();
        GameFactory factory2 = GameFactory.getInstance();
        
        System.out.println("Фабрики одинаковы: " + (factory1 == factory2));
        
        System.out.println("=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n");
    }

    public static void demonstrateGame() {
        System.out.println("=== ДЕМОНСТРАЦИЯ САПЕРА ===\n");

        Player player = new Player("Тестовый Игрок");
        Board board = new Board(8, 8, 10);
        Game game = new Game(board, player);

        System.out.println("1. Начальное состояние:");
        game.print();

        System.out.println("\n2. Делаем несколько ходов:");
        board.placeBombs(0, 0);
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

    public static void main(String[] args) {
        try {
            Locale.setDefault(Locale.forLanguageTag("ru-RU"));
        } catch (Exception e) {
            System.out.println("Ошибка установки локали: " + e.getMessage());
        }

        System.out.println("=== САПЕР НА JAVA ===");
        System.out.println("35 классов, полная объектно-ориентированная реализация\n");
		
		Scanner scanner = new Scanner(System.in);
		
        demonstrateStaticFeatures();
        demonstrateExceptionHandling(scanner);
        demonstrateGame();

        
        Menu menu = new Menu();
        
        try {
            menu.print();
            int choice = menu.getChoice(scanner);

            System.out.println("Выбран вариант: " + choice);
            
            switch (choice) {
                case 1: {
                    try {
                        GameFactory factory = GameFactory.getInstance();
                        Player player = new Player("Игрок");
                        Board board = new Board(9, 9, 10);
                        Game game = new Game(board, player);
                        
                        System.out.println("\n=== НАЧАЛО ИГРЫ ===");
                        game.print();
                        
                        board.placeBombs(0, 0);
                        game.makeMove(0, 0, false);
                        game.makeMove(1, 1, false);
                        game.makeMove(2, 2, true);
                        
                        game.print();
                    } catch (Exception e) {
                        System.out.println("Ошибка создания игры: " + e.getMessage());
                    }
                    break;
                }
                case 2:
                    System.out.println("Загрузка игры...");
                    try {
                        SaveManager saveManager = new SaveManager();
                        saveManager.print();
                    } catch (Exception e) {
                        System.out.println("Ошибка загрузки: " + e.getMessage());
                    }
                    break;
                case 3: {
                    try {
                        Settings settings = new Settings();
                        settings.inputSettings(scanner);
                        settings.print();
                    } catch (Exception e) {
                        System.out.println("Ошибка в настройках: " + e.getMessage());
                    }
                    break;
                }
                case 4: {
                    try {
                        HighScoreManager hsManager = new HighScoreManager();
                        hsManager.print();
                    } catch (Exception e) {
                        System.out.println("Ошибка загрузки рекордов: " + e.getMessage());
                    }
                    break;
                }
                case 5:
                    System.out.println("Выход из игры.");
                    break;
                default:
                    System.out.println("Неверный выбор!");
            }
        } catch (Exception e) {
            System.out.println("Критическая ошибка: " + e.getMessage());
            e.printStackTrace();
        } finally {
            if (scanner != null) {
                scanner.close();
                System.out.println("Ресурсы освобождены");
            }
        }
     }
}