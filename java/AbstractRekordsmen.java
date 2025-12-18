import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

interface AbstractRekordsmen {
    void zaregistrirovatPobedu();
    void pokazatRezultat();
    String getKategoriyaSorevnovaniya();
    int getGodUstanovkiRekorda();
}