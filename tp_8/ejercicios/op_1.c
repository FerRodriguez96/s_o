#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

/*
    Arme un programa que permita cambiar el propietario de un archivo, para ello debe pasar
    al programa el nombre del archivo, el nombre del nuevo propietario y el nombre del nuevo grupo.
*/

int main(int argc, char *argv[]){

    if(argc != 4){
        printf("No se han ingresado suficientes argumentos");
    }

    char *nombre_archivo = argv[1];
    int nuevo_prop = atoi(argv[2]);
    int nuevo_group = atoi(argv[3]);

    if (chown(nombre_archivo, nuevo_prop, nuevo_group) == -1){
        perror("Error al cambiar el propietario y el grupo");
    }

    return 0;
}