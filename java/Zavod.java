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