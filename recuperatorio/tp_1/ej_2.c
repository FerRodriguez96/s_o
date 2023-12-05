#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
    Desarrolle un programa que reciba como parámetros:
        ● Un programa a ejecutar y
        ● Un valor numérico.
    El programa debe verificar que el valor numérico sea mayor que cero, de no cumplirse esta
    condición debe finalizar su ejecución. Luego debe ejecutar 10 iteraciones que cumplan lo
    siguiente:
        ● Ejecutar el programa pasado como primer parámetro.
        ● Dormir el tiempo especificado como segundo parámetro.
*/

int main(int argc, char *argv[]){

    if (argc < 3){
        perror("No se han ingresado suficientes argumentos");
        exit(1);
    }else if (atoi(argv[2]) <= 0){
        perror("El numero ingresado debe ser mayor a 0");
        exit(1);
    }

    char *programa = argv[1];
    int numero = atoi(argv[2]);

    pid_t pid;

    for (int i = 0; i < 9; i++){

        pid = fork();

        if(pid == 0){
            execl(programa, programa, NULL);
            exit(1);
        }else{
            sleep(numero);
            printf("Durmiendo... %d segundos\n", numero);
        }
    }

    for (int i = 0; i < 9; i++) {
        wait(NULL);
    }

    return 0;
    
}