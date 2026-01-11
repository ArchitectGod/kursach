import java.util.*;

class Settings {
    private boolean sounds;

    public Settings() {
        this.sounds = true;
    }

    public void print() {
        System.out.println("=== НАСТРОЙКИ ===");
        System.out.println("Звуки: " + (sounds ? "Вкл" : "Выкл"));
    }

    public void inputSettings(Scanner scanner) {
        System.out.println("=== ВВОД НАСТРОЕК ===");
        System.out.print("Звуки (0-Выкл, 1-Вкл): ");
        this.sounds = scanner.nextInt() == 1;
    }


    public void toggleSounds() {
        sounds = !sounds;
        System.out.println("Звуки: " + (sounds ? "ВКЛ" : "ВЫКЛ"));
    }


    public boolean getSounds() { return sounds; }
}
