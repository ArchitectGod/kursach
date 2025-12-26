import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

class TemplateElektropribor<T> implements AbstractElektropribor {
    protected String tipUstroystva;
    protected boolean vklyuchen;
    private LinkedList<T> soundQueue;
    
    public TemplateElektropribor(String tip) {
        this.tipUstroystva = tip;
        this.vklyuchen = false;
        this.soundQueue = new LinkedList<>();
    }
    
    @Override
    public void vkluchit() {
        vklyuchen = true;
        soundQueue.clear();
	}
    
    @Override
    public void izdatZvuk(String zvuk) {
        System.out.println("[" + tipUstroystva + "] " + zvuk);
    }
    
    @Override
    public String getTipUstroystva() { return tipUstroystva; }
    
    public void queueSound(T sound) {
        soundQueue.add(sound);
    }
    
    public void playAllSounds() {
        for (T sound : soundQueue) {
            izdatZvuk(sound.toString());
        }
        soundQueue.clear();
    }
    
    public LinkedList<T> getSoundQueue() { return soundQueue; }
    
    public boolean isSoundQueueEmpty() {
        return soundQueue.isEmpty();
    }
}