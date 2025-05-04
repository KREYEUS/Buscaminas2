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