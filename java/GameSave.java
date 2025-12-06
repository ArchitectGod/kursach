import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 25. Сохранение игры
class GameSave {
    private String saveName;
    private long saveTime;

    public GameSave(String name) {
        this.saveName = name;
        this.saveTime = System.currentTimeMillis();
    }

    public void print() {
        System.out.printf("Сохранение: %s, время: %s%n", this.saveName, new Date(this.saveTime));
    }

    public void inputSaveData(Scanner scanner) {
        System.out.print("Введите имя сохранения: ");
        this.saveName = scanner.next();
        this.saveTime = System.currentTimeMillis();
    }

    public String getName() { return this.saveName; }
    public long getSaveTime() { return this.saveTime; }
}