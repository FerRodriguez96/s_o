// librerias a incluir
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// libreria para manejar lectura de directorios
#include <dirent.h>
// libreria para obtener informacion de directorios
#include <sys/stat.h>

/*Escriba un programa que recibe un parámetro obligatorio y dos
parámetros opcionales. El parámetro obligatorio es una palabra y los opcionales son un
directorio y la letra “e”. Si se recibe el parámetro de directorio el proceso debe cambiar su
directorio de trabajo a dicho directorio y si no puede realizarse esto debe terminar. El
programa luego debe imprimir el directorio de trabajo actual y todos los ficheros o directorios
contenidos en el mismo (sin entrar en subdirectorios) que contengan la palabra pasada
como parámetro al programa. Aparte de lo indicado el programa debe imprimir la cantidad
de bytes ocupados por dichos ficheros o directorios agrupándolos en “Archivos Regulares”,
“Directorios” y “Otros Archivos” (no se preocupe si hay hard-links a un mismo archivo).
Si se especifica el tercer parámetro debe eliminar los archivos que no sean archivos
regulares o directorios que contengan la palabra pasada como parámetro al programa.
*/

void imprimir_contenido(char *ruta, char *palabra, int bandera_eliminacion)
{
    DIR *dirp;
    struct dirent *direntp;
    struct stat atributos;

    dirp = opendir(ruta);

    if (dirp == NULL)
    {
        perror("Error al abrir el directorio");
        exit(1);
    }

    printf("Directorio actual: %s\n", ruta);

    while ((direntp = readdir(dirp)) != NULL)
    {
        char file_path[1024];

        printf(file_path, sizeof(file_path), "%s/%s", ruta, direntp->d_name);

        if (stat(file_path, &atributos) == 0)
        {
            if (S_ISREG(atributos.st_mode))
            {
                printf("Archivo regular: %s\n", direntp->d_name);
            }
            else if (S_ISDIR(atributos.st_mode))
            {
                printf("Directorio: %s\n", direntp->d_name);
            }
            else
            {
                printf("Otro archivo:%s\n", direntp->d_name);
            }

            if (strstr(direntp->d_name, palabra) != NULL)
            {
                printf("Contiene la palabra: %s\n", direntp->d_name);

                if (bandera_eliminacion == 1 && (S_ISREG(atributos.st_mode) || S_ISDIR(atributos.st_mode)))
                {
                    remove(file_path);
                    printf("Archivo eliminado: %s\n", direntp->d_name);
                }
            }
        }
    }

    closedir(dirp);
}

int main(int argc, char *argv[])
{
    if (argc <= 2 || argc > 4)
    {
        printf("Error en la cantidad de argumentos ingresados");
        exit(1);
    }

    char *palabra = argv[1];
    /*primera idea?
    char * directorio = argv[2];
    */

    /*
     operador ternario
     Si el numero de argumentos pasado es mayor a 3
     (esto include a la letra e) entonces el valor de
     directorio sera argv[2], si no, directorio sera
     "." que es el valor del directorio actual
    */
    char *directorio = (argc >= 3) ? argv[2] : ".";

    // Si se proporciona un directorio, cambia ahi:
    if (chdir(directorio) != 0)
    {
        perror("Error al cambiar de directorio");
        exit(1);
    }

    /*
        En primer lugar, se verifica que se tienen 4 argumentos
        y en segundo, si el argumento 4 es igual a "e".
        Esta comparacion se logra mediante strcmp, que da
        "0" en caso de ser afirmativa la comparacion.

        En caso de que ambas condiciones se cumplan, la bandera
        de eliminar la palabra pasa de 0 a 1.
    */
    int bandera_eliminar = 0;
    if (argc == 4 && strcmp("e", argv[3]) == 0)
    {
        bandera_eliminar = 1;
    }

    // llamado de funcion
    imprimir_contenido(".", palabra, bandera_eliminar);

    return 0;
}