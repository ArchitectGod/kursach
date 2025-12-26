import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class GeografiyaFunctions {
    public static <T extends AbstractGeografiya> double calculateAverageUroven(List<T> items) {
        if (items.isEmpty()) return 0.0;
        int sum = 0;
        for (T item : items) {
            sum += item.getUrovenOpasnosti();
        }
        return (double) sum / items.size();
    }
}