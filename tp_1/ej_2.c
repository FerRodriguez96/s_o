#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){

    // nombramiento de variables
    pid_t id;
    int estado;

    //pregunta si se ingresaron la suficiente cantidad de parametros
    if (argc < 3){
        printf("No se han ingresado el numero correcto de parametros\n");
        return 0;
    // si se ingresaron la cantidad correcta de parametros, continua la ejecucion
    }else if (argc >= 2){
        
        // asignacion de las variables a las posiciones del vector de argumentos
        char*programa = argv[1];
        int valor = atoi(argv[2]);

        // pregunta si el valor ingresado como tiempo de espera es menor o igual a 0
        if (valor <= 0){
            printf("El valor ingresado debe ser mayor a 0\n");
            return 0;
        }
        // bucle para ejecutar 10 iteraciones del programa pasado por parametro
        for (int i = 0; i < 10; i++){
            
            // creacion de proceso hijo
            id = fork();

            // si el pid es menor a 0, termina el programa
            if (id < 0){
                printf("Error al crear el proceso hijo\n");
                return 0;
            }else if (id == 0){
                //ejecucion del proceso hijo
                execlp(programa, programa, NULL);
                return 0;
            }else{
                //ejecucion del proceso padre

                //espera al estado del hijo
                waitpid(id, &estado,0);

                //espera la cantidad especificada en el parametro para ejecutar el siguiente hijo
                for (int j= 0; j < valor; j++){ 
                    printf("Esperando 1 segundo\n");
                    sleep(1);
                }

                //verifica la forma en la cual termino el hijo
                if (WIFEXITED(estado)) printf("Hijo termino normalmente\n");
            }
        }
    }
}