import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

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
}