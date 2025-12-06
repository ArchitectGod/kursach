import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 15. Контроллер игры
class GameController {
    private Game currentGame;

    public GameController() {
        this.currentGame = null;
    }

    public void print() {
        System.out.println("Контроллер игры, игра " + (this.currentGame != null ? "активна" : "не активна"));
    }

    public void inputNewGame(Scanner scanner) {
        System.out.println("Создание новой игры...");
    }

    public void setGame(Game game) {
        this.currentGame = game;
    }

    public void processMove(Coordinate coord, boolean isFlag) {
        if (this.currentGame == null) return;
        this.currentGame.makeMove(coord.getX(), coord.getY(), isFlag);
    }

    public void pauseCurrentGame() {
        if (this.currentGame != null) this.currentGame.pauseGame();
    }

    public void resumeCurrentGame() {
        if (this.currentGame != null) this.currentGame.resumeGame();
    }
}