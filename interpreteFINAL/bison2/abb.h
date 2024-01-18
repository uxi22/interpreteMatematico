#ifndef ABB_H
#define ABB_H

#include "definiciones.h"

#define L 20
/**
 * Tipo de dato abstracto para arbol binario con clave de
 * ordenacion y elemento de celda.
 */

///////////////////////////////////////INICIO PARTE MODIFICABLE
typedef char *tipoclave;

typedef componente_lex tipoelem;

//////////////////////////////////////////FIN PARTE MODIFICABLE
		
typedef struct celda * abb;//tipo opaco

/////////////////////////////// FUNCIONES

//FUNCIONES DE CREACIÓN Y DESTRUCCIÓN DEL ÁRBOL
/**
 * Crea el arbol vacio.
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void crear(abb *A);

/**
 * Destruye el arbol recursivamente
 * @param A El arbol que queremos destruir
 */
void destruir_arbol(abb *A);

//FUNCIONES DE INFORMACIÓN
/**
 * Comprueba si el arbol esta vacio
 * @param A El arbol binario
 */
unsigned es_vacio(abb A);

/**
 * Devuelve el subarbol izquierdo de A
 * @param A - Arbol original
 */
abb izq(abb A);
/**
 * Devuelve el subarbol derecho de A
 * @param A - Arbol original
 */
abb der(abb A);
/**
 * Recupera la informacion de la celda de la raiz del arbol
 * @param A
 * @param E Puntero al nodo que apuntara a la informacion
 */
void leer(abb A, tipoelem *E);


/**
 * Busca un nodo con clave <cl> en el arbol y, si existe
 * modifica el puntero <nodo> para que lo apunte.
 * Si no existe, se añade un nuevo nodo con la clave <cl>
 * @param A Arbol binario en el que se busca el nodo.
 * @param cl Clave que se buscara.
 * @param nodo Puntero a un tipoelem.
 */


short buscar_nodo(abb *A, tipoclave cl, tipoelem *nodo);

short buscar_modif_nodo(abb *A, tipoclave cl, double valor);

short buscar_ejecutar_nodo(abb *A, tipoclave cl, double param, double *resultado);

void insertar_nodo(abb *A, tipoelem E);

void imprimir_arbol(abb *A);

void imprimir_variables(abb *A);

void borrar_variables(abb *A);

#endif	// ABB_H

