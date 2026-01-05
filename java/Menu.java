import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class Menu {
    public void print() {
        System.out.println("=== ГЛАВНОЕ МЕНЮ ===");
        System.out.println("1. Новая игра");
        System.out.println("2. Настройки");
        System.out.println("3. Таблица лидеров");
        System.out.println("4. Достижения");
        System.out.println("5. Статистика");
        System.out.println("6. Помощь");
        System.out.println("7. Выход");
    }

    public int getChoice(Scanner scanner) {
        System.out.print("Выберите вариант: ");
        return scanner.nextInt();
    }
}