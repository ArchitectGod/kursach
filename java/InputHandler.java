import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class InputHandler {
    public Coordinate getCellCoordinates(Scanner scanner) {
        int[] coords = new int[2];
        System.out.print("Введите координаты X Y: ");
        coords[0] = scanner.nextInt();
        coords[1] = scanner.nextInt();
        return new Coordinate(coords[0], coords[1]);
    }
    private void clearInputBuffer(Scanner scanner) {
		if (scanner.hasNextLine()) {
			scanner.nextLine();
		}
	}
    public String getPlayerName(Scanner scanner) {
        System.out.print("Введите имя игрока: ");
        String name = scanner.next();
        clearInputBuffer(scanner);
        return name;
    }

    public int getMenuChoice(Scanner scanner) {
        System.out.print("Выберите действие: ");
        return scanner.nextInt();
    }

    public char getAction(Scanner scanner) {
        System.out.print("Выберите действие (o-открыть, f-флаг, h-помощь, q-выход): ");
        char action = scanner.next().charAt(0);
        clearInputBuffer(scanner);
        return action;
    }
}
