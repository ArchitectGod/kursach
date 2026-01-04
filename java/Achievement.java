import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class Achievement {
    private String title;
    private String description;
    private boolean unlocked;

    public Achievement(String t, String desc) {
        this.title = t;
        this.description = desc;
        this.unlocked = false;
    }

    public void print() {
        System.out.printf("Достижение: %s - %s [%s]%n", title, description,
            unlocked ? "РАЗБЛОКИРОВАНО" : "заблокировано");
    }

    public void unlock() {
        if (!unlocked) {
            unlocked = true;
        }
    }

    public boolean isUnlocked() { return unlocked; }
}