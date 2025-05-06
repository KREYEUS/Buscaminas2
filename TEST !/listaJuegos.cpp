// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "listaJuegos.h"

void inicializar(tListaJuegos& lista_juegos) {
	lista_juegos.cont = 0;
	lista_juegos.capacidad = MAX_JUEGOS;

	lista_juegos.lista = new tPtrJuego[lista_juegos.capacidad];
}

void destruye(tListaJuegos& lista_juegos) {
	for (int i = 0; i < lista_juegos.cont; i++) {
		delete lista_juegos.lista[i];
		lista_juegos.lista[i] = nullptr;
	}

	delete [] lista_juegos.lista;
	
	lista_juegos.lista = nullptr;
	lista_juegos.cont = 0;

	// lista_juegos.capacidad = 0; 
	// Por lo que he mirado, puede dar problemas
}

int insertar(tListaJuegos& lista_juegos, const tJuego& juego) {
	redimensionamiento(lista_juegos);
	int pos = busqueda(lista_juegos, juego);

	if (lista_juegos.cont < lista_juegos.capacidad) {
		tPtrJuego ptrJuego = new tJuego(juego);
		for (int i = lista_juegos.cont; i > pos; i--) {
			lista_juegos.lista[i] = lista_juegos.lista[i - 1];
		}
		lista_juegos.lista[pos] = ptrJuego;
		lista_juegos.cont++;
	}
	return pos;
}

int numero_juegos(const tListaJuegos& lista_juegos) {
	return lista_juegos.cont;
}

bool es_vacia(const tListaJuegos& lista_juegos) {
	return lista_juegos.cont == 0;
}

tJuego dame_juego(const tListaJuegos& lista_juegos, int pos) {
	return *lista_juegos.lista[pos]; 
	// Asumido que se ha comprobado que pos es correcto
}

void eliminar(tListaJuegos& lista_juegos, int pos) { 
	// Elimina el elemento sobre escribiendolo
	if (pos >= 0 && pos < lista_juegos.cont) {
		for (int i = pos; i < lista_juegos.cont - 1; i++) {
			lista_juegos.lista[i] = lista_juegos.lista[i + 1];
		}
		// Elimino el ultimo elemento que esta duplicado
		delete lista_juegos.lista[lista_juegos.cont - 1]; 
		lista_juegos.lista[lista_juegos.cont - 1] = nullptr;
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


int busqueda(const tListaJuegos& lista_juegos, const tJuego& juego) {
	int pos = 0;
	bool encontrado = false;
	int dificultadJuego = calcula_nivel(juego), i = 0;

	while (!encontrado && i < lista_juegos.cont) {
		int niveli = calcula_nivel(*lista_juegos.lista[i]);
		if (dificultadJuego > niveli) {
			i++;
			pos = i;
		}
		else{
			pos = i;
			encontrado = true;
		}		
	}
	return pos;
}