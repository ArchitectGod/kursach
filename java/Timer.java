import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 5. Класс таймера
class Timer {
    private long startTime;
    private long pausedTime;
    private boolean isRunning;

    public Timer() {
        this.startTime = 0;
        this.pausedTime = 0;
        this.isRunning = false;
    }

    public void print() {
        System.out.printf("Таймер: %d секунд, статус: %s%n", this.getElapsedTime(), this.isRunning ? "работает" : "на паузе");
    }

    public void inputStart(Scanner scanner) {
        System.out.print("Запустить таймер? (1-да, 0-нет): ");
        int choice = scanner.nextInt();
        if (choice == 1) {
            this.start();
        }
    }

    public void start() {
        this.startTime = System.currentTimeMillis() / 1000;
        this.isRunning = true;
    }

    public void pause() {
        if (this.isRunning) {
            this.pausedTime = System.currentTimeMillis() / 1000;
            this.isRunning = false;
        }
    }

    public void resume() {
        if (!this.isRunning) {
            this.startTime += (System.currentTimeMillis() / 1000 - this.pausedTime);
            this.isRunning = true;
        }
    }

    public int getElapsedTime() {
        if (this.isRunning) {
            return (int)(System.currentTimeMillis() / 1000 - this.startTime);
        }
        return (int)(this.pausedTime - this.startTime);
    }

    public void reset() {
        this.startTime = 0;
        this.pausedTime = 0;
        this.isRunning = false;
    }
}