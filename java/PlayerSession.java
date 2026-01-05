import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class PlayerSession {
    private Player player;
    private GameStats stats;

    public PlayerSession(Player p) {
        this.player = p;
        this.stats = new GameStats();
    }

    public void print() {
        System.out.printf("Сессия игрока: %s%n", player != null ? player.getName() : "нет игрока");
        stats.print();
    }

    public void addGameResult(boolean won, int time) {
        stats.addGame(won, time);
    }

    public Player getPlayer() { return player; }
    public GameStats getStats() { return stats; }
}
