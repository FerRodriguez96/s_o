#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void ejecutar_comando(const char *archivo, int valor) {
    int filedes[2];
    pid_t id;

    // Inicializar la tubería
    if (pipe(filedes) == -1) {
        perror("Error al crear la tubería");
        exit(1);
    }

    id = fork();
    
    if (id == 0) {
        // ejecucion de proceso hijo
        // cerrar lectura
        close(filedes[0]);

        // ligar al extremo de escritura de la tuberia
        dup2(filedes[1], STDOUT_FILENO);

        // Cerrar escritura
        close(filedes[1]);

        // Ejecutar el comando cat nombre_archivo
        execlp("cat", "cat", archivo, NULL);
        perror("Error al ejecutar el comando cat");
        exit(1);
    } else { 
        // ejecucion de proceso padre
        // cerrar escritura
        close(filedes[1]);

        // ligar al extremo de lectura de la tuberia
        dup2(filedes[0], STDIN_FILENO);

        // Convertir el valor a una cadena
        char valor_str[10];
        snprintf(valor_str, sizeof(valor_str), "%d", valor);

        // Ejecutar el comando head -n valor
        execlp("head", "head", "-n", valor_str, (char *)NULL);
        perror("Error al ejecutar el comando head");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    //pregunta si se ingresaron la suficiente cantidad de parametros
    if (argc < 3) {
        fprintf(stderr, "Uso: %s valor archivo1 archivo2 ...\n", argv[0]);
        exit(1);
    }

    // Obtener el valor como entero
    int valor = atoi(argv[1]);

    // Validar que el valor sea positivo
    if (valor <= 0) {
        fprintf(stderr, "El valor debe ser un número positivo.\n");
        exit(1);
    }

    // Iterar sobre los nombres de archivo y ejecutar el comando para cada uno
    for (int i = 2; i < argc; i++) {
        ejecutar_comando(argv[i], valor);
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 2; i < argc; i++) {
        wait(NULL);
    }

    return 0;
}
