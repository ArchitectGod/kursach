import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class GameSave {
    private String saveName;
    private long saveTime;
    
    public GameSave(String name) {
        this.saveName = name;
        this.saveTime = System.currentTimeMillis();
    }
    
    public void print() {
        System.out.printf("Сохранение: %s, время: %s%n", 
                         saveName, new Date(saveTime));
    }
    
    public String getName() { return saveName; }
    public long getSaveTime() { return saveTime; }
}