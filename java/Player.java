import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

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
        System.out.printf("Игрок: %s%n", name);
        System.out.printf("Время: %d сек, Открыто: %d, Ошибок: %d, Лучшее время: %d сек%n",
                timeSpent, openedCells, mistakes, bestTime);
    }

    public void inputPlayerInfo(Scanner scanner) {
        System.out.print("Введите имя игрока: ");
        this.name = scanner.next();
        System.out.print("Введите текущее время игры (сек): ");
        this.timeSpent = scanner.nextInt();
    }

    public void addMistake() {
        mistakes++;
        System.out.printf("Ошибка! Всего ошибок: %d%n", mistakes);
    }

    public void addOpenedCell() {
        openedCells++;
    }

    public void updateBestTime() {
        if (bestTime == 0 || timeSpent < bestTime) {
            bestTime = timeSpent;
            System.out.printf("Новый рекорд: %d сек!%n", bestTime);
        }
    }

    public void addTime(int seconds) {
        timeSpent += seconds;
    }

    public String getName() { return name; }
    public int getTimeSpent() { return timeSpent; }
    public int getOpenedCells() { return openedCells; }
    public int getMistakes() { return mistakes; }
    public int getBestTime() { return bestTime; }

    public void setTimeSpent(int time) { timeSpent = time; }
    public void setName(String newName) { name = newName; }
    
    public void resetStats() {
        openedCells = 0;
        mistakes = 0;
        timeSpent = 0;
    }
}