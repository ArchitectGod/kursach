import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class SoundSystem {
    private boolean enabled;

    public SoundSystem() {
        this.enabled = true;
    }

    public void playClickSound() {
        if (enabled) {
            System.out.print("\u0007"); 
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
    public boolean isEnabled() { return enabled; }
}