import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class Logger {
    private String filename;
    private PrintWriter file;

    public Logger(String fname) {
        this.filename = fname;
        try {
            this.file = new PrintWriter(new FileWriter(filename, true));
        } catch (IOException e) {
            System.out.println("Ошибка открытия файла лога: " + e.getMessage());
        }
    }
    
    public Logger() {
        this("game_log.txt");
    }

    public void print() {
        System.out.printf("Логгер: файл %s%n", filename);
    }

    public void logMessage(String message) {
        if (file != null) {
            String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
            file.printf("[%s] %s%n", timestamp, message);
            file.flush();
        }
        System.out.println("[LOG] " + message);
    }

    public void logGameStart(String playerName) {
        logMessage("Игра начата игроком: " + playerName);
    }

    public void logGameEnd(String playerName, boolean won) {
        logMessage("Игра завершена игроком: " + playerName + " Результат: " + (won ? "ПОБЕДА" : "ПОРАЖЕНИЕ"));
    }

    public void logMove(String playerName, int x, int y, String action) {
        logMessage("Игрок " + playerName + ": " + action + " на [" + x + "," + y + "]");
    }

    public void close() {
        if (file != null) {
            file.close();
        }
    }
}