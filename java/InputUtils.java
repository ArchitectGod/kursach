import java.util.Scanner;

public class InputUtils {
    
    public static void clearInputBuffer(Scanner scanner) {
        if (scanner.hasNextLine()) {
            scanner.nextLine();
        }
    }
    

    public static int safeInputInt(Scanner scanner, String prompt) {
        int value = 0;
        boolean validInput = false;
        
        while (!validInput) {
            try {
                System.out.print(prompt);
                value = scanner.nextInt();
                validInput = true;
            } catch (Exception e) {
                System.out.println("Ошибка! Пожалуйста, введите целое число.");
                scanner.nextLine();
            }
        }
        clearInputBuffer(scanner); 
        return value;
    }
    

    public static void safeInputTwoInts(Scanner scanner, int[] coords, String prompt) {
        boolean validInput = false;
        
        while (!validInput) {
            try {
                System.out.print(prompt);
                coords[0] = scanner.nextInt();
                coords[1] = scanner.nextInt();
                validInput = true;
            } catch (Exception e) {
                System.out.println("Ошибка! Пожалуйста, введите два числа через пробел (например: 2 3).");
                scanner.nextLine(); 
            }
        }
        clearInputBuffer(scanner); 
    }
    
    public static int[] getTwoInts(Scanner scanner, String prompt) {
        int[] coords = new int[2];
        safeInputTwoInts(scanner, coords, prompt);
        return coords;
    }
}