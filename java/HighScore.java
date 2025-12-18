import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class HighScore extends Rekordsmen {
    private String imyaIgroka;
    private int rezultat;
    
    public HighScore(String playerName, int result, String category, int year) {
super(category, year, playerName);
        this.imyaIgroka = playerName;
        this.rezultat = result;
    }
    
    public HighScore(String playerName, int result) {
        this(playerName, result, "Время", 2024);
    }
    
    public void print() {
        System.out.printf("Рекорд: %s - %d", imyaIgroka, rezultat);
        if (getKategoriyaSorevnovaniya().equals("Время")) System.out.print(" сек");
        System.out.printf(", Категория: %s, Год: %d%n", 
                         getKategoriyaSorevnovaniya(), getGodUstanovkiRekorda());
    }
    
    public int getRezultat() { return rezultat; }
    public String getImyaIgroka() { return imyaIgroka; }
}
