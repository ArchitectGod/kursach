import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 19. Сессия игрока
class PlayerSession {
    private Player player;
    private GameStats stats;

    public PlayerSession(Player p) {
        this.player = p;
        this.stats = new GameStats();
    }

    public void print() {
        System.out.printf("Сессия игрока: %s%n", this.player != null ? this.player.getName() : "нет игрока");
        this.stats.print();
    }
public void inputSessionData(Scanner scanner) {
        System.out.println("Ввод данных сессии...");
        if (this.player != null) {
            this.player.inputPlayerInfo(scanner);
        }
    }

    public void addGameResult(boolean won, int time) {
        this.stats.addGame(won, time);
    }

    public Player getPlayer() { return this.player; }
    public GameStats getStats() { return this.stats; }
}