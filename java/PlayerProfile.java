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
        System.out.printf("Профиль игрока: %s%n", player != null ? player.getName() : "нет игрока");
        System.out.printf("Аватар: %s, Уровень: %d%n", avatar, level);
    }

    public void inputProfile(Scanner scanner) {
        System.out.println("Настройка профиля:");
        System.out.print("Введите имя аватара: ");
        this.avatar = scanner.next();
    }

    public void levelUp() {
        level++;
        System.out.printf("Уровень повышен! Текущий уровень: %d%n", level);
    }

    public void setAvatar(String av) {
        avatar = av;
    }
}