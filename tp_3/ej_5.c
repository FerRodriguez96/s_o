#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void manejador (int sig){
    printf("Se ha capturado la señal SIGUSR1!");
}

int main (int argc, char* argv[]){
    // definicion de variables globales
    pid_t id;

    if (argc < 3){
        printf("No se han pasado suficientes argumentos");
    } else {
        id = fork();
        
    }

    if (signal(SIGUSR1, manejador)== SIG_ERR)
        exit(EXIT_FAILURE);
}