%{
    #include <stdio.h>
    #include "sintactico.tab.h"
    #include "definiciones.h"
    #include "errores.h"
    void cargar_fichero(char *fich);
    void cerrar_fichero();
%}

%option noyywrap

/*TOKENS*/
CARACTER [a-zA-Z]
DIGITO [0-9]
START_EXPONENTE_DEC ([eE][+-]?)

NUM_ENTERO {DIGITO}+
NUM_FLOAT {DIGITO}+("."{DIGITO}+)?({START_EXPONENTE_DEC}{DIGITO}+)?

IDENT {CARACTER}({CARACTER}|{DIGITO})*
FICH ({CARACTER}|{DIGITO})+(\.{CARACTER}+)

SALTO_LINEA \n

OPS [+-/*^]

%x FICHERO_

%%

"exit" {return EXIT;}
"workspace" {return WORKSPACE;}
"clear" {return CLEAR;}
"load" {BEGIN FICHERO_; return LOAD;}
<FICHERO_>{FICH} {yylval.lexema = strdup(yytext); BEGIN(INITIAL); return FICHERO;}
"help" {return HELP;}
"?" {return HELP;}
{IDENT} {yylval.lexema = strdup(yytext); return VARIABLE;}
{NUM_ENTERO} {yylval.num = atoi(yytext); return ENTERO; }
{NUM_FLOAT} {yylval.num = atof(yytext); return FLOTANTE; }
{SALTO_LINEA} {return SALTO;}
{OPS} {return (int)*yytext;}
"("|")" {return (int)*yytext;}
"=" {return IGUAL;}
";" {return PUNTOCOMA;}
" "

. {gestion_error(ERROR1);}

<<EOF>> {cerrar_fichero(); return (SALTO, SALTO) ;}

%%

FILE *fichero;

void cargar_fichero(char *fich)
{
    if ((fichero = fopen(fich, "r")) == NULL) {
        gestion_error(ERROR5);
        yyin = stdin;
    } else{
        yyin = fichero;
    }
}

void cerrar_fichero(){
    if (fichero != NULL){
        fclose(fichero);
    }
    yyin = stdin;
    yyrestart(stdin);
}
