import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Validator {
    public void print() {
        System.out.println("Валидатор входных данных");
    }
    
    public boolean isValidCoordinate(Coordinate coord, int maxX, int maxY) {
        return coord.getX() >= 0 && coord.getX() < maxX && 
               coord.getY() >= 0 && coord.getY() < maxY;
    }
    
    public boolean isValidName(String name) {
        return name != null && !name.isEmpty() && name.length() <= 49;
    }
}

