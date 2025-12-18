import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class GameHistory {
    private List<String> moves;
    private String playerName;
    private long startTime;
    
    public GameHistory(String player) {
        this.playerName = player;
        this.startTime = System.currentTimeMillis();
        this.moves = new ArrayList<>();
    }
    
    public void print() {
        System.out.println("=== ИСТОРИЯ ХОДОВ: " + playerName + " ===");
        System.out.println("Начало игры: " + new Date(startTime));
        System.out.println("Количество ходов: " + moves.size());
        
        for (int i = 0; i < moves.size(); i++) {
            System.out.println("Ход " + (i + 1) + ": " + moves.get(i));
        }
    }
    
    public void addMove(String move) {
        long currentTime = System.currentTimeMillis();
        int elapsed = (int)((currentTime - startTime) / 1000);
        String timedMove = "[" + elapsed + "с] " + move;
        moves.add(timedMove);
    }
}