#include <stdio.h>
#include <stdlib.h>

/*
    Usando la función malloc(), escriba un programa que reciba como argumento n números
    enteros (./mi_programa a1 a2 … an), los cuales deben ser almacenados en un arreglo C.
    Redimensione C (use realloc()) para almacenar otros m (lo ingresa el usuario) números
    enteros (la nueva longitud de C tiene que ser n+m).
    Consideraciones:
        ● Si no se pasan números debe imprimir un error y terminar.
        ● m tiene que ser mayor que 0, si no se debe mostrar un mensaje de error y terminar.
        ● Libere la memoria asignada a C.
*/

int main (int argc, char* argv[]){

    //verifica que se ingresen 1 o mas arreglos
    if (argc < 2){
        printf("Uso del programa: %s num1 num2 ... numN", argv[0]);
        exit(1);
    }

    // se define el tamaño del arreglo como argc - 1, siendo -1 el nombre del programa
    size_t tamano = (argc - 1) * sizeof(int);

    // se le asigna al arreglo el tamaño en bytes
    int *arreglo = malloc(tamano);

    //se verifica que se ha podido asignar la memoria
    if (arreglo == NULL){
        perror("Asignacion de memoria fallida\n");
    }
    else
    {
        printf("Asignacion de memoria exitosa\n");

        //recorre el arreglo para imprimir sus valores
        for(int i = 0; i < argc - 1; i++){

            arreglo[i] = atoi(argv[i + 1]);

            printf("El arreglo en la posicion %d contiene: %d \n",i , arreglo[i]);
        }

        int m;

        //pide al usuario que indique la cantidad de valores nuevos que va a ingresar al arreglo
        printf("Ingrese la cantidad de numeros que se van a ingresar\n");
        scanf("%d", &m);

        //se define una variable que suma la cantidad de valores hasta ahora mas la cantidad de valores a ingresar
        int nuevo_tamano = (argc - 1) + m; 

        //se le reasigna mas memoria al arreglo, pasando el arreglo y el tamaño nuevo
        arreglo = realloc(arreglo, (nuevo_tamano) * sizeof(int));

        //verifica si se pudo asignar el nuevo tamaño de memoria
        if (arreglo == NULL)
        {
            printf("No se ha podido asignar mas memoria");
            free(arreglo);
            exit(1);
        }
        else
        {
            // El usuario ingresa los nuevos valores
            printf("Ingrese %d numeros nuevos al arreglo:\n", m);
            for(int i = argc - 1; i < nuevo_tamano; i++){
                scanf("%d", &arreglo[i]);
            }

            // se imprime el arreglo con los nuevos valores
            for(int i= 0; i < nuevo_tamano; i++){
                printf("El arreglo en la posicion %d contiene: %d \n",i , arreglo[i]);
            }
        }
        
        free(arreglo);
    }

    return 0;

}