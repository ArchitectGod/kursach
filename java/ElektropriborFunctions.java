import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class ElektropriborFunctions {
    public static <T extends AbstractElektropribor> String findMostCommonTip(List<T> items) {
        if (items.isEmpty()) return "";
        Map<String, Integer> tipCount = new HashMap<>();
        for (T item : items) {
            String tip = item.getTipUstroystva();
            tipCount.put(tip, tipCount.getOrDefault(tip, 0) + 1);
        }
        return Collections.max(tipCount.entrySet(), Map.Entry.comparingByValue()).getKey();
    }
}