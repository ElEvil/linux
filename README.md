#Linux Keylogger en C
#Descripción: Este programa es un keylogger desarrollado en C para sistemas Linux. Registra todas las teclas presionadas en el teclado y las guarda en un archivo de log. El keylogger es capaz de manejar teclas especiales y registra la entrada tal como la escribe el usuario.

## Instrucciones de Uso
### 1. Requisitos Previos
- Sistema operativo: Linux (con acceso a `/dev/input/`).
- Compilador: `gcc` o cualquier otro compilador de C compatible con Linux.
- Permisos de superusuario (sudo) para acceder a los dispositivos de entrada.

### 2. Compilación

Para compilar el programa, abre una terminal y ejecuta el siguiente comando:

bash   gcc -o keylogger keylogger.c
