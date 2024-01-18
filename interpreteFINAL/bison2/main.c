#include <stdio.h>
#include "definiciones.h"
#include "ts.h"
#include "lex.yy.h"
#include "sintactico.tab.h"
#include "errores.h"

int main(int argc, char **argv) {
    if (argc > 2) {
        gestion_error(ERROR6);
        return 1;
    }
    inicializar_ts();
    printf("Tabla de símbolos:\n");
    imprimir_ts();
    if (argc == 2) {
        cargar_fichero(argv[1]);
    }
    printf(">>>>INTÉRPRETE<<<<\n");
    yyparse();
    printf(">>>>FIN INTÉRPRETE<<<<\n");
    printf("Tabla de símbolos:\n");
    imprimir_ts();
    destruir_ts();
    return 0;
}