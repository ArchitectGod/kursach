import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 27. Звуковая система
class SoundSystem {
    private boolean enabled;

    public SoundSystem() {
        this.enabled = true;
    }
public void print() {
        System.out.println("Звуковая система: " + (enabled ? "включена" : "выключена"));
    }

    public void inputToggle(Scanner scanner) {
        System.out.print("Переключить звук? (1-вкл, 0-выкл): ");
        int choice = scanner.nextInt();
        enabled = (choice == 1);
    }

    public void playClickSound() {
        if (enabled) {
            System.out.println("[ЗВУК] Клик!");
        }
    }

    public void playExplosionSound() {
        if (enabled) {
            System.out.println("[ЗВУК] БУМ!");
        }
    }

    public void playWinSound() {
        if (enabled) {
            System.out.println("[ЗВУК] Победа!");
        }
    }

    public void setEnabled(boolean enable) { enabled = enable; }
}