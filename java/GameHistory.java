import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class GameHistory {
    private List<Pair<String, Coordinate>> moves;

    private static class Pair<F, S> {
        public final F first;
        public final S second;
        
        public Pair(F first, S second) {
            this.first = first;
            this.second = second;
        }
    }

    public GameHistory() {
        this.moves = new ArrayList<>();
    }

    public void print() {
        System.out.println("=== ИСТОРИЯ ХОДОВ ===");
        if (moves.isEmpty()) {
            System.out.println("История пуста.");
            return;
        }
        
        int start = Math.max(0, moves.size() - 10);
        for (int i = start; i < moves.size(); i++) {
            System.out.printf("Ход %d: %s в (%d,%d)%n",
                i + 1, moves.get(i).first,
                moves.get(i).second.getX(), moves.get(i).second.getY());
        }
    }

    public void addMove(String move, Coordinate coord) {
        moves.add(new Pair<>(move, coord));
    }

    public void clear() {
        moves.clear();
    }

    public int getMoveCount() {
        return moves.size();
    }
}