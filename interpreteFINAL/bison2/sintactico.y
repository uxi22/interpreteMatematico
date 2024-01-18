%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stddef.h>
    #include <math.h>
    #include "ts.h"
    #include "definiciones.h"
    #include "errores.h"
    #include "sintactico.tab.h"
    #include "lex.yy.h"

    int yylex();
    int yyerror(char *s);
    void ayuda();
%}

%union{
    char *lexema;
    double num;   
}


%token <lexema> VARIABLE FICHERO
%token <num> ENTERO FLOTANTE

%token SALTO PUNTOCOMA EXIT WORKSPACE CLEAR LOAD HELP

%right IGUAL
%right '^'
%left '+' 
%left '-'
%left '*'
%left '/'

%type <num> expresion operacion asignacion funcion


%%

input: /*cadena vacía*/ {printf("$");}
    | input linea {printf("$");}
;

linea: expresion SALTO    {printf("Resultado: %.20f\n", $1);}
    | expresion PUNTOCOMA SALTO 
    | asignacion SALTO {printf("Asignado: %.20f\n", $1);}
    | asignacion PUNTOCOMA SALTO
    | SALTO
    | EXIT SALTO {printf("Saliendo...\n");return 0;}
    | WORKSPACE SALTO {printf("Área de trabajo:\n");imprimir_vars();}
    | CLEAR SALTO {borrar_vars();}
    | LOAD FICHERO {printf("Cargando fichero...\n"); cargar_fichero($2); free($2);}
    | HELP SALTO {ayuda();}
;

expresion: ENTERO   {$$ = $1;}
    | FLOTANTE {$$ = $1;}
    | VARIABLE  {if (buscarElem($1) > 0){
                    $$ = valorElem($1);
                }else { //error
                    gestion_error(ERROR3);
                    $$ = 0;
                }
                free($1);
    }
    | '(' expresion ')' {$$ = $2;}
    | operacion {$$ = $1;}
    | funcion {$$ = $1;}
;

operacion: expresion '+' expresion {$$ = $1 + $3;}
    | expresion '-' expresion {$$ = $1 - $3;}
    | '-' expresion {$$ = -$2;}
    | expresion '*' expresion    {$$ = $1 * $3;}
    | expresion '/' expresion  {
        if ($3 == 0){
            gestion_error(ERROR2);
            $$ = 0;
        }else $$ = $1 / $3;}
    | expresion '^' expresion {$$ = pow($1, $3);}
;

asignacion: VARIABLE IGUAL expresion{
    switch(buscarModifElem($1, $3)){
        case 0: 
            $$ = $3;
            break;
        case CONSTANTE: 
            gestion_error(ERROR4);
            free($1);
            break;
        case VAR_NUM: 
            $$ = $3;
            free($1);
            break;
        case FUNCION:
            gestion_error(ERROR9);
            free($1);
            break;
    }
    }
;

funcion: VARIABLE '(' expresion ')'{if ((buscarEjecutar($1, $3, &($$))) <3){
                                        gestion_error(ERROR7);
                                        $$ = 0;
                                    }
                                    free($1);
                                    }
    | VARIABLE '(' ')' {if (($$ = buscarEjecutar($1, 0, &($$))) <3){
                            gestion_error(ERROR7);
                            free($1);
                            $$ = 0;
                        }
                        free($1);
                        }
;

%%


int yyerror(char *s){
    gestion_error(ERROR10);
}

void ayuda(){
    printf("~~~Ayuda del intérprete~~~\n"
    "SINOPSIS:\n"
    "\t./interprete\n"
    "\t./interprete [fichero]\n"
    "COMANDOS\n"
    "\t\"exit\": Permite terminar la ejecución del intérprete y salir del programa\n"
    "\t\"workspace\": Muestra por pantalla las variables disponibles en el espacio de trabajo (variables declaradas y constantes del sistema)\n"
    "\t\"clear\": Limpia de la tabla de símbolos las variables declaradas hasta el momento\n"
    "\t\"load [fichero]\": Permite cargar un fichero para que el intérprete lo analice\n"
    "\t\"help\" o \"?\": Muestra el manual del intérprete\n"
    "FUNCIONES\n"
    "\tsin(): Calcula el seno en radianes\n"
    "\tcos(): Calcula el coseno en radianes\n"
    "\ttan(): Calcula la tangente en radianes\n"
    "\tlog(): Calcula el logaritmo en base 10\n"
    "\tln(): Calcula el logaritmo neperiano\n"
    "\texp(): Eleva \"e\" al exponente indicado\n"
    "\tsqrt(): Calcula la raíz cuadrada\n"
    "CONSTANTES\n"
    "\tpi = 3.14159265358979323846\n"
    "\te = 2.71828182845904523536\n");
}