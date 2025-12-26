import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class MoveCounter extends Schitatel {
    private int vsegoHodov;
    private int bezopasnyeHody;
    private int flagHody;
    private int bombHody;
    
    public MoveCounter() {
        super("Счетчик ходов", 0); 
        this.vsegoHodov = 0;
        this.bezopasnyeHody = 0;
        this.flagHody = 0;
        this.bombHody = 0;
    }
    
    public void print() {
        System.out.println("=== СТАТИСТИКА ХОДОВ ===");
        System.out.println("Тип счетчика: " + getTipSchetchika());
        System.out.println("Всего ходов: " + vsegoHodov);
        System.out.printf("Безопасные: %d, Флаги: %d, Бомбы: %d%n", 
                         bezopasnyeHody, flagHody, bombHody);
    }
    
    @Override
    public void sbrosit() {
        super.sbrosit();
        vsegoHodov = 0;
        bezopasnyeHody = 0;
        flagHody = 0;
        bombHody = 0;
        System.out.println("Счетчик ходов сброшен");
    }
    
    @Override
    public void pokazatTekushee() {
        System.out.println("Текущее состояние счетчика: " + vsegoHodov + " ходов");
    }
    
    public void dobavitBezopasniyHod() {
        vsegoHodov++;
        bezopasnyeHody++;
    }
    
    public void dobavitFlagHod() {
        vsegoHodov++;
        flagHody++;
    }
    
    public void dobavitBombHod() {
        vsegoHodov++;
        bombHody++;
    }
    
    public int getVsegoHodov() { return vsegoHodov; }
    public int getBezopasnyeHody() { return bezopasnyeHody; }
    public int getFlagHody() { return flagHody; }
    public int getBombHody() { return bombHody; }
    
    public float getEffectiveness() {
        if (vsegoHodov == 0) return 0.0f;
        return (float)bezopasnyeHody / vsegoHodov * 100.0f;
    }
}
