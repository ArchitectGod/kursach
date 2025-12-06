import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 4. Класс игрока
class Player {
    private String name;
    private int timeSpent;
    private int openedCells;
    private int mistakes;
    private int bestTime;

    public Player(String playerName) {
        this.name = playerName != null ? playerName : "";
        this.timeSpent = 0;
        this.openedCells = 0;
        this.mistakes = 0;
        this.bestTime = 0;
    }
    
    public Player() {
        this("");
    }

    public void print() {
        System.out.printf("Игрок: %s%n", this.name);
        System.out.printf("Время: %d сек, Открыто: %d, Ошибок: %d, Лучшее время: %d сек%n",
                this.timeSpent, this.openedCells, this.mistakes, this.bestTime);
    }

    public void inputPlayerInfo(Scanner scanner) {
        System.out.print("Введите имя игрока: ");
        this.name = scanner.next();
        System.out.print("Введите текущее время игры (сек): ");
        this.timeSpent = scanner.nextInt();
    }

    public void addMistake() {
        this.mistakes++;
        System.out.printf("Ошибка! Всего ошибок: %d%n", this.mistakes);
    }

    public void addOpenedCell() {
        this.openedCells++;
        System.out.printf("Открыта клетка! Всего открыто: %d%n", this.openedCells);
    }

    public void updateBestTime() {
        if (this.bestTime == 0 || this.timeSpent < this.bestTime) {
            this.bestTime = this.timeSpent;
            System.out.printf("Новый рекорд: %d сек!%n", this.bestTime);
        }
    }

    public void addTime(int seconds) {
        this.timeSpent += seconds;
    }

    public String getName() { return this.name; }
    public int getTimeSpent() { return this.timeSpent; }
    public int getOpenedCells() { return this.openedCells; }
    public int getMistakes() { return this.mistakes; }
    public int getBestTime() { return this.bestTime; }

    public void setTimeSpent(int time) { this.timeSpent = time; }
    public void setName(String newName) { this.name = newName; }
}