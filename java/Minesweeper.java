import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

public class Minesweeper {
    public static void main(String[] args) {
        Locale.setDefault(Locale.forLanguageTag("ru-RU"));
        
        try (Scanner scanner = new Scanner(System.in)) {
            GameManager gameManager = new GameManager();
            gameManager.run(scanner);
        } catch (Exception e) {
            System.out.println("Ошибка: " + e.getMessage());
            e.printStackTrace();
        }
    }
}