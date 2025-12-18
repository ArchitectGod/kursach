import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class SaveManager {
    private List<GameSave> saves;
    
    public SaveManager() {
        this.saves = new ArrayList<>();
    }
    
    public void print() {
        System.out.printf("Менеджер сохранений, сохранений: %d%n", saves.size());
        for (GameSave save : saves) {
            save.print();
        }
    }
    
    public void createSave(String name) {
        saves.add(new GameSave(name));
        System.out.println("Создано сохранение: " + name);
    }
    
    public boolean loadSave(String name) {
        for (GameSave save : saves) {
            if (save.getName().equals(name)) {
                System.out.println("Загружено сохранение: " + name);
                return true;
            }
        }
        System.out.println("Сохранение не найдено: " + name);
        return false;
    }
}
