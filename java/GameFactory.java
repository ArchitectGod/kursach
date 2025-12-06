import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 17. Фабрика игр
class GameFactory {
    private static GameFactory instance;
    
    public static GameFactory getInstance() {
        if (instance == null) {
            instance = new GameFactory();
        }
        return instance;
    }
    
    private GameFactory() {}

    public void print() {
        System.out.println("Фабрика создания игр");
    }

    public Game createEasyGame(String playerName) {
        if (playerName == null || playerName.trim().isEmpty()) {
            throw new IllegalArgumentException("Имя игрока не может быть пустым");
        }
        
        Board board = new Board(9, 9, 10);
        Player player = new Player(playerName);
        return new Game(board, player);
    }

    public Game createMediumGame(String playerName) {
        if (playerName == null || playerName.trim().isEmpty()) {
            throw new IllegalArgumentException("Имя игрока не может быть пустым");
        }
        
        Board board = new Board(16, 16, 40);
        Player player = new Player(playerName);
        return new Game(board, player);
    }

    public Game createHardGame(String playerName) {
        if (playerName == null || playerName.trim().isEmpty()) {
            throw new IllegalArgumentException("Имя игрока не может быть пустым");
        }
        
        Board board = new Board(30, 16, 99);
        Player player = new Player(playerName);
        return new Game(board, player);
    }

    public Game createCustomGame(String playerName, int width, int height, int bombs) {
        if (playerName == null || playerName.trim().isEmpty()) {
            throw new IllegalArgumentException("Имя игрока не может быть пустым");
        }
        if (width <= 0 || height <= 0) {
            throw new IllegalArgumentException("Размеры поля должны быть положительными");
        }
        if (bombs <= 0 || bombs >= width * height) {
            throw new IllegalArgumentException("Некорректное количество бомб");
        }
        
        Board board = new Board(width, height, bombs);
        Player player = new Player(playerName);
        return new Game(board, player);
    }
}
