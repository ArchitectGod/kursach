import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

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
        System.out.printf("Таймер: %d секунд, статус: %s%n", getElapsedTime(), isRunning ? "работает" : "на паузе");
    }

    public void start() {
        startTime = System.currentTimeMillis() / 1000;
        isRunning = true;
    }

    public void pause() {
        if (isRunning) {
            pausedTime = System.currentTimeMillis() / 1000;
            isRunning = false;
        }
    }

    public void resume() {
        if (!isRunning) {
            startTime += (System.currentTimeMillis() / 1000 - pausedTime);
            isRunning = true;
        }
    }

    public int getElapsedTime() {
        if (isRunning) {
            return (int)(System.currentTimeMillis() / 1000 - startTime);
        }
        return (int)(pausedTime - startTime);
    }

    public void reset() {
        startTime = 0;
        pausedTime = 0;
        isRunning = false;
    }

    public boolean getIsRunning() { return isRunning; }
}
