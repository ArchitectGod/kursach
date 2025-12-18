import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

interface AbstractZavod {
    void zapustitProizvodstvo();
    void ostanovitProizvodstvo();
    String getNazvanieZavoda();
}