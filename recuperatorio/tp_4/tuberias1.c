#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("Error al crear la tubería");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error al crear el proceso hijo");
        exit(1);
    }

    if (pid == 0) { // Proceso hijo
        close(pipe_fd[0]); // Cierra el descriptor de lectura

        // Utiliza pipe_fd[1] para escribir en la tubería
        char mensaje[] = "Hola desde el hijo";
        write(pipe_fd[1], mensaje, sizeof(mensaje));

        close(pipe_fd[1]); // Cierra el descriptor de escritura
    } else { // Proceso padre
        close(pipe_fd[1]); // Cierra el descriptor de escritura

        // Utiliza pipe_fd[0] para leer desde la tubería
        char buffer[100];
        read(pipe_fd[0], buffer, sizeof(buffer));

        printf("Mensaje recibido en el padre: %s\n", buffer);

        close(pipe_fd[0]); // Cierra el descriptor de lectura
    }

    return 0;
}