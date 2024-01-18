#include <stdio.h>
#include "definiciones.h"
#include "ts.h"
#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lex.yy.h"

#define TAMM 8

abb arbol_simbolos;
simbolo aux;

//función para meter las palabras reservadas al principio
void insertar(char *lex, int id){
    aux.lexema = lex;
    insertar_nodo(&arbol_simbolos, aux);
}

void insertar_funcion(char *lex, double (*funcion)(double)){
    aux.lexema = lex;
    aux.valor.funcion = funcion;
    aux.tipo = FUNCION;
    insertar_nodo(&arbol_simbolos, aux);
}

//si la encuentra la ejecuta
short buscarEjecutar(char *lexema, double param, double *resultado){
    return buscar_ejecutar_nodo(&arbol_simbolos, lexema, param, resultado);
}


//si lo encuentra y no es cte lo modifica, si no lo encuentra lo inserta
short buscarModifElem(char *lexema, double valor){
    return buscar_modif_nodo(&arbol_simbolos, lexema, valor);
}

short buscarElem(char *lexema){
    if (buscar_nodo(&arbol_simbolos, lexema, &aux)){
        return aux.tipo;
    } else {
        return -1;
    }
}

double valorElem(char *lexema) {
    if (strcmp(lexema, aux.lexema) == 0) {
        return aux.valor.numero;
    } else {
        if (buscar_nodo(&arbol_simbolos, lexema, &aux)){
            return aux.valor.numero;
        } else {
            //error
            return -1;
        }
    }
}


abb arbol_simbolos; //árbol que vamos a utilizar como tabla de símbolos

//función para inicializar la tabla de símbolos
void inicializar_ts(){
    crear(&arbol_simbolos);
    aux.lexema = "pi";
    aux.valor.numero = 3.14159265358979323846;
    aux.tipo = CONSTANTE;
    insertar_nodo(&arbol_simbolos, aux);
    aux.lexema = "e";
    aux.valor.numero = 2.71828182845904523536;
    aux.tipo = CONSTANTE;
    insertar_nodo(&arbol_simbolos, aux);
    aux.lexema = "sin";
    aux.valor.funcion = sin;
    aux.tipo = FUNCION;
    insertar_nodo(&arbol_simbolos, aux);
    aux.lexema = "cos";
    aux.valor.funcion = cos;
    aux.tipo = FUNCION;
    insertar_nodo(&arbol_simbolos, aux);
    aux.lexema = "tan";
    aux.valor.funcion = tan;
    aux.tipo = FUNCION;
    insertar_nodo(&arbol_simbolos, aux);
    aux.lexema = "log";
    aux.valor.funcion = log10;
    aux.tipo = FUNCION;
    insertar_nodo(&arbol_simbolos, aux);
    aux.lexema = "ln";
    aux.valor.funcion = log;
    aux.tipo = FUNCION;
    insertar_nodo(&arbol_simbolos, aux);
    aux.lexema = "exp";
    aux.valor.funcion = exp;
    aux.tipo = FUNCION;
    insertar_nodo(&arbol_simbolos, aux);
    aux.lexema = "sqrt";
    aux.valor.funcion = sqrt;
    aux.tipo = FUNCION;
    insertar_nodo(&arbol_simbolos, aux);
}

void imprimir_ts(){
    imprimir_arbol(&arbol_simbolos);
}

void imprimir_vars(){
    imprimir_variables(&arbol_simbolos);
}

void borrar_vars(){
    borrar_variables(&arbol_simbolos);
}

//para destruir el árbol al terminar 
void destruir_ts(){
    destruir_arbol(&arbol_simbolos);
}
