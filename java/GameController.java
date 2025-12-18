import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class GameController {
    private Game currentGame;
    
    public GameController() {
        this.currentGame = null;
    }
    
    public void print() {
        System.out.println("Контроллер игры, игра " + 
                          (currentGame != null ? "активна" : "не активна"));
    }
    
    public void setGame(Game game) {
        currentGame = game;
    }
    
    public void processMove(int x, int y) {
        if (currentGame != null) {
            currentGame.makeMove(x, y);
        }
    }
    
    public Game getCurrentGame() { return currentGame; }
}