import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class HighScoreManager {
    private List<HighScore> highScores;
    
    public HighScoreManager() {
        this.highScores = new ArrayList<>();
    }
    
    public void print() {
        System.out.println("=== ТАБЛИЦА РЕКОРДОВ ===");
        if (highScores.isEmpty()) {
            System.out.println("Рекордов пока нет");
            return;
        }
        
        for (int i = 0; i < highScores.size() && i < 10; i++) {
            System.out.print((i + 1) + ". ");
            highScores.get(i).print();
        }
    }
    
    public void addScore(HighScore score) {
        highScores.add(score);
        highScores.sort((a, b) -> Integer.compare(a.getRezultat(), b.getRezultat()));
        
        if (highScores.size() > 10) {
            highScores = new ArrayList<>(highScores.subList(0, 10));
        }
    }
    
    public void saveToFile(String filename) {
        try (PrintWriter file = new PrintWriter(new FileWriter(filename))) {
            for (HighScore score : highScores) {
                file.printf("%s,%d,%s,%d%n",
                           score.getImyaIgroka(),
                           score.getRezultat(),
                           score.getKategoriyaSorevnovaniya(),
                           score.getGodUstanovkiRekorda());
            }
            System.out.println("Рекорды сохранены в " + filename);
        } catch (IOException e) {
            System.out.println("Ошибка сохранения рекордов: " + e.getMessage());
        }
    }
}