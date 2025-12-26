import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class HintSystem {
    private int hintsAvailable;
    private int hintsUsed;
    
    public HintSystem() {
        this.hintsAvailable = 3;
        this.hintsUsed = 0;
    }
    
    public void print() {
        System.out.printf("Система подсказок, доступно подсказок: %d, использовано: %d%n", 
                         hintsAvailable, hintsUsed);
    }
    
    public boolean useHint() {
        if (hintsAvailable > 0) {
            hintsAvailable--;
            hintsUsed++;
            System.out.println("Использована подсказка! Осталось: " + hintsAvailable);
            return true;
        }
        System.out.println("Подсказки закончились!");
        return false;
    }
    
    public int getHintsAvailable() { return hintsAvailable; }
    public int getHintsUsed() { return hintsUsed; }
}