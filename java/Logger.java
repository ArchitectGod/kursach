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
            this.file = new PrintWriter(new FileWriter(this.filename, true));
        } catch (IOException e) {
            System.out.println("Ошибка открытия файла лога: " + e.getMessage());
            throw new RuntimeException("Не удалось создать логгер", e);
        }
    }

    public void print() {
        System.out.printf("Логгер: файл %s%n", this.filename);
    }

    public void inputFilename(Scanner scanner) {
        System.out.print("Введите имя файла для лога: ");
        this.filename = scanner.next();
        try {
            if (this.file != null) this.file.close();
            this.file = new PrintWriter(new FileWriter(this.filename, true));
        } catch (IOException e) {
            System.out.println("Ошибка открытия файла лога: " + e.getMessage());
        }
    }

    public void logMessage(String message) {
        if (this.file != null) {
            try {
                String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
                this.file.printf("[%s] %s%n", timestamp, message);
                this.file.flush();
            } catch (Exception e) {
                System.out.println("Ошибка записи в лог: " + e.getMessage());
            }
        }
    }

    public void validateFilename() throws IllegalArgumentException {
        if (this.filename == null || this.filename.trim().isEmpty()) {
            throw new IllegalArgumentException("Имя файла не может быть пустым");
        }
        if (this.filename.length() > 100) {
            throw new IllegalArgumentException("Имя файла слишком длинное");
        }
    }

    public void logGameStart(String playerName) {
        try {
            this.validateFilename();
            this.logMessage("Игра начата игроком: " + playerName);
        } catch (IllegalArgumentException e) {
            System.out.println("Ошибка валидации: " + e.getMessage());
        }
    }

    public void logGameEnd(String playerName, boolean won) {
        try {
            this.validateFilename();
            this.logMessage("Игра завершена игроком: " + playerName + " Результат: " + (won ? "ПОБЕДА" : "ПОРАЖЕНИЕ"));
        } catch (IllegalArgumentException e) {
            System.out.println("Ошибка валидации: " + e.getMessage());
        }
    }
public void close() {
        if (this.file != null) {
            try {
                this.file.close();
            } catch (Exception e) {
                System.out.println("Ошибка при закрытии файла: " + e.getMessage());
            }
        }
    }
}