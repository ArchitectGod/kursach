import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

public class Minesweeper {
    
    // Демонстрация виртуальных методов
    public static void demonstrateVirtualMethods() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ ВИРТУАЛЬНЫХ МЕТОДОВ ===");
        
        // Создаем объекты
        Coordinate coord1 = new Coordinate(1, 1);
        Coordinate coord2 = new Coordinate(2, 2) {
            @Override
            public void virtualMethodDemo() {
                System.out.println("Виртуальный метод Coordinate: переопределенная реализация");
            }
        };
        
        // Вызов через базовый класс (в Java все методы виртуальные)
        System.out.println("Вызов виртуального метода:");
        coord1.virtualMethodDemo();
        coord2.virtualMethodDemo();
    }
    
    // Демонстрация protected модификатора
    public static void demonstrateProtected() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ МОДИФИКАТОРА PROTECTED ===");
        
        Geografiya geo = new Geografiya("Тестовый регион", 3);
        
        // Нельзя напрямую получить доступ к protected полю razvedeno
        // но можно через публичный метод
        System.out.println("Доступ к protected полю через публичный метод:");
        System.out.println("Разведано: " + geo.getRazvedeno());
        
        // Демонстрация protected метода в производном классе
        Coordinate coord = new Coordinate(3, 3);
        coord.issledovatTerritoriyu(); // Вызывает переопределенный метод
    }
    
    // Демонстрация клонирования
    public static void demonstrateCloning() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ КЛОНИРОВАНИЯ ===");
        
        try {
            Coordinate original = new Coordinate(5, 5, "Оригинал", 2, true);
            
            // Поверхностное клонирование
            Coordinate shallowCopy = (Coordinate) original.clone();
            System.out.println("Поверхностное клонирование:");
            original.print();
            shallowCopy.print();
			// Глубокое клонирование
            Coordinate deepCopy = original.deepClone();
            System.out.println("Глубокое клонирование:");
            deepCopy.print();
            
            // Изменяем оригинал
            original.setX(10);
            System.out.println("После изменения оригинала:");
            original.print();
            System.out.print("Поверхностная копия: ");
            shallowCopy.print();
            System.out.print("Глубокая копия: ");
            deepCopy.print();
            
        } catch (CloneNotSupportedException e) {
            System.out.println("Ошибка клонирования: " + e.getMessage());
        }
    }
    
    // Демонстрация наследования и перегрузки методов
    public static void demonstrateInheritance() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ НАСЛЕДОВАНИЯ И ПЕРЕГРУЗКИ ===");
        
        // Создаем объекты разных классов с наследованием
        Coordinate coord = new Coordinate(7, 7, "Горный район", 5, false);
        GameFactory factory = new GameFactory("Супер-фабрика");
        SoundSystem sound = new SoundSystem();
        Achievement achievement = new Achievement("Мастер", "Выиграть 50 игр");
        MoveCounter counter = new MoveCounter();
        
        System.out.println("1. Coordinate (наследует Geografiya):");
        coord.pokazatInfo(); // Перегруженный метод
        
        System.out.println("\n2. GameFactory (наследует Zavod):");
        factory.zapustitProizvodstvo(); // Перегруженный метод
        
        System.out.println("\n3. SoundSystem (наследует Elektropribor):");
        sound.vkluchit();
        sound.playClick();
        
        System.out.println("\n4. Achievement (наследует Rekordsmen):");
        achievement.pokazatRezultat(); // Перегруженный метод
        
        System.out.println("\n5. MoveCounter (наследует Schitatel):");
        counter.dobavitBezopasniyHod();
        counter.dobavitFlagHod();
        counter.print(); // Собственный метод
    }
    
    // Демонстрация интерфейсов
    public static void demonstrateInterfaces() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ ИНТЕРФЕЙСОВ ===");
        
        // Создаем объекты, реализующие интерфейсы
        Geografiya geo = new Geografiya("Интерфейсный регион", 4);
        Elektropribor elec = new Elektropribor("Тестовое устройство");
        Zavod zavod = new Zavod("Тестовый завод");
        
        // Работа через интерфейсы
        AbstractGeografiya abstractGeo = geo;
        AbstractElektropribor abstractElec = elec;
        AbstractZavod abstractZavod = zavod;
        
        System.out.println("1. Работа через интерфейс AbstractGeografiya:");
        abstractGeo.pokazatInfo();
        abstractGeo.issledovatTerritoriyu();
        
        System.out.println("\n2. Работа через интерфейс AbstractElektropribor:");
        abstractElec.vkluchit();
        abstractElec.izdatZvuk("Тестовый звук");
        
        System.out.println("\n3. Работа через интерфейс AbstractZavod:");
        abstractZavod.zapustitProizvodstvo();
    }
    
    // Демонстрация множественного наследования (Game наследует два интерфейса)
    public static void demonstrateMultipleInheritance() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ МНОЖЕСТВЕННОГО НАСЛЕДОВАНИЯ ===");
        
        Board board = new Board(5, 5, 3);
        Player player = new Player("Тестовый игрок");
        Game game = new Game(board, player, "Множественный регион");
        
        System.out.println("Game наследует два интерфейса:");
        
        // Использование как AbstractGeografiya
        AbstractGeografiya asGeo = game;
        System.out.println("1. Как AbstractGeografiya:");
        asGeo.pokazatInfo();
        asGeo.issledovatTerritoriyu();
        
        // Использование как AbstractZavod
		AbstractZavod asZavod = game;
        System.out.println("\n2. Как AbstractZavod:");
        asZavod.zapustitProizvodstvo();
        
        System.out.println("\n3. Как обычный Game объект:");
        game.print();
    }
    
    public static void main(String[] args) {
        System.out.println("=== ПРОГРАММА САПЁР НА JAVA ===");
        
        // Демонстрация всех возможностей
        demonstrateProtected();
        demonstrateVirtualMethods();
        demonstrateCloning();
        demonstrateInheritance();
        demonstrateInterfaces();
        demonstrateMultipleInheritance();
        
        System.out.println("\n=== РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА ===");
    }
}