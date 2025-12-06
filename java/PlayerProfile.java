import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 22. Профиль игрока
class PlayerProfile {
    private Player player;
    private String avatar;
    private int level;

    public PlayerProfile(Player p, String av) {
        this.player = p;
        this.avatar = av;
        this.level = 1;
    }
    
    public PlayerProfile(Player p) {
        this(p, "default");
    }

    public void print() {
        System.out.printf("Профиль игрока: %s%n", this.player != null ? this.player.getName() : "нет игрока");
        System.out.printf("Аватар: %s, Уровень: %d%n", this.avatar, this.level);
    }

    public void inputProfile(Scanner scanner) {
        System.out.println("Настройка профиля:");
        System.out.print("Введите имя аватара: ");
        this.avatar = scanner.next();
    }

    public void levelUp() {
        this.level++;
        System.out.printf("Уровень повышен! Текущий уровень: %d%n", this.level);
    }

    public void setAvatar(String av) {
        this.avatar = av;
    }
}
