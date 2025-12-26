import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class TemplateSchitatel<T extends Number> implements AbstractSchitatel {
    private String tipSchetchika;
    private T currentValue;
    private Map<String, T> history;
    
    public TemplateSchitatel(String tip, T startValue) {
        this.tipSchetchika = tip;
        this.currentValue = startValue;
        this.history = new HashMap<>();
    }
    
    @Override
    public void sbrosit() {
        history.put("reset", currentValue);

        if (currentValue instanceof Integer) {
            currentValue = (T) Integer.valueOf(0);
        } else if (currentValue instanceof Double) {
            currentValue = (T) Double.valueOf(0.0);
        } else if (currentValue instanceof Float) {
            currentValue = (T) Float.valueOf(0.0f);
        } else if (currentValue instanceof Long) {
            currentValue = (T) Long.valueOf(0L);
        } else {

            try {
                currentValue = (T) currentValue.getClass().getDeclaredConstructor(String.class).newInstance("0");
            } catch (Exception e) {

            }
        }
    }
    
    @Override
    public void pokazatTekushee() {
        System.out.println("Текущее значение: " + currentValue);
    }
    
    @Override
    public String getTipSchetchika() { return tipSchetchika; }
    
    public void increment(T value) {

        if (currentValue instanceof Integer && value instanceof Integer) {
            Integer newValue = currentValue.intValue() + value.intValue();
            currentValue = (T) newValue;
        } else if (currentValue instanceof Double && value instanceof Double) {
            Double newValue = currentValue.doubleValue() + value.doubleValue();
            currentValue = (T) newValue;
        } else if (currentValue instanceof Float && value instanceof Float) {
            Float newValue = currentValue.floatValue() + value.floatValue();
            currentValue = (T) newValue;
        } else if (currentValue instanceof Long && value instanceof Long) {
            Long newValue = currentValue.longValue() + value.longValue();
            currentValue = (T) newValue;
        } else {

            Double newValue = currentValue.doubleValue() + value.doubleValue();

            if (currentValue instanceof Integer) {
                currentValue = (T) Integer.valueOf(newValue.intValue());
            } else if (currentValue instanceof Double) {
                currentValue = (T) newValue;
            } else if (currentValue instanceof Float) {
                currentValue = (T) Float.valueOf(newValue.floatValue());
            } else if (currentValue instanceof Long) {
                currentValue = (T) Long.valueOf(newValue.longValue());
            }
        }
        history.put("increment", value);
    }
    
    public T getCurrentValue() { return currentValue; }
    
    public Map<String, T> getHistory() { return history; }
    
    public boolean containsKey(String key) {
        return history.containsKey(key);
    }
}