import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class Renderer {
    public void renderBoard(Board board) {
        board.print();
    }

    public void renderPlayer(Player player) {
        player.print();
    }

    public void renderGame(Game game) {
        game.print();
    }

    public void renderGameState(Game game) {
        System.out.println("=== САПЕР ===");
        System.out.println("Время: " + game.getGameTime() + " сек");
        if (game.getPlayer() != null) {
            System.out.println("Игрок: " + game.getPlayer().getName());
        }
        System.out.println();
        if (game.getBoard() != null) {
            renderBoard(game.getBoard());
        }
        System.out.println();
    }
}