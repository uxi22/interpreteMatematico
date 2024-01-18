#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"
#include "errores.h"

///////////////////////// ESTRUCTURAS DE DATOS

struct celda {
    tipoelem info;
    struct celda *izq, *der;
};

//////////////////////// FUNCIONES

/*Extraer la clave de una celda */
tipoclave _clave_elem(tipoelem *E) {
    return E->lexema; //se va a comparar por lexema
}


/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las 
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta. */
int _comparar_claves(tipoclave cl1, tipoclave cl2) {
    return strcmp(cl1,cl2)==0 ? 0 : strcmp(cl1,cl2)>0 ? 1 : -1;
    //devuelve 0 si son iguales, num pos si la primera es mayor, num neg si la segunda es mayor
}


/////////////////////////// FIN PARTE MODIFICABLE
/////////////////////////////////////////////////////////////

//OPERACIONES DE CREACIÓN Y DESTRUCCIÓN

void crear(abb *A) {
    *A = NULL;
}


void destruir_arbol(abb *A) {
    if (*A != NULL) {
        destruir_arbol(&(*A)->izq);
        destruir_arbol(&(*A)->der);
        free(*A);
        *A = NULL;
    }
}

//OPERACIONES DE INFORMACIÓN

unsigned es_vacio(abb A) {
    return A == NULL;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}

void leer(abb A, tipoelem *E) {
    *E = A->info;
}
// Función privada para comparar las claves

int _comparar_clave_elem(tipoclave cl, tipoelem E) {
    return _comparar_claves(cl, _clave_elem(&E));
}


short buscar_modif_nodo(abb *A, tipoclave cl, double valor) {
    if (es_vacio(*A)) {
        //no existe ese nodo en el arbol
        //se inserta con el valor especificado
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = cl;
        (*A)->info.tipo = VAR_NUM;
        (*A)->info.valor.numero = valor;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return 0;
    }
    int comp = _comparar_clave_elem(cl, (*A)->info);

    if (comp == 0) { // cl == A->info
        if ((*A)->info.tipo == CONSTANTE) {
            return CONSTANTE;
        } else if ((*A)->info.tipo == VAR_NUM) {
            (*A)->info.valor.numero = valor;
            return VAR_NUM;
        } else if ((*A)->info.tipo == FUNCION) {
            return FUNCION;
        }
    } else if (comp < 0) { // cl < A->info
        buscar_modif_nodo(&(*A)->izq, cl, valor);
    } else { // cl > A->info
        buscar_modif_nodo(&(*A)->der, cl, valor);
    }
}

short buscar_ejecutar_nodo(abb *A, tipoclave cl, double param, double *resultado) {
    if (es_vacio(*A)) {
        //no existe ese nodo en el arbol
        return -1;
    }
    int comp = _comparar_clave_elem(cl, (*A)->info);

    if (comp == 0) { // cl == A->info
        if ((*A)->info.tipo == CONSTANTE) {
            return CONSTANTE;
        } else if ((*A)->info.tipo == VAR_NUM) {
            return VAR_NUM;
        } else if ((*A)->info.tipo == FUNCION) {
            *resultado = (*A)->info.valor.funcion(param);
            return FUNCION;
        }
    } else if (comp < 0) { // cl < A->info
        buscar_ejecutar_nodo(&(*A)->izq, cl, param, resultado);
    } else { // cl > A->info
        buscar_ejecutar_nodo(&(*A)->der, cl, param, resultado);
    }
}

short buscar_nodo(abb *A, tipoclave cl, tipoelem *nodo){
    if (es_vacio(*A)) {
        //no existe ese nodo en el arbol
        return 0;
    }
    int comp = _comparar_clave_elem(cl, (*A)->info);

    if (comp == 0) { // cl == A->info
        *nodo = (*A)->info; //se devuelve el nodo encontrado
        return 1;
    } else if (comp < 0) { // cl < A->info
        buscar_nodo(&(*A)->izq, cl, nodo);
    } else { // cl > A->info
        buscar_nodo(&(*A)->der, cl, nodo);
    }
}

void insertar_nodo(abb *A, tipoelem E) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info = E;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    } else {
        int comp = _comparar_clave_elem(_clave_elem(&E), (*A)->info);
        if (comp == 0) { // cl == A->info
            //no se inserta
            gestion_error(ERROR8);
        } else if (comp < 0) { // cl < A->info
            insertar_nodo(&(*A)->izq, E);
        } else { // cl > A->info
            insertar_nodo(&(*A)->der, E);
        }
    }
}

void borrar_variables(abb *A){
    if (*A != NULL) {
        borrar_variables(&(*A)->izq);
        borrar_variables(&(*A)->der);
        if((*A)->info.tipo == VAR_NUM){
            free(*A);
            *A = NULL;
        }
    }
}


void imprimir_arbol(abb *A){
    if (*A != NULL) {
        imprimir_arbol(&(*A)->izq);
        imprimir_arbol(&(*A)->der);
        if (((*A)->info.tipo == CONSTANTE) || ((*A)->info.tipo == VAR_NUM)) {
            printf(" lex %s -> id %f\n", (*A)->info.lexema, (*A)->info.valor.numero);
        }
    }
}

void imprimir_variables(abb *A){
    if (*A != NULL) {
        imprimir_variables(&(*A)->izq);
        imprimir_variables(&(*A)->der);
        if((*A)->info.tipo == VAR_NUM){
            printf("\tlex %s id %f\n", (*A)->info.lexema, (*A)->info.valor.numero);
        }
    }
}
