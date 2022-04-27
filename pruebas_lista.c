#include <stdio.h>
#include "lista.h"
#include "testing.h"

static void prueba_lista_vacia(){

}



void pruebas_lista_estudiante(){
    //..
    prueba_lista_vacia();

}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
