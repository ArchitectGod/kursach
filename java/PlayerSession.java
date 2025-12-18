import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class PlayerSession {
    private Player player;
    private GameStats stats;
    
    public PlayerSession(Player player) {
        this.player = player;
        this.stats = new GameStats();
    }
    
    public void print() {
        System.out.printf("Сессия игрока: %s%n", 
                         player != null ? player.getName() : "нет игрока");
        stats.print();
    }
    
    public void addGameResult(boolean won, int time) {
        stats.addGame(won, time);
    }
}