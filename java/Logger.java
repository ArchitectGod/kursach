import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 8. Класс логгера
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

    public void print() {
        System.out.printf("Логгер: файл %s%n", filename);
    }

    public void inputFilename(Scanner scanner) {
        System.out.print("Введите имя файла для лога: ");
        this.filename = scanner.next();
        try {
            if (file != null) file.close();
            this.file = new PrintWriter(new FileWriter(filename, true));
        } catch (IOException e) {
            System.out.println("Ошибка открытия файла лога: " + e.getMessage());
        }
    }

    public void logMessage(String message) {
        if (file != null) {
            String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
            file.printf("[%s] %s%n", timestamp, message);
            file.flush();
        }
    }

    public void logGameStart(String playerName) {
        logMessage("Игра начата игроком: " + playerName);
    }

    public void logGameEnd(String playerName, boolean won) {
        logMessage("Игра завершена игроком: " + playerName + " Результат: " + (won ? "ПОБЕДА" : "ПОРАЖЕНИЕ"));
    }

    public void close() {
        if (file != null) {
            file.close();
        }
    }
}