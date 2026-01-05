import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.TimeUnit;

class Notifier {
    public void showWinMessage() {
        System.out.println("\n🎉 ПОЗДРАВЛЯЕМ! ВЫ ВЫИГРАЛИ! 🎉");
    }

    public void showLoseMessage() {
        System.out.println("\n💥 ВЫ ПРОИГРАЛИ! ПОПРОБУЙТЕ ЕЩЕ РАЗ! 💥");
    }

    public void showErrorMessage(String message) {
        System.out.println("❌ ОШИБКА: " + message);
    }

    public void showInfoMessage(String message) {
        System.out.println("ℹ️  " + message);
    }
}
