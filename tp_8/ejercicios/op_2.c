#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
    Arme un programa que permita cambiar los permisos de acceso sobre un archivo, para
    ello debe pasar al programa el nombre del archivo y los permisos que quiere tenga el mismo
    (Tome en cuenta las constantes de la Tabla 15-4 del libro de Kerrisk).
*/

int main(int argc, char *argv[]){

    if(argc < 3){
        printf("No se han ingresado suficientes argumentos");
        exit(1);
    }

    char *nombreArchivo = argv[1];

    for (int i = 2; i < argc; i++){
        
        const char *permisos = argv[i];
    

        mode_t modo = strtol(permisos, NULL, 8);


        if (chmod(nombreArchivo, modo) == -1){
            perror("Error al cambiar los permisos");
            exit(1);
        }
    }
}