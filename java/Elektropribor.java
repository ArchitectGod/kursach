import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class Elektropribor implements AbstractElektropribor {
    protected String tipUstroystva;
    protected boolean vklyuchen;
    
    public Elektropribor(String tip) {
        this.tipUstroystva = tip;
        this.vklyuchen = false;
    }
    
    public Elektropribor() {
        this("Устройство");
    }
    
    @Override
    public void vkluchit() {
        vklyuchen = true;
    }
    
    @Override
    public void izdatZvuk(String zvuk) {
        if (vklyuchen) {
            System.out.printf("[%s] %s%n", tipUstroystva, zvuk);
        }
    }
    
    @Override
    public String getTipUstroystva() { return tipUstroystva; }
    
    public boolean getVklyuchen() { return vklyuchen; }
}
