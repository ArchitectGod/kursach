import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 23. Достижение
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

    public void inputUnlock(Scanner scanner) {
        System.out.printf("Разблокировать достижение '%s'? (1-да, 0-нет): ", title);
        int choice = scanner.nextInt();
        if (choice == 1) unlock();
    }

    public void unlock() {
        unlocked = true;
        System.out.printf("🎊 Достижение разблокировано: %s! 🎊%n", title);
    }

    public boolean isUnlocked() { return unlocked; }
}
