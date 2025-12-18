import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Menu {
    public void print() {
        System.out.println("=== ГЛАВНОЕ МЕНЮ ===");
        System.out.println("1. Новая игра");
        System.out.println("2. Загрузить игру");
        System.out.println("3. Настройки");
        System.out.println("4. Таблица лидеров");
        System.out.println("5. Выход");
    }
    
    public int getChoice(Scanner scanner) {
        System.out.print("Выберите вариант: ");
        return scanner.nextInt();
    }
}