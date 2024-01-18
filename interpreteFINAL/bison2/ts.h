#ifndef TS_H
#define TS_H

#include "definiciones.h"

typedef componente_lex simbolo;


void inicializar_ts();
simbolo buscarInsertElem(char *lexema);
short buscarModifElem(char *lexema, double valor);
short buscarEjecutar(char *lexema, double param, double *resultado);
short buscarElem(char *lexema);

double valorElem(char *lexema);
void destruir_ts();
void imprimir_ts();
void imprimir_vars();
void borrar_vars();

#endif