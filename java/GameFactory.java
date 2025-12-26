import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class GameFactory extends Zavod {
    private Map<String, int[]> poleTemplates;
    
    public GameFactory(String nazvanie) {
super(nazvanie);
        this.poleTemplates = new HashMap<>();
        
        poleTemplates.put("Легкое", new int[]{9, 9, 10});
        poleTemplates.put("Среднее", new int[]{16, 16, 40});
        poleTemplates.put("Сложное", new int[]{30, 16, 99});
    }
    
    public GameFactory() {
        this("Фабрика игр");
    }
    
    public void print() {
        System.out.printf("Фабрика игровых полей: %s%n", getNazvanieZavoda());
    }
    
    @Override
    public void zapustitProizvodstvo() {
        super.zapustitProizvodstvo();
        System.out.println("Производство игровых полей запущено!");
    }
    
    public Board createPole(String tip) {
        zapustitProizvodstvo();
        
        int[] params = poleTemplates.get(tip);
        if (params != null) {
            return new Board(params[0], params[1], params[2]);
        }
        return new Board(9, 9, 10);
    }
}