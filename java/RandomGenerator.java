import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class RandomGenerator {
    private Random random;
    private int seed;
	public RandomGenerator() {
        this.seed = (int) System.currentTimeMillis();
        this.random = new Random(seed);
    }

    public RandomGenerator(int s) {
        this.seed = s;
        this.random = new Random(seed);
    }

    public void print() {
        System.out.printf("Генератор случайных чисел, seed: %d%n", seed);
    }

    public int getRandom(int min, int max) {
        return min + random.nextInt(max - min + 1);
    }

    public Coordinate getRandomCoordinate(int maxX, int maxY) {
        return new Coordinate(getRandom(0, maxX - 1), getRandom(0, maxY - 1));
    }
}