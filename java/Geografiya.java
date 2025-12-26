import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Geografiya implements AbstractGeografiya {
    protected String nazvanieRegiona;
    protected int urovenOpasnosti;
    protected boolean razvedeno;
    
    public Geografiya(String region, int danger) {
        this.nazvanieRegiona = region;
        this.urovenOpasnosti = danger;
        this.razvedeno = false;
    }
    
    public Geografiya() {
        this("Неизвестно", 0);
    }
    
    @Override
    public void issledovatTerritoriyu() {
        if (!razvedeno) {
            razvedeno = true;
        }
    }
    
    @Override
    public void pokazatInfo() {
        System.out.printf("Регион: %s, Опасность: %d%n", nazvanieRegiona, urovenOpasnosti);
    }
    
    @Override
    public String getNazvanieRegiona() { return nazvanieRegiona; }
    
    @Override
    public int getUrovenOpasnosti() { return urovenOpasnosti; }
    
    @Override
    public void izmenitOpasnost(int novayaOpasnost) {
        if (novayaOpasnost >= 0 && novayaOpasnost <= 10) {
            this.urovenOpasnosti = novayaOpasnost;
        }
    }
    
    protected void setRazvedeno(boolean razvedeno) {
        this.razvedeno = razvedeno;
    }
    
    public boolean getRazvedeno() { return razvedeno; }
}
