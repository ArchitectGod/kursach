import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 13. Отрисовщик
class Renderer {
    public void print() {
        System.out.println("Рендерер для отображения игры");
    }

    public void renderBoard(Board board) {
        board.print();
    }

    public void renderPlayer(Player player) {
        player.print();
    }

    public void renderGame(Game game) {
        game.print();
    }
}