#include <stdio.h>
#include "lista.h"
#include "testing.h"

#define TAM_PRUEBA_VEC 5

/*Funcion para agregar todos los elementos del arreglo vec usando insertar (puede elegirse al principio o ultimo)*/
void _lista_insertar_arreglo(lista_t* lista, int* vec, size_t largo, bool insertar(lista_t* lista, void* dato)) {
    for(int i = 0; i < largo; i++) {
        insertar(lista, &vec[i]);
    }
}

/*borra todos los valores de la lista(de enteros) y compara con los valores del arreglo (ascendente)*/
bool _lista_borrar_comparar(lista_t* lista, const int* vec) {
    int num;
    size_t i = 0;
    while(!lista_esta_vacia(lista)){
        num = *(int*)lista_borrar_primero(lista);
        if(num != vec[i++]){
            return false;
        }
    }
    return true;
}

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



static void prueba_lista_borrar() {
    printf("\nINICIO DE PRUEBAS DE LISTA BORRAR\n");

    int vec[TAM_PRUEBA_VEC] = {4, 8, 12, 16, 20};
    int vec2[TAM_PRUEBA_VEC] = {20, 16, 12, 8, 4};
    lista_t* lista = lista_crear();

    //Agrego a la lista algunos elementos a lo ultimo
    _lista_insertar_arreglo(lista, vec, TAM_PRUEBA_VEC, lista_insertar_ultimo);
    //La lista deberia ser (primero) [4, 8, 12, 16, 20] (ultimo), comprobamos*/

    //Pruebo si los elementos borrados son los correctos!
    print_test("Prueba lista borrar elementos agregados al final", _lista_borrar_comparar(lista, vec));

    //Agrego elementos al principio y compruebo que al borrar sean los adecuados
    _lista_insertar_arreglo(lista, vec, TAM_PRUEBA_VEC, lista_insertar_primero);
    //La lista deberia ser (primero) [20, 16, 12, 8, 4] (ultimo), comprobamos*/

    print_test("Prueba lista borrar elementos agregados al principio", _lista_borrar_comparar(lista, vec2));

    lista_destruir(lista, NULL);
}

static void prueba_lista_largo() {
    lista_t* lista = lista_crear();
    int vec[TAM_PRUEBA_VEC] = {4, 8, 12, 16, 20};

    printf("\nINICIO DE PRUEBAS DE LARGO DE LISTA\n");

    print_test("Prueba largo lista recien creada es 0", lista_largo(lista) == 0);

    //Inserto 1 elemento y pruebo si el largo es 1
    lista_insertar_primero(lista, &vec[0]);
    print_test("Inserto un elemento, largo de lista 1", lista_largo(lista) == 1);

    //Borro el dato y pruebo si el largo es 0
    lista_borrar_primero(lista);
    print_test("Borro el unico elemento, largo de lista 0", lista_largo(lista) == 0);

    //Inserto varios elementos y pruebo si el largo es correcto
    _lista_insertar_arreglo(lista, vec, TAM_PRUEBA_VEC, lista_insertar_primero);
    print_test("Inserto 5 elementos, largo de lista 5", lista_largo(lista) == 5);

    //Borro 1 elemento y pruebo si el largo es 4
    lista_borrar_primero(lista);
    print_test("Borro 1 elemento, largo de lista 4", lista_largo(lista) == 4);

    //Borro todos los elementos y pruebo si el largo es 0
    while(!lista_esta_vacia(lista)) {
        lista_borrar_primero(lista);
    }
    print_test("Borro todos los elementos, largo de lista es 0", lista_largo(lista) == 0);

    lista_destruir(lista, NULL);
}


void pruebas_lista_estudiante() {
    //..
    prueba_lista_crear();
    prueba_lista_esta_vacia();
    prueba_lista_insertar();
    prueba_lista_borrar();
    prueba_lista_largo();

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
