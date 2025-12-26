import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

public class Minesweeper {
    
    public static void demonstrateJavaFeatures() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ JAVA FEATURES ===\n");
        
        CollectionDemo.demonstrateCollections();
        
        System.out.println("\n9. Демонстрация всех шаблонных классов:");
        
        try {
            TemplateZavod<String> tFactory = new TemplateZavod<>("Шаблонный завод", String.class);
            tFactory.addToQueue("Продукт1");
            tFactory.addToQueue("Продукт2");
            System.out.println("Размер очереди производства: " + tFactory.getQueueSize());
            
            TemplateElektropribor<String> tDevice = new TemplateElektropribor<>("Шаблонное устройство");
            tDevice.vkluchit();
            tDevice.queueSound("Звук1");
            tDevice.queueSound("Звук2");
            tDevice.playAllSounds();
            
            TemplateRekordsmen<Integer, String> tRecord = new TemplateRekordsmen<>("Шаблонный рекорд", 2024);
            tRecord.setRecordData(42);
            tRecord.zaregistrirovatPobedu();
            
            List<Zavod> zavodList = Arrays.asList(
                new Zavod("Завод А"),
                new Zavod("Завод С"),
                new Zavod("Завод Б")
            );
            ZavodFunctions.sortByNazvanie(zavodList);
            System.out.println("Отсортированные заводы:");
            for (Zavod z : zavodList) {
                System.out.println("  " + z.getNazvanieZavoda());
            }
            
            List<Rekordsmen> rekordsList = Arrays.asList(
                new Rekordsmen("Скорость", 2023, "Игрок1"),
                new Rekordsmen("Точность", 2024, "Игрок2"),
                new Rekordsmen("Выносливость", 2022, "Игрок3")
            );
            Rekordsmen best = RekordsmenFunctions.findBestRezultat(rekordsList);
            if (best != null) {
                System.out.println("Лучший результат: год " + best.getGodUstanovkiRekorda());
            }
            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void demonstrateVirtualMethods() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ ВИРТУАЛЬНЫХ МЕТОДОВ ===");
        
        Coordinate coord1 = new Coordinate(1, 1);
        Coordinate coord2 = new Coordinate(2, 2) {
            @Override
            public void virtualMethodDemo() {
                System.out.println("Виртуальный метод Coordinate: переопределенная реализация");
            }
        };
        
        System.out.println("Вызов виртуального метода:");
        coord1.virtualMethodDemo();
        coord2.virtualMethodDemo();
    }
    
    public static void demonstrateProtected() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ МОДИФИКАТОРА PROTECTED ===");
        
        Geografiya geo = new Geografiya("Тестовый регион", 3);
        System.out.println("Доступ к protected полю через публичный метод:");
        System.out.println("Разведано: " + geo.getRazvedeno());
        
        Coordinate coord = new Coordinate(3, 3);
        coord.issledovatTerritoriyu();
    }
    
    public static void demonstrateCloning() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ КЛОНИРОВАНИЯ ===");
		try {
            Coordinate original = new Coordinate(5, 5, "Оригинал", 2, true);
            
            Coordinate shallowCopy = (Coordinate) original.clone();
            System.out.println("Поверхностное клонирование:");
            original.print();
            shallowCopy.print();
            
            Coordinate deepCopy = original.deepClone();
            System.out.println("Глубокое клонирование:");
            deepCopy.print();
            
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
    
    public static void demonstrateInheritance() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ НАСЛЕДОВАНИЯ И ПЕРЕГРУЗКИ ===");
        
        Coordinate coord = new Coordinate(7, 7, "Горный район", 5, false);
        GameFactory factory = new GameFactory("Супер-фабрика");
        SoundSystem sound = new SoundSystem();
        Achievement achievement = new Achievement("Мастер", "Выиграть 50 игр");
        MoveCounter counter = new MoveCounter();
        
        System.out.println("1. Coordinate (наследует Geografiya):");
        coord.pokazatInfo();
        
        System.out.println("\n2. GameFactory (наследует Zavod):");
        factory.zapustitProizvodstvo();
        
        System.out.println("\n3. SoundSystem (наследует Elektropribor):");
        sound.vkluchit();
        sound.playClick();
        
        System.out.println("\n4. Achievement (наследует Rekordsmen):");
        achievement.pokazatRezultat();
        
        System.out.println("\n5. MoveCounter (наследует Schitatel):");
        counter.dobavitBezopasniyHod();
        counter.dobavitFlagHod();
        counter.print();
    }
    
    public static void demonstrateInterfaces() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ ИНТЕРФЕЙСОВ ===");
        
        Geografiya geo = new Geografiya("Интерфейсный регион", 4);
        Elektropribor elec = new Elektropribor("Тестовое устройство");
        Zavod zavod = new Zavod("Тестовый завод");
        
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
    
    public static void demonstrateMultipleInheritance() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ МНОЖЕСТВЕННОГО НАСЛЕДОВАНИЯ ===");
        
        Board board = new Board(5, 5, 3);
        Player player = new Player("Тестовый игрок");
        Game game = new Game(board, player, "Множественный регион");
        
        System.out.println("Game наследует два интерфейса:");
        
        AbstractGeografiya asGeo = game;
        System.out.println("1. Как AbstractGeografiya:");
        asGeo.pokazatInfo();
        asGeo.issledovatTerritoriyu();
        
        AbstractZavod asZavod = game;
        System.out.println("\n2. Как AbstractZavod:");
        asZavod.zapustitProizvodstvo();
        
        System.out.println("\n3. Как обычный Game объект:");
        game.print();
    }
	public static void main(String[] args) {
        demonstrateProtected();
        demonstrateVirtualMethods();
        demonstrateCloning();
        demonstrateInheritance();
        demonstrateInterfaces();
        demonstrateMultipleInheritance();
        demonstrateJavaFeatures();
        
        System.out.println("\n=== РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА ===");
    }
}