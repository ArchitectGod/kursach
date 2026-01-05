import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class GameController {
    private Game currentGame;

    public GameController() {
        this.currentGame = null;
    }

    public void setGame(Game game) {
        currentGame = game;
    }

    public void processMove(Coordinate coord, boolean isFlag) {
        if (currentGame == null) return;
        currentGame.makeMove(coord.getX(), coord.getY(), !isFlag);
    }

    public void pauseCurrentGame() {
        if (currentGame != null) currentGame.pauseGame();
    }

    public void resumeCurrentGame() {
        if (currentGame != null) currentGame.resumeGame();
    }
}