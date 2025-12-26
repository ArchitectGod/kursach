import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class SoundSystem extends Elektropribor {
    private String nazvanieUstroystva;
    private List<String> zvukovyeEffekti;
    
    public SoundSystem(String deviceName) {
        super("Звуковая система");
        this.nazvanieUstroystva = deviceName;
        this.zvukovyeEffekti = Arrays.asList("click", "flag", "bomb", "win", "lose");
    }
    
    public SoundSystem() {
        this("Игровая звуковая система");
    }
    
    public void print() {
        System.out.printf("Звуковая система: %s (%s)%n", 
                         nazvanieUstroystva, getTipUstroystva());
    }
    
    @Override
    public void izdatZvuk(String zvuk) {
        if (getVklyuchen()) {
            switch (zvuk) {
                case "click": System.out.println("[ЗВУК] Клик"); break;
                case "flag": System.out.println("[ЗВУК] Флаг"); break;
                case "bomb": System.out.println("[ЗВУК] ВЗРЫВ!"); break;
                case "win": System.out.println("[ЗВУК] ПОБЕДА!"); break;
                case "lose": System.out.println("[ЗВУК] Поражение"); break;
                default: System.out.println("[ЗВУК] " + zvuk); break;
            }
        }
    }
    
    public void playClick() { izdatZvuk("click"); }
    public void playFlag() { izdatZvuk("flag"); }
    public void playBomb() { izdatZvuk("bomb"); }
    public void playWin() { izdatZvuk("win"); }
    public void playLose() { izdatZvuk("lose"); }
}