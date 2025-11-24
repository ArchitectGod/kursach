import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 34. История игры
class GameHistory {
    private List<String> moves;
    private List<Coordinate> positions;

    public GameHistory() {
        this.moves = new ArrayList<>();
        this.positions = new ArrayList<>();
    }

    public void print() {
        System.out.println("=== ИСТОРИЯ ХОДОВ ===");
        for (int i = 0; i < moves.size(); i++) {
            System.out.printf("Ход %d: %s в (%d,%d)%n",
                i + 1, moves.get(i),
                positions.get(i).getX(), positions.get(i).getY());
        }
    }

    public void inputClearHistory(Scanner scanner) {
        System.out.print("Очистить историю? (1-да, 0-нет): ");
        int choice = scanner.nextInt();
        if (choice == 1) clearHistory();
    }

    public void addMove(String move, Coordinate coord) {
        moves.add(move);
        positions.add(coord);
    }

    public void clearHistory() {
        moves.clear();
        positions.clear();
        System.out.println("История очищена!");
    }

    public int getMoveCount() {
        return moves.size();
    }

    public void printLastMoves(int count) {
        int start = Math.max(0, moves.size() - count);
        System.out.printf("Последние %d ходов:%n", count);
        for (int i = start; i < moves.size(); i++) {
            System.out.printf("Ход %d: %s в (%d,%d)%n",
                i + 1, moves.get(i),
                positions.get(i).getX(), positions.get(i).getY());
        }
    }
}