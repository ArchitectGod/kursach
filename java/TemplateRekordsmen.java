import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class TemplateRekordsmen<T1, T2> implements AbstractRekordsmen {
    private String kategoriyaSorevnovaniya;
    private int godUstanovkiRekorda;
    private Object recordData;
    private List<AbstractRekordsmen> competitors;
    
    public TemplateRekordsmen(String kategoriya, int god) {
        this.kategoriyaSorevnovaniya = kategoriya;
        this.godUstanovkiRekorda = god;
        this.competitors = new ArrayList<>();
    }
    
    @Override
    public void zaregistrirovatPobedu() {
        System.out.println("Победа зарегистрирована в категории: " + kategoriyaSorevnovaniya);
    }
    
    @Override
    public void pokazatRezultat() {
        System.out.println("Рекорд: " + kategoriyaSorevnovaniya);
    }
    
    @Override
    public String getKategoriyaSorevnovaniya() { return kategoriyaSorevnovaniya; }
    
    @Override
    public int getGodUstanovkiRekorda() { return godUstanovkiRekorda; }
    
    public void setRecordData(Object data) {
        this.recordData = data;
    }
    
    public Object getRecordData() { return recordData; }
    
    public void addCompetitor(AbstractRekordsmen competitor) {
        competitors.add(competitor);
    }
    
    public List<AbstractRekordsmen> getCompetitors() { return competitors; }
    
    public void sortCompetitorsByYear() {
        Collections.sort(competitors, (a, b) -> 
            Integer.compare(a.getGodUstanovkiRekorda(), b.getGodUstanovkiRekorda()));
    }
}