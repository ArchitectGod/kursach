import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class GameSave {
    private String saveName;
    private long saveTime;

    public GameSave(String name) {
        this.saveName = name;
        this.saveTime = System.currentTimeMillis();
    }
	public void print() {
        System.out.printf("Сохранение: %s, время: %s%n", saveName, 
            LocalDateTime.ofEpochSecond(saveTime/1000, 0, java.time.ZoneOffset.UTC));
    }

    public String getName() { return saveName; }
    public long getSaveTime() { return saveTime; }
}