import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

interface AbstractGeografiya {
    void issledovatTerritoriyu();
    void pokazatInfo();
    String getNazvanieRegiona();
    int getUrovenOpasnosti();
    void izmenitOpasnost(int novayaOpasnost);
}