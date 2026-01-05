import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class HelpSystem {
    public void print() {
        System.out.println("=== СИСТЕМА ПОМОЩИ ===");
        System.out.println("Цель игры: открыть все клетки без бомб");
        System.out.println("Правила:");
        System.out.println("1. Цифры показывают количество бомб вокруг клетки");
        System.out.println("2. Если цифра 0, все соседние клетки безопасны");
        System.out.println("3. Используйте флаги для отметки предполагаемых бомб");
        System.out.println("\nУправление в игре:");
        System.out.println("o - открыть клетку");
        System.out.println("f - поставить/убрать флаг");
        System.out.println("h - получить подсказку");
        System.out.println("p - пауза");
        System.out.println("q - выйти в меню");
    }
}