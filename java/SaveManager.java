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
        System.out.printf("Менеджер сохранений, сохранений: %d%n", saves.size());
        for (GameSave save : saves) {
            save.print();
        }
    }

    public void inputCreateSave(Scanner scanner) {
        GameSave save = new GameSave("");
        save.inputSaveData(scanner);
        saves.add(save);
    }

    public void createSave(String name) {
        saves.add(new GameSave(name));
    }

    public boolean loadSave(String name) {
        for (GameSave save : saves) {
            if (save.getName().equals(name)) {
                System.out.println("Загружаем сохранение: " + name);
                return true;
            }
        }
        return false;
    }

    public void deleteSave(String name) {
        saves.removeIf(save -> save.getName().equals(name));
    }
}
