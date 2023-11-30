// librerias a incluir
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// libreria para manejar lectura de directorios
#include <dirent.h>
// libreria para obtener informacion de directorios
#include <sys/stat.h>
// libreria para tener constantes de limites de sistema
#include <linux/limits.h>

/*
    Desarrolle un programa que reciba como máximo 2 parámetros, un valor numérico y opcionalmente
    un nombre de directorio. El programa debe cambiar al directorio
    especificado como parámetro (siempre que se especifique dicho valor) y realizar lo siguiente:
        ● Imprimir el directorio de trabajo.
        ● Eliminar los archivos regulares del directorio que tengan un tamaño mayor o igual al
        valor numérico especificado, se debe exceptuar al ejecutable del programa y
        archivos usados por el programa.
        ● El nombre de cada archivo eliminado se debe almacenar en un archivo control.txt .
        ● Sumar la cantidad de bytes de los archivos eliminados, imprimiendo el resultado al
        final para indicar la cantidad de espacio liberado (no se preocupe por hardlinks a un
        mismo archivo).
        ● Contar la cantidad de archivos que no sean regulares o directorios del directorio que
        está recorriendo, imprimiendo el resultado al final.

    Consideraciones:
        ● No puede usar system() o alguna función de la familia exec().
        ● Si se recibe una cantidad de parámetros no especificada por los requerimientos el
        programa debe mostrar un mensaje de error y terminar.
*/

void eliminar_contenido(int numero, char* ruta, char*ejecutable){

    //declaracion de esctructuras
    DIR * dirp;
    struct dirent * direntp;
    struct stat atributos;

    // declaracion de variables
    long long cant_reg = 0;
    int cant_otros = 0;

    // apertura de directorio
    dirp = opendir(".");

    //comprobacion de apertura correcta
    if (dirp == NULL){
        perror("Error al abrir el directorio");
        exit(1);
    }

    while ((direntp = readdir(dirp)) != NULL)
    {
        if ((stat(direntp->d_name, &atributos) == 0))
        {
            if((S_ISREG(atributos.st_mode) != 0) && atributos.st_size >= numero)
            {
                if (direntp->d_name != ejecutable)
                {
                    if (unlink(direntp->d_name) == -1){
                        perror("Error al eliminar el archivo regular");
                    }
                    else
                    {
                        printf("Se ha eliminado el archivo regular: %s\n", direntp->d_name);
                    }
                }
            }
        }
    }

    closedir(dirp);
}

int main(int argc, char* argv[]){

    //comprobacion de cantidad de argumentos
    if (argc < 2){
        perror("No se han ingresado la cantidad correcta de argumentos");
        exit(1);
    }

    char* ejecutable = argv[0];

    // asignacion del numero ingresado por parametro
    int numero = atoi(argv[1]);

    // declaracion del buffer
    char buf[PATH_MAX];

    //se obtiene el directorio actual
    if (getcwd(buf, PATH_MAX) == NULL){
        perror("No se ha podido obtener el directorio actual");
        exit(1);
    }else
    {
        printf("Directorio actual: %s\n", buf);
    }

    printf("Cambiando de directorio...\n");

    //se verifica que se haya ingresado un directorio por argumentros
    if (argc > 2){
        // se realiza el cambio de directorio
        if (chdir(argv[2]) == -1){
            perror("No se ha podido cambiar al directorio ingresado");
            exit(1);
        }

        printf("Directorio actual: %s\n", argv[2]);
    }

    //llamado a funcion
    eliminar_contenido(numero, buf, ejecutable);
    
    return(0);
}