import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 20. Уведомитель
class Notifier {
    public void print() {
        System.out.println("Система уведомлений");
    }

    public void showWinMessage() {
        System.out.println("🎉 ПОЗДРАВЛЯЕМ! ВЫ ВЫИГРАЛИ! 🎉");
    }

    public void showLoseMessage() {
        System.out.println("💥 ВЫ ПРОИГРАЛИ! ПОПРОБУЙТЕ ЕЩЕ РАЗ! 💥");
    }

    public void showErrorMessage(String message) {
        System.out.println("❌ ОШИБКА: " + message);
    }

    public void showInfoMessage(String message) {
        System.out.println("ℹ️  ИНФО: " + message);
    }
}
