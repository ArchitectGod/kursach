import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Zavod implements AbstractZavod {
    protected String nazvanieZavoda;
    protected boolean rabotaet;
    
    public Zavod(String nazvanie) {
        this.nazvanieZavoda = nazvanie;
        this.rabotaet = false;
    }
    
    public Zavod() {
        this("Завод");
    }
    
    @Override
    public void zapustitProizvodstvo() {
        rabotaet = true;
    }
    
    @Override
    public void ostanovitProizvodstvo() {
        rabotaet = false;
    }
    
    @Override
    public String getNazvanieZavoda() { return nazvanieZavoda; }
    
    public boolean getRabotaet() { return rabotaet; }
}

class Schitatel implements AbstractSchitatel {
    protected String tipSchetchika;
    protected int tekusheeZnachenie;
    
    public Schitatel(String tip) {
        this.tipSchetchika = tip;
        this.tekusheeZnachenie = 0;
    }
    
    public Schitatel() {
        this("Счетчик");
    }
    
    @Override
    public void sbrosit() {
        tekusheeZnachenie = 0;
    }
    
    @Override
    public void pokazatTekushee() {
        System.out.printf("Счетчик %s: %d%n", tipSchetchika, tekusheeZnachenie);
    }
    
    @Override
    public String getTipSchetchika() { return tipSchetchika; }
    
    public int getTekusheeZnachenie() { return tekusheeZnachenie; }
}