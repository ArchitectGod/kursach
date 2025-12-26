import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class SchitatelFunctions {
    public static <T extends Number> int calculateTotalValue(List<T> items) {
        int total = 0;
        for (T item : items) {
            total += item.intValue();
        }
        return total;
    }
}