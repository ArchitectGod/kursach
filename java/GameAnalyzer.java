import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class GameAnalyzer extends Schitatel {
    private int analyzedGames;
    
    public GameAnalyzer() {
        super("Анализатор игр", 0);
        this.analyzedGames = 0;
    }
    
    public void print() {
        System.out.printf("Анализатор игрового процесса: %s%n", getTipSchetchika());
        System.out.println("Проанализировано игр: " + analyzedGames);
    }
    
    @Override
    public void sbrosit() {
        super.sbrosit();
        analyzedGames = 0;
        System.out.println("Анализатор сброшен");
    }
    
    public void analyzeBoard(Board board) {
        analyzedGames++;
        System.out.printf("Анализ поля %dx%d:%n", board.getWidth(), board.getHeight());
        System.out.println("Количество бомб: " + board.getTotalBombs());
        System.out.printf("Плотность бомб: %.1f%%%n", 
                         (float)board.getTotalBombs() / (board.getWidth() * board.getHeight()) * 100);
    }
}