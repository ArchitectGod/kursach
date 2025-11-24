import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 14. Обработчик ввода
class InputHandler {
    public void print() {
        System.out.println("Обработчик ввода пользователя");
    }

    public Coordinate getCellCoordinates(Scanner scanner) {
        System.out.print("Введите координаты X Y: ");
        int x = scanner.nextInt();
        int y = scanner.nextInt();
        return new Coordinate(x, y);
    }

    public String getPlayerName(Scanner scanner) {
        System.out.print("Введите имя игрока: ");
        return scanner.next();
    }

    public int getMenuChoice(Scanner scanner) {
        System.out.print("Выберите действие: ");
        return scanner.nextInt();
    }
}