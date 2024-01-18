#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#define TAM 40

typedef union {
    double numero;
    double (*funcion)();
} tipo;

typedef struct {
    char *lexema;
    short tipo;
    tipo valor;
} componente_lex;


//fin de fichero
#define ENDOFF 309

#define VAR_NUM 1
#define CONSTANTE 2
#define FUNCION 3

#define ERROR1 400
#define ERROR2 401
#define ERROR3 402
#define ERROR4 403
#define ERROR5 404
#define ERROR6 405
#define ERROR7 406
#define ERROR8 407
#define ERROR9 408
#define ERROR10 409




#endif
