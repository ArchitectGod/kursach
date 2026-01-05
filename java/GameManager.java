import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class GameManager {
    private Game currentGame;
    private Settings settings;
    private Logger logger;
    private HighScoreManager scoreManager;
    private AchievementSystem achievementSystem;
    private SoundSystem soundSystem;
    private HintSystem hintSystem;
    private GameHistory gameHistory;
    private MoveCounter moveCounter;
    private GameStats gameStats;
    private Renderer renderer;
    private InputHandler inputHandler;
    private Validator validator;
    private Notifier notifier;
    private HelpSystem helpSystem;

    private boolean gameRunning;
    private int currentDifficulty;

    public GameManager() {
        settings = new Settings();
        logger = new Logger();
		scoreManager = new HighScoreManager();
        achievementSystem = new AchievementSystem();
        soundSystem = new SoundSystem();
        hintSystem = new HintSystem();
        gameHistory = new GameHistory();
        moveCounter = new MoveCounter();
        gameStats = new GameStats();
        renderer = new Renderer();
        inputHandler = new InputHandler();
        validator = new Validator();
        notifier = new Notifier();
        helpSystem = new HelpSystem();
        
        gameRunning = false;
        currentDifficulty = 0;
    }

    public void run(Scanner scanner) {
        Random rand = new Random();
        showMainMenu(scanner);
    }

    private void showMainMenu(Scanner scanner) {
        while (true) {
            clearScreen();
            System.out.println("=== САПЕР ===");
            System.out.println("1. Новая игра");
            System.out.println("2. Настройки");
            System.out.println("3. Таблица рекордов");
            System.out.println("4. Достижения");
            System.out.println("5. Статистика");
            System.out.println("6. Помощь");
            System.out.println("7. Выход");
            
            int choice = InputUtils.safeInputInt(scanner, "Выберите: ");

            switch (choice) {
                case 1: startNewGame(scanner); break;
                case 2: showSettings(scanner); break;
                case 3: showHighScores(); break;
                case 4: showAchievements(); break;
                case 5: showStatistics(); break;
                case 6: showHelp(); break;
                case 7: exitGame(); return;
                default: System.out.println("Неверный выбор!"); pause(scanner);
            }
        }
    }

    private void startNewGame(Scanner scanner) {
        clearScreen();
        System.out.println("=== НОВАЯ ИГРА ===");

        Difficulty difficulty = new Difficulty();
        difficulty.inputDifficulty(scanner);
        currentDifficulty = getDifficultyLevel(difficulty.getLevel());

        String playerName;
        do {
            playerName = inputHandler.getPlayerName(scanner);
        } while (!validator.isValidName(playerName));

        Player player = new Player(playerName);
        Board board = new Board(difficulty.getWidth(), difficulty.getHeight(), difficulty.getBombs());
        currentGame = new Game(board, player);

        logger.logGameStart(playerName);
        gameRunning = true;
        gameHistory.clear();
        moveCounter.reset();
        hintSystem = new HintSystem();

        playGame(scanner);
    }

    private void playGame(Scanner scanner) {
        while (gameRunning && currentGame.isGameRunning()) {
            clearScreen();
            renderer.renderGameState(currentGame);
            System.out.println("Подсказок: " + hintSystem.getHintsAvailable());
            System.out.println("\nКоманды: (o)открыть, (f)флаг, (h)подсказка, (p)пауза, (q)выйти");
            System.out.print("Выберите действие: ");

            char action = scanner.next().charAt(0);
            InputUtils.clearInputBuffer(scanner);

            processAction(action, scanner);
        }

        if (currentGame != null && !currentGame.isGameRunning()) {
            showGameResult(scanner);
        }
    }

    private void processAction(char action, Scanner scanner) {
        hintSystem.resetHintUsed();
        
        switch (Character.toLowerCase(action)) {
            case 'o': {
                int[] coords = new int[2];
                InputUtils.safeInputTwoInts(scanner, coords, "Введите координаты для открытия (X Y): ");
                handleOpenCell(coords[0], coords[1], scanner);
                break;
            }
            case 'f': {
                int[] coords = new int[2];
                InputUtils.safeInputTwoInts(scanner, coords, "Введите координаты для флага (X Y): ");
				handleFlagCell(coords[0], coords[1], scanner);
                break;
            }
            case 'h': {
                handleHint();
                pause(scanner);
                break;
            }
            case 'p': {
                handlePause(scanner);
                break;
            }
            case 'q': {
                gameRunning = false;
                System.out.println("Выход в меню...");
                pause(scanner);
                break;
            }
            default:
                System.out.println("Неверная команда!");
                pause(scanner);
        }
    }

    private void handleOpenCell(int x, int y, Scanner scanner) {
        if (!validator.isValidCoordinate(new Coordinate(x, y),
            currentGame.getBoard().getWidth(),
            currentGame.getBoard().getHeight())) {
            pause(scanner);
            return;
        }

        Cell cell = currentGame.getBoard().getCell(x, y);
        if (cell == null) return;

        if (cell.getIsOpen()) {
            notifier.showInfoMessage("Клетка уже открыта!");
            pause(scanner);
            return;
        }

        if (cell.getIsFlag()) {
            notifier.showInfoMessage("Сначала уберите флаг!");
            pause(scanner);
            return;
        }

        soundSystem.playClickSound();
        currentGame.makeMove(x, y, true);
        gameHistory.addMove("Открытие", new Coordinate(x, y));
        logger.logMove(currentGame.getPlayer().getName(), x, y, "Открытие");

        if (cell.getIsBomb()) {
            moveCounter.addBombMove();
            soundSystem.playExplosionSound();
        } else {
            moveCounter.addSafeMove();
            if (cell.getCountBomb() == 0) {
                openAdjacentCells(x, y);
            }
        }

        checkGameEnd();
    }

    private void handleFlagCell(int x, int y, Scanner scanner) {
        if (!validator.isValidCoordinate(new Coordinate(x, y),
            currentGame.getBoard().getWidth(),
            currentGame.getBoard().getHeight())) {
            pause(scanner);
            return;
        }

        Cell cell = currentGame.getBoard().getCell(x, y);
        if (cell == null || cell.getIsOpen()) return;

        int flags = currentGame.getBoard().countFlags();
        if (!cell.getIsFlag() && flags >= currentGame.getBoard().getTotalBombs()) {
            notifier.showInfoMessage("Нельзя поставить больше флагов чем бомб!");
            pause(scanner);
            return;
        }

        cell.toggleFlag();
        soundSystem.playClickSound();
        moveCounter.addFlagMove();
        String action = cell.getIsFlag() ? "Поставлен флаг" : "Убран флаг";
        gameHistory.addMove(action, new Coordinate(x, y));
        logger.logMove(currentGame.getPlayer().getName(), x, y, action);
    }

    private void handleHint() {
        Coordinate hint = hintSystem.getHint(currentGame.getBoard());
        if (hint.getX() != -1) {
            notifier.showInfoMessage("Подсказка: безопасная клетка [" +
                hint.getX() + "," + hint.getY() + "]");
        }
    }

    private void handlePause(Scanner scanner) {
        currentGame.pauseGame();
        System.out.println("\nИгра на паузе. Нажмите Enter для продолжения...");
        scanner.nextLine();
        currentGame.resumeGame();
    }

    private void openAdjacentCells(int x, int y) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;

                int newX = x + dx;
                int newY = y + dy;

                if (newX >= 0 && newX < currentGame.getBoard().getWidth() &&
                    newY >= 0 && newY < currentGame.getBoard().getHeight()) {

                    Cell cell = currentGame.getBoard().getCell(newX, newY);
					if (cell != null && !cell.getIsOpen() && !cell.getIsFlag() && !cell.getIsBomb()) {
                        currentGame.makeMove(newX, newY, true);
                        gameHistory.addMove("Автооткрытие", new Coordinate(newX, newY));
                        moveCounter.addSafeMove();

                        if (cell.getCountBomb() == 0) {
                            openAdjacentCells(newX, newY);
                        }
                    }
                }
            }
        }
    }

    private void checkGameEnd() {
        if (!currentGame.isGameRunning()) {
            if (currentGame.getState() == 1) {
                soundSystem.playWinSound();
                handleWin();
            } else if (currentGame.getState() == 2) {
                handleLoss();
            }
        }
    }

    private void handleWin() {
        Player player = currentGame.getPlayer();
        int gameTime = currentGame.getGameTime();

        gameStats.addGame(true, gameTime);
        gameStats.saveToFile("statistics.txt");

        achievementSystem.checkAchievements(player, gameTime, true, currentDifficulty);

        ScoringSystem scoring = new ScoringSystem();
        int score = scoring.calculateScore(player, gameTime);
        scoreManager.addScore(player.getName(), score, gameTime,
            getDifficultyString(currentDifficulty));

        notifier.showWinMessage();
        logger.logGameEnd(player.getName(), true);
    }

    private void handleLoss() {
        Player player = currentGame.getPlayer();
        notifier.showLoseMessage();
        logger.logGameEnd(player.getName(), false);
        gameStats.addGame(false, currentGame.getGameTime());
    }

    private void showGameResult(Scanner scanner) {
        clearScreen();
        System.out.println("=== ИГРА ОКОНЧЕНА ===");
        System.out.println("Результат: " + (currentGame.getState() == 1 ? "ПОБЕДА!" : "ПОРАЖЕНИЕ"));
        System.out.println("Время: " + currentGame.getGameTime() + " сек");
        
        if (currentGame.getPlayer() != null) {
            System.out.println("Игрок: " + currentGame.getPlayer().getName());
            System.out.println("Ошибок: " + currentGame.getPlayer().getMistakes());
        }

        System.out.println();
        moveCounter.print();
        System.out.println();
        gameHistory.print();

        System.out.println("\nНажмите Enter для продолжения...");
        scanner.nextLine();
        gameRunning = false;
    }

    private void showSettings(Scanner scanner) {
        clearScreen();
        settings.inputSettings(scanner);
        soundSystem.setEnabled(settings.getSounds());
        pause(scanner);
    }

    private void showHighScores() {
        clearScreen();
        scoreManager.print();
        pause(new Scanner(System.in));
    }

    private void showAchievements() {
        clearScreen();
        achievementSystem.print();
        System.out.printf("\nРазблокировано: %d/%d достижений%n",
            achievementSystem.getUnlockedCount(), 5);
        pause(new Scanner(System.in));
    }

    private void showStatistics() {
        clearScreen();
        gameStats.print();
        System.out.println();
        moveCounter.print();
        pause(new Scanner(System.in));
    }

    private void showHelp() {
        clearScreen();
        helpSystem.print();
        pause(new Scanner(System.in));
    }

    private void exitGame() {
        System.out.println("Спасибо за игру!");
        logger.close();
    }

    private int getDifficultyLevel(String difficulty) {
        if (difficulty.equals("Легко")) return 0;
        if (difficulty.equals("Средне")) return 1;
        if (difficulty.equals("Сложно")) return 2;
        return 0;
    }

    private String getDifficultyString(int level) {
        switch (level) {
            case 0: return "Легко";
            case 1: return "Средне";
            case 2: return "Сложно";
            default: return "Легко";
        }
    }
	private void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    private void pause(Scanner scanner) {
        System.out.println("\nНажмите Enter для продолжения...");
        scanner.nextLine();
    }
}