import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class RekordsmenFunctions {
    public static <T extends AbstractRekordsmen> T findBestRezultat(List<T> items) {
        if (items.isEmpty()) return null;
        return Collections.max(items, (a, b) -> 
            Integer.compare(a.getGodUstanovkiRekorda(), b.getGodUstanovkiRekorda()));
    }
}