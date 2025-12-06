import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 29. Система помощи
class HelpSystem {
    public void print() {
        System.out.println("=== СИСТЕМА ПОМОЩИ ===");
        System.out.println("Цель игры: открыть все клетки без бомб");
        System.out.println("Управление:");
        System.out.println("- ЛКМ: открыть клетку");
        System.out.println("- ПКМ: поставить/убрать флаг");
        System.out.println("Цифры показывают количество бомб вокруг клетки");
    }

    public void showRules() {
        this.print();
    }

    public void showTips() {
        System.out.println("=== СОВЕТЫ ===");
        System.out.println("1. Начинайте с углов");
        System.out.println("2. Используйте флаги для отметки бомб");
        System.out.println("3. Анализируйте цифры для определения безопасных клеток");
        System.out.println("4. Если вокруг клетки 0 бомб, она откроет область автоматически");
    }
public void showControls() {
        System.out.println("=== УПРАВЛЕНИЕ ===");
        System.out.println("WASD/Стрелки - перемещение");
        System.out.println("Пробел - открыть клетку");
        System.out.println("F - поставить/убрать флаг");
        System.out.println("P - пауза");
        System.out.println("H - помощь");
    }
}
