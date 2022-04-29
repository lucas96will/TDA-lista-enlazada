#include <stdio.h>
#include "lista.h"
#include "testing.h"

#define TAM_PRUEBA_VEC 5

static void prueba_lista_crear() {
    lista_t* lista = lista_crear();
    printf("\nINICIO DE PRUEBAS DE CREAR LISTA\n");
    print_test("Crear lista", lista != NULL);
    print_test("Lista creada vacia", lista_esta_vacia(lista));
    print_test("Lista creada borrar primero es NULL", lista_borrar_primero(lista) == NULL);
    print_test("Lista creada ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista creada ver ultimo es NULL", lista_ver_primero(lista) == NULL);
    print_test("Lista creada obtener largo es 0", lista_largo(lista) == 0);

    lista_destruir(lista, NULL);
}
static void prueba_lista_insertar() {
    printf("\nINICIO DE PRUEBAS DE LISTA INSERTAR\n");

    lista_t* lista = lista_crear();
    int vec[TAM_PRUEBA_VEC] = {2, 4, 6, 8, 10};

    //Inserto el 2 al princpio y pruebo si el primero es 2
    print_test("Insertar el 2 primero en la lista", lista_insertar_primero(lista, &vec[0]));
    print_test("El primero en la lista es el 2", *(int*)lista_ver_primero(lista) == 2);

    //Inserto el 4 al princpio y pruebo si el primero es 4, el ultimo 2
    print_test("Insertar el 4 primero en la lista", lista_insertar_primero(lista, &vec[1]));
    print_test("El primero en la lista es el 4", *(int*)lista_ver_primero(lista) == 4);
    print_test("Ultimo en la lista es el 2", *(int*)lista_ver_ultimo(lista) == 2);

    //Inserto el 6 al principio y pruebo si el primero es 6 y ultimo 2
    print_test("Insertar el 6 primero en la lista", lista_insertar_primero(lista, &vec[2]));
    print_test("El primero en la lista es el 6", *(int*)lista_ver_primero(lista) == 6);
    print_test("Ultimo en la lista es el 2", *(int*)lista_ver_ultimo(lista) == 2);

    //Inserto el 8 a lo ultimo y pruebo si el primero es 6 y el ultimo 8
    print_test("Insertar el 6 primero en la lista", lista_insertar_ultimo(lista, &vec[3]));
    print_test("El primero en la lista es el 6", *(int*)lista_ver_primero(lista) == 6);
    print_test("Ultimo en la lista es el 8", *(int*)lista_ver_ultimo(lista) == 8);

    //Inserto el 10 a lo ultimo y pruebo si el primero es 6 y el ultimo 10
    print_test("Insertar el 6 primero en la lista", lista_insertar_ultimo(lista, &vec[4]));
    print_test("El primero en la lista es el 6", *(int*)lista_ver_primero(lista) == 6);
    print_test("Ultimo en la lista es el 8", *(int*)lista_ver_ultimo(lista) == 10);

    lista_destruir(lista, NULL);
}

static void prueba_lista_esta_vacia() {
    printf("\nINICIO DE PRUEBAS DE LISTA ESTA VACIA\n");

    int vec[TAM_PRUEBA_VEC] = {2, 4, 6, 8, 10};
    lista_t* lista = lista_crear();

    //Inserto al principio, pruebo si esta vacia
    print_test("Insertar el 2, primero en la lista", lista_insertar_primero(lista, &vec[0]));
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    //borro al principio y pruebo si esta vacia
    print_test("Borro el 2 de la lista", *(int*)lista_borrar_primero(lista) == 2);
    print_test("La lista esta vacia", lista_esta_vacia(lista));

    //Inserto a lo ultimo, pruebo si esta vacia
    print_test("Insertar el 2, ultimo en la lista", lista_insertar_ultimo(lista, &vec[0]));
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    //borro al principio y pruebo si esta vacia
    print_test("Borro el 2 de la lista", *(int*)lista_borrar_primero(lista) == 2);
    print_test("La lista esta vacia", lista_esta_vacia(lista));


    lista_destruir(lista, NULL);
}



void pruebas_lista_estudiante() {
    //..
    prueba_lista_crear();
    prueba_lista_esta_vacia();
    prueba_lista_insertar();


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
