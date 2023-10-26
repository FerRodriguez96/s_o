#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    pid_t id;
    int estado;

        if (argc < 2){
            printf("No se han recibido suficientes argumentos\n");
        } else if (argc >= 2){

            for (int i = 1; i < argc; i++){
                id = fork();
                if(id != -1){
                    if (id == 0){
                        
                        pid_t pgid_hijo = getpgid(id);
                        pid_t ppid_hijo = getppid();
                        printf("PID hijo: %d\n", getpid());
                        printf("PPID hijo: %d\n", ppid_hijo);
                        printf("PGID hijo: %d\n", pgid_hijo);
                        printf("Nombre del archivo: %s\n", argv[i]);

                        execlp("wc","wc","-l", argv[i],NULL);

                        return(0);
                    }
                    else{
                        wait(&estado);
                        if (WIFEXITED(estado)) printf("Hijo termino normalmente\n");
                        if (WIFSIGNALED(estado)) printf("Hijo termino a causa de una señal\n");
                    }
            }else{
                printf("Error al crear el proceso hijo\n");
                return 1;
            }
        }
    
    }
}