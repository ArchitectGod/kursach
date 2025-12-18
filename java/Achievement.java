import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Achievement extends Rekordsmen {
    private boolean unlocked;
    private String description;
    
    public Achievement(String category, String desc, int year) {
        super(category, year, "Игрок");
        this.unlocked = false;
        this.description = desc;
    }
    
    public Achievement(String category, String desc) {
        this(category, desc, 2024);
    }
    
    public void print() {
        System.out.printf("Достижение: %s - %s [%s]%n", 
                         getKategoriyaSorevnovaniya(), 
                         description, 
                         unlocked ? "РАЗБЛОКИРОВАНО" : "заблокировано");
    }
    
    @Override
    public void zaregistrirovatPobedu() {
        unlocked = true;
        System.out.println("Достижение разблокировано: " + getKategoriyaSorevnovaniya());
    }
    
    @Override
    public void pokazatRezultat() {
        System.out.printf("Рекорд в категории '%s': %s%n", 
                         getKategoriyaSorevnovaniya(), description);
    }
    
    public boolean isUnlocked() { return unlocked; }
    public String getDescription() { return description; }
}