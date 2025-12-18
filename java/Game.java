import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Game implements AbstractGeografiya, AbstractZavod {
    private Board board;
    private Player player;
    private int state;
    private Timer timer;
    private String nazvanieRegiona;
    private int urovenOpasnosti;
    private String nazvanieZavoda;
    private boolean razvedeno;
    
    public Game(Board board, Player player, String region) {
        this.board = board;
        this.player = player;
        this.state = 0;
        this.timer = new Timer();
        this.nazvanieRegiona = region;
        this.urovenOpasnosti = 1;
        this.nazvanieZavoda = "Игровая фабрика";
        this.razvedeno = false;
        timer.start();
    }
    
    public Game(Board board, Player player) {
        this(board, player, "Игровая зона");
    }
    
    public void print() {
        System.out.println("=== СОСТОЯНИЕ ИГРЫ ===");
        System.out.println("Регион: " + nazvanieRegiona);
        System.out.print("Статус: ");
        switch (state) {
            case 0: System.out.println("В процессе"); break;
            case 1: System.out.println("ПОБЕДА!"); break;
            case 2: System.out.println("ПРОИГРЫШ"); break;
        }
        System.out.printf("Время игры: %d сек%n", getGameTime());
        if (board != null) board.print();
        if (player != null) player.print();
    }
    
    // Реализация методов интерфейса AbstractGeografiya
@Override
    public void issledovatTerritoriyu() {
        System.out.println("Исследование игровой территории: " + nazvanieRegiona);
        razvedeno = true;
    }
    
    @Override
    public void pokazatInfo() {
        System.out.printf("Игра в регионе: %s, Опасность: %d%n", 
                         nazvanieRegiona, urovenOpasnosti);
    }
    
    @Override
    public String getNazvanieRegiona() { return nazvanieRegiona; }
    
    @Override
    public int getUrovenOpasnosti() { return urovenOpasnosti; }
    
    @Override
    public void izmenitOpasnost(int novayaOpasnost) {
        if (novayaOpasnost >= 0 && novayaOpasnost <= 10) {
            urovenOpasnosti = novayaOpasnost;
        }
    }
    
    // Реализация методов интерфейса AbstractZavod
    @Override
    public void zapustitProizvodstvo() {
        System.out.println("Запуск производства игр: " + nazvanieZavoda);
    }
    
    @Override
    public void ostanovitProizvodstvo() {
        System.out.println("Остановка производства игр: " + nazvanieZavoda);
    }
    
    @Override
    public String getNazvanieZavoda() { return nazvanieZavoda; }
    
    public void winGame() {
        state = 1;
        if (player != null) {
            int gameTime = getGameTime();
            player.setTimeSpent(gameTime);
        }
    }
    
    public void loseGame() {
        state = 2;
        if (player != null) {
            player.addMistake();
        }
    }
    
    public boolean isGameRunning() {
        return state == 0;
    }
    
    public int getGameTime() {
        return timer.getElapsedTime();
    }
    
    public void pauseGame() {
        timer.pause();
    }
    
    public void resumeGame() {
        timer.resume();
    }
    
    public void makeMove(int x, int y) {
        if (!isGameRunning() || board == null) return;
        
        Cell cell = board.getCell(x, y);
        if (cell != null && !cell.getIsOpen()) {
            cell.open();
            player.addOpenedCell();
            
            if (cell.getIsBomb()) {
                loseGame();
            }
        }
    }
    
    public int getState() { return state; }
    public Board getBoard() { return board; }
    public Player getPlayer() { return player; }
}