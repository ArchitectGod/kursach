import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class GameAnalyzer {
    public void analyzeBoard(Board board) {
        int flaggedBombs = 0;
        int totalBombs = board.getTotalBombs();

        System.out.printf("Анализ поля: бомб %d, безопасных клеток осталось: %d%n",
            totalBombs, board.getSafeCellsLeft());
    }

    public void analyzePlayer(Player player) {
        System.out.printf("Анализ игрока: %s%n", player.getName());
        System.out.printf("Эффективность: %.1f%%%n",
            player.getOpenedCells() > 0 ?
            (float)(player.getOpenedCells() - player.getMistakes()) / player.getOpenedCells() * 100 : 0);
    }

    public void analyzeGame(Game game) {
        System.out.println("Анализ игры:");
        System.out.println("Статус: " + (game.isGameRunning() ? "в процессе" : (game.getState() == 1 ? "победа" : "поражение")));
        System.out.println("Время: " + game.getGameTime() + " сек");
    }
}