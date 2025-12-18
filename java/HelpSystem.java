import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class HelpSystem {
    public void print() {
        System.out.println("Система помощи");
    }
    
    public void showTips() {
        System.out.println("=== СОВЕТЫ ДЛЯ САПЁРА ===");
        System.out.println("1. Начинайте с углов или центра");
        System.out.println("2. Используйте флаги для отметки бомб");
        System.out.println("3. Цифра показывает сколько бомб вокруг клетки");
        System.out.println("4. Анализируйте поле, не торопитесь");
    }
}