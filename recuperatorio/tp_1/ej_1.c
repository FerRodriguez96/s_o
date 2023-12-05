#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    Escriba un programa que reciba una cantidad variable de nombres de archivo desde la
    línea de comandos. Por cada nombre de archivo el programa debe crear un proceso hijo
    que:
        ● Imprima su PGID, PPID, PID y el nombre del archivo; y
        ● Use una de las funciones de la familia exec() para ejecutar: wc -l
        nombre_de_archivo.
        Consideraciones:
        ● Los procesos hijos se deben ejecutar concurrentemente.
        ● El proceso padre debe indicar que proceso hijo va finalizando e indicando de que
        manera finaliza (Normal o por una señal).
        ● Si no se pasa ningún nombre de archivo se debe mostrar un mensaje de error.
        ● No se puede utilizar la llamada al sistema system().
*/

int main (int argc, char *argv[]){

    if (argc < 1){
        perror("No se han ingresado nombres de archivo");
        exit(1);
    }

    int estado = 0;
    pid_t pid;

    for (int i = 1; i < argc; i++){

        pid = fork();

        if (pid == 0){

            printf("El PGID del proceso es: %d\n", getpgid(pid));
            printf("El PPID del proceso es: %d\n", getppid());
            printf("El PID del proceso es: %d\n", getpid());
            printf("El nombre del archivo es: %s\n", argv[i]);

            execlp ("wc","wc", "-l", argv[i], NULL);

            exit(1);

        }
    }

    for (int i = 1; i < argc; ++i) {
       wait(&estado);
            if (WIFEXITED(estado)){
                printf("Hijo termino normalmente\n");
            }

            if (WIFSIGNALED(estado)){
                printf("Hijo termino a causa de una señal\n");
            }
    }

    return 0;

}