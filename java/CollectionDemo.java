import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class CollectionDemo {
    
    public static void demonstrateCollections() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ COLLECTIONS FRAMEWORK ===\n");
        
        List<AbstractGeografiya> regions = new ArrayList<>();
        regions.add(new Geografiya("Север", 3));
        regions.add(new Geografiya("Юг", 7));
        regions.add(new Geografiya("Запад", 2));
        regions.add(new Geografiya("Восток", 5));
        
        System.out.println("1. ArrayList - сортировка регионов по опасности:");
        regions.sort((a, b) -> Integer.compare(a.getUrovenOpasnosti(), b.getUrovenOpasnosti()));
        for (AbstractGeografiya region : regions) {
            region.pokazatInfo();
        }
        
        System.out.println("\n2. Collections.max - максимальная опасность:");
        AbstractGeografiya maxRegion = Collections.max(regions, 
            (a, b) -> Integer.compare(a.getUrovenOpasnosti(), b.getUrovenOpasnosti()));
        System.out.print("Самый опасный регион: ");
        maxRegion.pokazatInfo();
        
        int[] dangerLevels = {3, 7, 2, 5, 9};
        System.out.println("\n3. Массив (аналог std::array):");
        System.out.println("Второй элемент массива: " + dangerLevels[1]);
        
        Map<String, AbstractZavod> factories = new HashMap<>();
        factories.put("Основной", new Zavod("Главный завод"));
        factories.put("Вспомогательный", new Zavod("Второстепенный завод"));
        
        System.out.println("\n4. HashMap - фабрики:");
        for (Map.Entry<String, AbstractZavod> entry : factories.entrySet()) {
            System.out.println("Ключ: " + entry.getKey() + ", Завод: " + entry.getValue().getNazvanieZavoda());
        }
        
        List<AbstractElektropribor> devices = new LinkedList<>();
        devices.add(new Elektropribor("Колонки"));
        devices.add(new Elektropribor("Наушники"));
        
        System.out.println("\n5. LinkedList - электроприборы:");
        for (AbstractElektropribor device : devices) {
            device.vkluchit();
            device.izdatZvuk("тестовый звук");
        }
        
        System.out.println("\n6. Stream API - фильтрация и поиск:");
        boolean anyDangerous = regions.stream()
            .anyMatch(r -> r.getUrovenOpasnosti() > 5);
        System.out.println("Есть ли опасные регионы (опасность > 5): " + anyDangerous);
        
        Optional<AbstractGeografiya> dangerousRegion = regions.stream()
            .filter(r -> r.getUrovenOpasnosti() > 5)
            .findFirst();
        dangerousRegion.ifPresent(r -> {
            System.out.print("Первый опасный регион: ");
            r.pokazatInfo();
        });
        
        System.out.println("\n7. Stream API - преобразование:");
        List<String> regionNames = regions.stream()
            .map(AbstractGeografiya::getNazvanieRegiona)
            .sorted()
            .toList();
        System.out.println("Отсортированные названия регионов: " + regionNames);
        
        System.out.println("\n8. Демонстрация шаблонных классов и функций:");
        
        TemplateGeografiya<Integer> tGeo = new TemplateGeografiya<>("Шаблонный регион", 5, 100);
        tGeo.addRegion(new Geografiya("Вложенный регион", 3));
        tGeo.issledovatTerritoriyu();
        System.out.println("Параметр шаблонной географии: " + tGeo.getParam());
        
        TemplateSchitatel<Double> tCounter = new TemplateSchitatel<>("Шаблонный счетчик", 3.14);
        tCounter.increment(1.5);
        tCounter.pokazatTekushee();
        
        double avgDanger = GeografiyaFunctions.calculateAverageUroven(regions);
        System.out.println("Средняя опасность регионов: " + avgDanger);
        
        List<Elektropribor> elecList = Arrays.asList(
            new Elektropribor("Колонки"),
            new Elektropribor("Наушники"),
			new Elektropribor("Колонки")
        );
        String commonTip = ElektropriborFunctions.findMostCommonTip(elecList);
        System.out.println("Самый распространенный тип устройства: " + commonTip);
        
        List<Schitatel> counters = Arrays.asList(
            new Schitatel("Счетчик1", 10),
            new Schitatel("Счетчик2", 20),
            new Schitatel("Счетчик3", 30)
        );
        List<Integer> counterValues = Arrays.asList(10, 20, 30);
        int total = SchitatelFunctions.calculateTotalValue(counterValues);
        System.out.println("Общее значение всех счетчиков: " + total);
    }
}