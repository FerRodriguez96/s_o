// librerias a incluir
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// libreria para manejar lectura de directorios
#include <dirent.h>
// libreria para obtener informacion de directorios
#include <sys/stat.h>

/*Desarrolle un programa que reciba como máximo 2 parámetros, un valor
numérico y opcionalmente un nombre de directorio. El programa debe cambiar al directorio
especificado como parámetro (siempre que se especifique dicho valor) y realizar lo
siguiente:
    ● Imprimir el directorio de trabajo.
    ● Imprimir los archivos regulares que tengan un numero de hard-links mayor o igual al
    valor numérico especificado.
    ● Verificar si un directorio (no considerar “.” y “..”) puede ser eliminado (implemente
    una función para esto). (*)
    ● Eliminar todos los enlaces simbólicos.
    ● Sumar la cantidad de bytes de los archivos FIFO, imprimiendo el resultado al final.
(*) La función a implementar debe tener el siguiente formato de cabecera rmdir_control(char
* nombre), y debe retornar -1 en caso de que no se pueda eliminar el directorio y 1 en caso
que si pueda eliminarse.
*/

//funcion para imprimir contenido del directorio
void imprimir_contenido(char *ruta, int numero)
{
    //declaraciones de estructuras de directorio
    DIR * dirp;
    struct dirent * direntp;
    struct stat atributos;

    //apertura del directorio
    dirp = opendir(ruta);

    //comprobacion de apertura
    if (dirp == NULL){
        perror("Error al abrir el directorio");
        exit(1);
    }

    //imprimir directorio actual
    printf("Directorio actual: %s\n", ruta);

    //leer directorio
    while ((direntp = readdir(dirp)) != NULL){

        //definicion de file_path
        char file_path[1024];

        //obtener atributos
        if(stat(file_path, &atributos) == 0)
        {
            //imprimir archivos con un numero mayor de hardlinks comparado al numero ingresado
            if ((atributos.st_nlink) >= numero && S_ISREG(atributos.st_mode))
            {
                printf("Archivo regular con un numero de hardlinks mayor al numero ingresado: %s\n", direntp->d_name);
            }

            //eliminar enlaces simbolicos
            if (S_ISLNK(atributos.st_mode)) 
            {
                if (unlink(ruta) == -1) 
                {
                    perror("Error al eliminar el enlace simbólico");
                    exit(1);
                }
            }
        }

    }

    return 0;
}

int main (int argc, char *argv[])
{
    // verificacion de cantidad de parametros ingresados
    if (argc <= 1 || argc > 3)
    {
        perror("Error en la cantidad de argumentos ingresados");
        exit(1);
    }

    // conversion del parametro a int
    int numero = atoi(argv[1]);

    /*
        Si el numero de parametros pasado es mayor a 2,
        entonces directorio toma el valor de argv[2].
        Si no, toma el valor del directorio actual.
    */ 
    char *directorio = (argc >= 2) ? argv[2] : ".";

    // Si se proporciona un directorio, cambia ahi:
    if (chdir(directorio) != 0)
    {
        perror("Error al cambiar de directorio");
        exit(1);
    }

    //llamado de funcion para imprimir contenido
    imprimir_contenido(".", numero);

    //llamado de funcion para verificar si se puede eliminar el directorio

}