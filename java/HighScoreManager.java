import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class HighScoreManager {
    private List<HighScore> highScores;
    private final String filename = "highscores.txt";

    public HighScoreManager() {
        this.highScores = new ArrayList<>();
        loadScores();
    }

    public void print() {
        System.out.println("=== ТАБЛИЦА РЕКОРДОВ ===");
        if (highScores.isEmpty()) {
            System.out.println("Рекордов пока нет.");
            return;
        }
        
        for (int i = 0; i < highScores.size() && i < 10; i++) {
            System.out.print((i + 1) + ". ");
            highScores.get(i).print();
        }
    }

    public void addScore(HighScore score) {
        highScores.add(score);
        highScores.sort((a, b) -> Integer.compare(b.getScore(), a.getScore()));

        if (highScores.size() > 10) {
            highScores = new ArrayList<>(highScores.subList(0, 10));
        }
        
        saveScores();
    }

    public void addScore(String playerName, int score, int time, String difficulty) {
        addScore(new HighScore(playerName, score, time, difficulty));
    }

    public void clearScores() {
        highScores.clear();
        saveScores();
    }

    private void loadScores() {
        try (Scanner fileScanner = new Scanner(new File(filename))) {
            highScores.clear();
            while (fileScanner.hasNext()) {
                String name = fileScanner.next();
                int score = fileScanner.nextInt();
                int time = fileScanner.nextInt();
                String difficulty = fileScanner.next();
                highScores.add(new HighScore(name, score, time, difficulty));
            }
        } catch (FileNotFoundException e) {
            // Файл не найден - это нормально при первом запуске
        }
    }
	private void saveScores() {
        try (PrintWriter file = new PrintWriter(new FileWriter(filename))) {
            for (HighScore score : highScores) {
                file.printf("%s %d %d %s%n",
                    score.getName(), score.getScore(),
                    score.getTime(), score.getDifficulty());
            }
        } catch (IOException e) {
            System.out.println("Ошибка сохранения рекордов: " + e.getMessage());
        }
    }
}