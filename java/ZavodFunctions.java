import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class ZavodFunctions {
    public static <T extends AbstractZavod> void sortByNazvanie(List<T> items) {
        items.sort((a, b) -> a.getNazvanieZavoda().compareTo(b.getNazvanieZavoda()));
    }
}