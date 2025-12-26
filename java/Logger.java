import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Logger {
    private String filename;
    private PrintWriter file;
    
    public Logger(String fname) {
        this.filename = fname;
        try {
            this.file = new PrintWriter(new FileWriter(filename, true));
        } catch (IOException e) {
            System.out.println("Ошибка открытия файла: " + filename);
        }
    }
    
    public void close() {
        if (file != null) {
            file.close();
        }
    }
    
    public void print() {
        System.out.printf("Логгер: файл %s%n", filename);
    }
    
    public void logMessage(String message) {
        if (file != null) {
            file.println(message);
            file.flush();
        }
    }
}