import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 12. Рандомайзер
class RandomGenerator {
    private Random random;

    public RandomGenerator() {
        this.random = new Random();
    }

    public RandomGenerator(int seed) {
        this.random = new Random(seed);
    }

    public void print() {
        System.out.println("Генератор случайных чисел");
    }

    public void inputSeed(Scanner scanner) {
        System.out.print("Введите seed для генератора: ");
        int seed = scanner.nextInt();
        this.random = new Random(seed);
    }

    public int getRandom(int min, int max) {
        return min + random.nextInt(max - min + 1);
    }

    public Coordinate getRandomCoordinate(int maxX, int maxY) {
        return new Coordinate(getRandom(0, maxX - 1), getRandom(0, maxY - 1));
    }
}