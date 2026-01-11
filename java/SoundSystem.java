import java.io.*;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

class SoundSystem {
    private boolean enabled;
    private Thread soundThread;
    private Clip currentClip;

    public SoundSystem() {
        this.enabled = true;
    }

    public void playClickSound() {
        if (enabled) {
            System.out.print("\u0007"); 
        }
    }

    public void playExplosionSound() {
        if (enabled) {
            playsound("explode");
        }
    }

    public void playWinSound() {
        if (enabled) {
           playsound("Win");
        }
    }

    public void setEnabled(boolean enable) { enabled = enable; }
    public boolean isEnabled() { return enabled; }


    private void playsound(String filename){
        
        soundThread = new Thread(() -> {
            try {
            File soundFile = new File(filename + ".wav"); 
            AudioInputStream ais = AudioSystem.getAudioInputStream(soundFile);
            Clip clip = AudioSystem.getClip();
            clip.open(ais);
            clip.setFramePosition(0); 
            clip.start(); 
            Thread.sleep(10000);
            clip.stop(); 
            clip.close(); 
            } catch (IOException | UnsupportedAudioFileException | LineUnavailableException exc) {
                exc.printStackTrace();
            } catch (InterruptedException exc) {}
        });
        soundThread.start();
    }
}
