import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 16. Валидатор
class Validator {
    public void print() {
        System.out.println("Валидатор входных данных");
    }

    public boolean isValidCoordinate(Coordinate coord, int maxX, int maxY) {
        boolean valid = coord.getX() >= 0 && coord.getX() < maxX &&
            coord.getY() >= 0 && coord.getY() < maxY;
        if (!valid) {
            System.out.printf("Неверные координаты! Допустимый диапазон: X:0-%d, Y:0-%d%n", maxX - 1, maxY - 1);
        }
        return valid;
    }

    public boolean isValidName(String name) {
        boolean valid = name != null && !name.isEmpty() && name.length() <= 49;
        if (!valid) {
            System.out.println("Неверное имя! Длина должна быть 1-49 символов");
        }
        return valid;
    }

    public boolean isValidBombCount(int bombs, int width, int height) {
        boolean valid = bombs > 0 && bombs < width * height;
        if (!valid) {
            System.out.printf("Неверное количество бомб! Должно быть от 1 до %d%n", width * height - 1);
        }
        return valid;
    }
}
