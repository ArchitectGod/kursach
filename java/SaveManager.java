import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// 26. Менеджер сохранений
class SaveManager {
    private List<GameSave> saves;

    public SaveManager() {
        this.saves = new ArrayList<>();
    }

    public void print() {
        System.out.printf("Менеджер сохранений, сохранений: %d%n", this.saves.size());
        for (GameSave save : this.saves) {
            save.print();
        }
    }

    public void inputCreateSave(Scanner scanner) {
        GameSave save = new GameSave("");
        save.inputSaveData(scanner);
        this.saves.add(save);
    }

    public void createSave(String name) {
        if (name == null || name.trim().isEmpty()) {
            throw new IllegalArgumentException("Имя сохранения не может быть пустым");
        }
        this.saves.add(new GameSave(name));
    }

    public boolean loadSave(String name) {
        try {
            if (name == null) {
                throw new IllegalArgumentException("Имя сохранения не может быть null");
            }
            
            for (GameSave save : this.saves) {
                if (save.getName().equals(name)) {
                    System.out.println("Загружаем сохранение: " + name);
                    return true;
                }
            }
            return false;
        } catch (IllegalArgumentException e) {
            System.out.println("Ошибка загрузки: " + e.getMessage());
            return false;
        }
    }
public void deleteSave(String name) {
        try {
            if (name == null) {
                throw new IllegalArgumentException("Имя сохранения не может быть null");
            }
            
            boolean removed = this.saves.removeIf(save -> save.getName().equals(name));
            if (!removed) {
                System.out.println("Сохранение не найдено: " + name);
            }
        } catch (IllegalArgumentException e) {
            System.out.println("Ошибка удаления: " + e.getMessage());
        }
    }
}
