import java.util.*;
import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.lang.reflect.*;

interface AbstractElektropribor {
    void vkluchit();
    void izdatZvuk(String zvuk);
    String getTipUstroystva();
}