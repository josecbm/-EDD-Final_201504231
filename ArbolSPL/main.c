#include <stdio.h>
#include <stdlib.h>
#include "arbolspl.h"
int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    int opcion=0;
    int id =0;

     Arbol* ArbolInt = NULL;
   do{

        printf("1. Graficar \n");
        printf("2. Modificar \n");
        printf("3. Agregar \n");
        printf("4. Eliminar \n");
        printf("5. buscar \n");
        printf("6. salir \n ");
        scanf("%i" , &opcion);
        switch (opcion) {
        case 1:
               graficar(&ArbolInt);
            break;
        case 2:
            printf("Ingrese un valor a modificar\n");
            scanf("%i" , &id);
            Borrar(&ArbolInt ,id);
            printf("Ingrese un valor a sustitucion\n");
            scanf("%i" , &id);
            Insertar(&ArbolInt ,id);
            break;
        case 3:
                printf("Ingrese un valor\n");
                scanf("%i" , &id);
                Insertar(&ArbolInt , id);
            break;
        case 4:
            printf("Ingrese un valor\n");
            scanf("%i" , &id);
              Borrar(&ArbolInt , id);
            break;
        case 5:
            printf("Ingrese un valor\n");
            scanf("%i" , &id);
            printf("%i\n",Buscar(&ArbolInt,id));
            break;

        default:
            break;
        }


   }while(opcion!=6);

}
