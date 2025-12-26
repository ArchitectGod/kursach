import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class RandomGenerator {
    private Random random;
    private int seed;
    
    public RandomGenerator() {
        this.seed = (int)System.currentTimeMillis();
        this.random = new Random(seed);
    }
    
    public RandomGenerator(int seed) {
        this.seed = seed;
        this.random = new Random(seed);
    }
    
    public void print() {
        System.out.printf("Генератор случайных чисел, seed: %d%n", seed);
    }
    
    public int getRandom(int min, int max) {
        return min + random.nextInt(max - min + 1);
    }
}

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
}