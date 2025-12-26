import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Notifier extends Elektropribor {
    public Notifier() {
        super("Уведомитель");
    }
    
    public void print() {
        System.out.printf("Система уведомлений: %s%n", getTipUstroystva());
    }
    
    @Override
    public void vkluchit() {
        super.vkluchit();
        System.out.println("Уведомления включены");
    }
    
    public void showWinMessage() {
        izdatZvuk("🎉 ПОЗДРАВЛЯЕМ! ВЫ ВЫИГРАЛИ! 🎉");
    }
    
    public void showLoseMessage() {
        izdatZvuk("💥 ВЫ ПРОИГРАЛИ! ПОПРОБУЙТЕ ЕЩЕ РАЗ! 💥");
    }
}