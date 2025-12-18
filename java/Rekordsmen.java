import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Rekordsmen implements AbstractRekordsmen {
    protected String kategoriyaSorevnovaniya;
    protected int godUstanovkiRekorda;
    protected String imyaUchastnika;
    
    public Rekordsmen(String kategoriya, int god, String imya) {
        this.kategoriyaSorevnovaniya = kategoriya;
        this.godUstanovkiRekorda = god;
        this.imyaUchastnika = imya;
    }
    
    public Rekordsmen() {
        this("Категория", 2024, "Участник");
    }
    
    @Override
    public void zaregistrirovatPobedu() {
        System.out.printf("Победа зарегистрирована для %s%n", imyaUchastnika);
    }
    
    @Override
    public void pokazatRezultat() {
        System.out.printf("Рекорд: %s, Участник: %s%n", kategoriyaSorevnovaniya, imyaUchastnika);
    }
    
    @Override
    public String getKategoriyaSorevnovaniya() { return kategoriyaSorevnovaniya; }
    
    @Override
    public int getGodUstanovkiRekorda() { return godUstanovkiRekorda; }
    
    public String getImyaUchastnika() { return imyaUchastnika; }
}