import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class PlayerProfile {
    private Player player;
    private String avatar;
    private int level;
    
    public PlayerProfile(Player player, String avatar) {
        this.player = player;
        this.avatar = avatar;
        this.level = 1;
	}
    
    public PlayerProfile(Player player) {
        this(player, "default");
    }
    
    public void print() {
        System.out.printf("Профиль игрока: %s%n", 
                         player != null ? player.getName() : "нет игрока");
        System.out.printf("Аватар: %s, Уровень: %d%n", avatar, level);
    }
    
    public void levelUp() {
        level++;
        System.out.printf("%s повысил уровень до %d!%n", 
                         player.getName(), level);
    }
}