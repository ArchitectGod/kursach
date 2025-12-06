import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 6. Класс игры
class Game {
    private Board board;
    private Player player;
    private int state;
    private Timer timer;
public Game(Board b, Player p) {
        this.board = b;
        this.player = p;
        this.state = 0;
        this.timer = new Timer();
        this.timer.start();
    }

    public void print() {
        System.out.println("=== СОСТОЯНИЕ ИГРЫ ===");
        System.out.print("Статус: ");
        switch (this.state) {
            case 0: System.out.println("В процессе"); break;
            case 1: System.out.println("ПОБЕДА!"); break;
            case 2: System.out.println("ПРОИГРЫШ"); break;
        }
        System.out.printf("Время игры: %d сек%n", this.getGameTime());
        if (this.board != null) this.board.print();
        if (this.player != null) this.player.print();
    }

    public void inputGameSettings(Scanner scanner) {
        System.out.println("=== НАСТРОЙКИ ИГРЫ ===");
        if (this.board != null) {
            this.board.inputBoardSize(scanner);
        }
        if (this.player != null) {
            this.player.inputPlayerInfo(scanner);
        }
    }

    public void winGame() {
        this.state = 1;
        this.timer.pause();
        if (this.player != null) {
            this.player.updateBestTime();
        }
        System.out.println("🎉 ПОБЕДА! 🎉");
    }

    public void loseGame() {
        this.state = 2;
        this.timer.pause();
        this.board.revealAllBombs();
        if (this.player != null) {
            this.player.addMistake();
        }
        System.out.println("💥 ПРОИГРЫШ! 💥");
    }

    public boolean isGameRunning() {
        return this.state == 0;
    }

    public int getGameTime() {
        return this.timer.getElapsedTime();
    }

    public void pauseGame() {
        this.timer.pause();
        System.out.println("Игра на паузе");
    }

    public void resumeGame() {
        this.timer.resume();
        System.out.println("Игра продолжается");
    }

    public void makeMove(int x, int y, boolean isFlag) {
        if (!this.isGameRunning()) return;

        Cell cell = this.board.getCell(x, y);
        if (cell == null) {
            System.out.println("Неверные координаты!");
            return;
        }

        if (isFlag) {
            cell.toggleFlag();
            System.out.println(cell.getIsFlag() ? "Флаг установлен" : "Флаг снят");
        } else {
            if (cell.getIsFlag()) {
                System.out.println("Сначала снимите флаг!");
                return;
            }

            if (cell.getIsOpen()) {
                System.out.println("Клетка уже открыта!");
                return;
            }

            if (!this.board.areBombsPlaced()) {
                this.board.placeBombs(x, y);
            }

            if (cell.getIsBomb()) {
                this.loseGame();
            } else {
                this.board.openArea(x, y);
                this.player.addOpenedCell();
                
                if (this.board.isGameWon()) {
                    this.winGame();
                }
            }
        }
    }

    public int getState() { return this.state; }
    public Board getBoard() { return this.board; }
    public Player getPlayer() { return this.player; }
}
