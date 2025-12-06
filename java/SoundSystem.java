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
        System.out.println("Звуковая система: " + (this.enabled ? "включена" : "выключена"));
    }

    public void inputToggle(Scanner scanner) {
        System.out.print("Переключить звук? (1-вкл, 0-выкл): ");
        int choice = scanner.nextInt();
        this.enabled = (choice == 1);
    }

    public void playClickSound() {
        if (this.enabled) {
            System.out.println("[ЗВУК] Клик!");
        }
    }

    public void playExplosionSound() {
        if (this.enabled) {
            System.out.println("[ЗВУК] БУМ!");
        }
    }

    public void playWinSound() {
        if (this.enabled) {
            System.out.println("[ЗВУК] Победа!");
        }
    }

    public void setEnabled(boolean enable) { this.enabled = enable; }
}