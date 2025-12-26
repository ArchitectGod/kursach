import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class TemplateGeografiya<T> implements AbstractGeografiya {
    private String nazvanieRegiona;
    private int urovenOpasnosti;
    private T dopolnitelnyParam;
    private List<AbstractGeografiya> regions;
    
    public TemplateGeografiya(String region, int danger, T param) {
        this.nazvanieRegiona = region;
        this.urovenOpasnosti = danger;
        this.dopolnitelnyParam = param;
        this.regions = new ArrayList<>();
    }
    
    public void addRegion(AbstractGeografiya region) {
        regions.add(region);
    }
    
    @Override
    public void issledovatTerritoriyu() {
        for (AbstractGeografiya region : regions) {
            region.issledovatTerritoriyu();
        }
    }
    
    @Override
    public void pokazatInfo() {
        System.out.printf("Шаблонный регион: %s, Опасность: %d, Параметр: %s%n", 
                         nazvanieRegiona, urovenOpasnosti, dopolnitelnyParam);
    }
    
    @Override
    public String getNazvanieRegiona() { return nazvanieRegiona; }
    
    @Override
    public int getUrovenOpasnosti() { return urovenOpasnosti; }
	@Override
    public void izmenitOpasnost(int novayaOpasnost) {
        if (novayaOpasnost >= 0 && novayaOpasnost <= 10) {
            this.urovenOpasnosti = novayaOpasnost;
        }
    }
    
    public T getParam() { return dopolnitelnyParam; }
    public void setParam(T param) { this.dopolnitelnyParam = param; }
    
    public List<AbstractGeografiya> getRegions() { return regions; }
    
    public void sortRegionsByDanger() {
        Collections.sort(regions, (a, b) -> 
            Integer.compare(a.getUrovenOpasnosti(), b.getUrovenOpasnosti()));
    }
}
