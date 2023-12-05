#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>

/*
    Debe implementar un programa que reciba una cantidad variable de
    argumentos donde el proceso padre debe:
        ● ignorar SIGTERM y SIGINT.
        ● imprimir su PID, PPID.
        ● crear un proceso hijo para que ejecute el programa definido por los argumentos
          recibidos enviando el resultado de su ejecución por una tubería sin nombre.
        ● crear otro proceso hijo que ejecute sort -u tomando como su entrada estándar la
        tubería sin nombre.
        ● Imprimir como van finalizando sus hijos usando las macros (Indicar forma de
        finalización y valor de señal o de retorno según corresponda).

        Ejemplo de ejecución: miprograma ls -l

        Donde el primer hijo ejecuta ls -l y el segundo hijo sort -u ambos comunicados por una
        tubería sin nombre.
*/

void manejador(int sig)
{

    if (SIGINT == sig || SIGTERM == sig)
    {
        printf("Ignorando señal %d, retornando al programa...\n", sig);
        return;
    }
}

int main(int argc, char *argv[])
{

    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        printf("Error al crear la tuberia");
        exit(1);
    }

    pid_t id_hijo1;
    pid_t id_hijo2;
    int estado;
    
    if (signal(SIGINT, manejador) == SIG_IGN)
    {
        printf("Señal SIGINT capturada!");
    }

    if (signal(SIGTERM, manejador) == SIG_IGN)
    {
        printf("Señal SIGTERM capturada!");
    }

    printf("El PID del padre es: %d\n", getpid());
    printf("El PPID del padre es: %d\n", getppid());
    
    char *argumento[argc - 1];
    for (int i = 1; i < argc; i++) {
        argumento[i - 1] = argv[i];
    }
    argumento[argc -1] = NULL;


    id_hijo1 = fork();
    id_hijo2 = fork();

    if (id_hijo1 == 0)
    {
        close(pipe_fd[0]);

        dup2(pipe_fd[1], STDOUT_FILENO);

        close(pipe_fd[1]);

        execvp(argumento[0], argumento);
        printf("Error al ejecutar el argumento ingresado\n");
        exit(1);
    }

    if (id_hijo2 == 0)
    {
        close(pipe_fd[1]);

        dup2(pipe_fd[0], STDIN_FILENO);

        close(pipe_fd[0]);

        execlp("sort", "sort", "-u", NULL);
        printf("Error al ejecutar el comando sort\n");
        exit(1);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    pid_t pid1 = waitpid(id_hijo1, &estado, 0);

    if (pid1 == id_hijo1) {
        // El proceso hijo especificado ha terminado
        if (WIFEXITED(estado)) {
            printf("Hijo 1 terminó normalmente con código de salida %d\n", WEXITSTATUS(estado));
        }

        if (WIFSIGNALED(estado)) {
            printf("Hijo 1 terminó debido a una señal\n");
        }
    }

    pid_t pid2 = waitpid(id_hijo2, &estado, 0);

    if (pid2 == id_hijo2) {
        // El proceso hijo especificado ha terminado
        if (WIFEXITED(estado)) {
            printf("Hijo 2 terminó normalmente con código de salida %d\n", WEXITSTATUS(estado));
        }

        if (WIFSIGNALED(estado)) {
            printf("Hijo 2 terminó debido a una señal\n");
        }
    }

    return 0;
}