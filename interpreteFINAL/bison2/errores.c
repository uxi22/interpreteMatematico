#include <stdio.h>

#include "definiciones.h"

void gestion_error(int tipo){
    switch (tipo)
    {
    case ERROR1:
        printf("<<ERROR LÉXICO: Carácter no válido>>\n");
        break;
    case ERROR2:
        printf("<<ERROR SINTÁCTICO: División entre cero>>\n");
        break;
    case ERROR3:
        printf("<<ERROR SINTÁCTICO: Variable no inicializada>>\n");
        break;
    case ERROR4:
        printf("<<ERROR SINTÁCTICO: No se puede modificar una constante>>\n");
        break;
    case ERROR5:
        printf("<<ERROR: No se puede leer el fichero>>\n");
        break;
    case ERROR6:
        printf("<<ERROR: Demasiados argumentos>>\nUso: ./interprete [fichero]\n");
        break;
    case ERROR7:
        printf("<<ERROR: Función no reconocida>>\n");
        break;
    case ERROR8:
        printf("<<ERROR: Nodo ya existente en la tabla de símbolos>>\n");
        break;
    case ERROR9:
        printf("<<ERROR SINTÁCTICO: Palabra reservada para una función>>\n");
        break;
    case ERROR10:
        printf("<<ERROR SINTÁCTICO: Sintaxis no válida>>\n");
        break;
    default:
        break;
    }
}

