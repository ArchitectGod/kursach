import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class Game {
    private Board board;
    private Player player;
    private int state; // 0-в процессе, 1-победа, 2-поражение
    private Timer timer;

    public Game(Board b, Player p) {
        this.board = b;
        this.player = p;
        this.state = 0;
        this.timer = new Timer();
        this.timer.start();
    }
    
    public Game() {
        this(null, null);
    }

    public void print() {
        System.out.println("=== СОСТОЯНИЕ ИГРЫ ===");
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

    public void winGame() {
        state = 1;
        timer.pause();
        if (player != null) {
            player.updateBestTime();
        }
        System.out.println("🎉 ПОБЕДА! 🎉");
    }
	public void loseGame() {
        state = 2;
        timer.pause();
        if (board != null) {
            board.revealAllBombs();
        }
        if (player != null) {
            player.addMistake();
        }
        System.out.println("💥 ПРОИГРЫШ! 💥");
    }

    public boolean isGameRunning() {
        return state == 0;
    }

    public int getGameTime() {
        return timer.getElapsedTime();
    }

    public void pauseGame() {
        timer.pause();
        System.out.println("Игра на паузе");
    }

    public void resumeGame() {
        timer.resume();
        System.out.println("Игра продолжается");
    }

    public void makeMove(int x, int y, boolean open) {
        if (!isGameRunning()) return;

        Cell cell = board.getCell(x, y);
        if (cell == null || cell.getIsOpen()) return;

        if (open) {
            if (!board.areBombsPlaced()) {
                board.placeBombs(x, y);
            }

            if (cell.getIsFlag()) {
                System.out.println("Клетка помечена флагом! Сначала уберите флаг.");
                return;
            }

            cell.open();
            board.decreaseSafeCells();
            if (player != null) player.addOpenedCell();

            if (cell.getIsBomb()) {
                board.revealAllBombs();
                loseGame();
            } else if (board.isGameWon()) {
                winGame();
            }
        } else {
            cell.toggleFlag();
        }
    }

    public int getState() { return state; }
    public Board getBoard() { return board; }
    public Player getPlayer() { return player; }
    public Timer getTimer() { return timer; }

    public void setBoard(Board b) { board = b; }
    public void setPlayer(Player p) { player = p; }
    public void setState(int s) { state = s; }

    public void reset() {
        state = 0;
        timer.reset();
        timer.start();
        if (player != null) player.resetStats();
        if (board != null) board.reset();
    }
}
