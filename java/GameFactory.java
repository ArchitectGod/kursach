import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class GameFactory {
    public Game createEasyGame(String playerName) {
        Board board = new Board(9, 9, 10);
        Player player = new Player(playerName);
        return new Game(board, player);
    }

    public Game createMediumGame(String playerName) {
        Board board = new Board(16, 16, 40);
        Player player = new Player(playerName);
        return new Game(board, player);
    }

    public Game createHardGame(String playerName) {
        Board board = new Board(30, 16, 99);
        Player player = new Player(playerName);
        return new Game(board, player);
    }

    public Game createCustomGame(String playerName, int width, int height, int bombs) {
        Board board = new Board(width, height, bombs);
        Player player = new Player(playerName);
        return new Game(board, player);
    }
}