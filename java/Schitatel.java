import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Schitatel implements AbstractSchitatel {
    protected String tipSchetchika;
    protected int tekusheeZnachenie;
    
    public Schitatel(String tip, int initialValue) {
        this.tipSchetchika = tip;
        this.tekusheeZnachenie = initialValue;
    }
    
    public Schitatel(String tip) {
        this(tip, 0);
    }
    
    public Schitatel() {
        this("Счетчик", 0);
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