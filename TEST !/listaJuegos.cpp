#include "listaJuegos.h"

void inicializar(tListaJuegos& lista_juegos) {
	lista_juegos.cont = 0;
	lista_juegos.capacidad = MAX_JUEGOS;

	lista_juegos.lista = new tPtrJuego[lista_juegos.capacidad];
}

void destruye(tListaJuegos& lista_juegos) {
	for (int i = 0; i < lista_juegos.cont; i++) {
		delete lista_juegos.lista[i];
	}

	delete [] lista_juegos.lista;
}

void insertar(tListaJuegos& lista_juegos, const tJuego& juego) {
	redimensionamiento(lista_juegos);
	if (lista_juegos.cont < lista_juegos.capacidad) {
		tPtrJuego ptrJuego = new tJuego(juego);

		lista_juegos.lista[lista_juegos.cont] = ptrJuego;
		lista_juegos.cont++;
	}	
}

int numero_juegos(const tListaJuegos& lista_juegos) {
	return lista_juegos.cont;

}

bool es_vacia(const tListaJuegos& lista_juegos) {
	return lista_juegos.cont == 0;
}

tJuego dame_juego(const tListaJuegos& lista_juegos, int pos) {
	return *lista_juegos.lista[pos];
}

void eliminar(tListaJuegos& lista_juegos, int pos) {
	if (pos >= 0 && pos < lista_juegos.cont) {
		for (int i = pos; i < lista_juegos.cont - 1; i++) {
			lista_juegos.lista[i] = lista_juegos.lista[i + 1];
		}
		delete lista_juegos.lista[lista_juegos.cont - 1];
		lista_juegos.cont--;
	}	
}

void redimensionamiento(tListaJuegos& lista_juegos) {
	if (lista_juegos.cont >= lista_juegos.capacidad) {
		int newSize = lista_juegos.capacidad * 2;
		tPtrJuego* vaux = new tPtrJuego[newSize];

		for (int i = 0; i < lista_juegos.cont; i++) {
			vaux[i] = lista_juegos.lista[i];
		}

		lista_juegos.capacidad = newSize;
		delete[] lista_juegos.lista;
		lista_juegos.lista = vaux;
	}	
}
/*
* "La implementación del módulo tendrá que incluir las funciones necesarias para la gestión de la lista,
 comoson la búsqueda y el redimensionamiento de la misma"
* Hay que implementarlo?
int busqueda(const tListaJuegos& lista_juegos, tJuego& juego) {
	int pos = 0;
	bool encontrado = false;
	while ((pos < lista_juegos.cont) && !encontrado) {
		if (*lista_juegos.lista[pos] == juego) { 
		// Parece que hay que definir un operador == para 
		// comparar un tJuego con otro
			encontrado = true;
		}
		else {
			pos++;
		}
	}
	if (!encontrado) {
		pos = -1;
	}
	return pos;
}
*/